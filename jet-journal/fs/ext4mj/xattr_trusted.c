// SPDX-License-Identifier: GPL-2.0
// Per-core journaling part by Jongseok Kim
// SPDX-FileCopyrightText: Copyright (c) 2021 Sungkyunkwan University
/*
 * linux/fs/ext4mj/xattr_trusted.c
 * Handler for trusted extended attributes.
 *
 * Copyright (C) 2003 by Andreas Gruenbacher, <a.gruenbacher@computer.org>
 */

#include <linux/string.h>
#include <linux/capability.h>
#include <linux/fs.h>
#include "ext4mj_zj.h"
#include "ext4mj.h"
#include "xattr.h"

static bool
ext4mj_xattr_trusted_list(struct dentry *dentry)
{
	return capable(CAP_SYS_ADMIN);
}

static int
ext4mj_xattr_trusted_get(const struct xattr_handler *handler,
		       struct dentry *unused, struct inode *inode,
		       const char *name, void *buffer, size_t size)
{
	return ext4mj_xattr_get(inode, EXT4MJ_XATTR_INDEX_TRUSTED,
			      name, buffer, size);
}

static int
ext4mj_xattr_trusted_set(const struct xattr_handler *handler,
		       struct dentry *unused, struct inode *inode,
		       const char *name, const void *value,
		       size_t size, int flags)
{
	return ext4mj_xattr_set(inode, EXT4MJ_XATTR_INDEX_TRUSTED,
			      name, value, size, flags);
}

const struct xattr_handler ext4mj_xattr_trusted_handler = {
	.prefix	= XATTR_TRUSTED_PREFIX,
	.list	= ext4mj_xattr_trusted_list,
	.get	= ext4mj_xattr_trusted_get,
	.set	= ext4mj_xattr_trusted_set,
};
