/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>

#include "../util.h"

const char *
disk_free(const char *mnt)
{
	struct statvfs fs;

	if (statvfs(mnt, &fs) < 0) {
		warn("statvfs '%s':", mnt);
		return NULL;
	}

	return fmt_human_2(fs.f_frsize * fs.f_bavail);
}

const char *
disk_perc(const char *mnt)
{
	struct statvfs fs;

	if (statvfs(mnt, &fs) < 0) {
		warn("statvfs '%s':", mnt);
		return NULL;
	}

	return bprintf("%d", (int)(100 *
	               (1.0f - ((float)fs.f_bavail / (float)fs.f_blocks))));
}

const char *
disk_total(const char *mnt)
{
	struct statvfs fs;

	if (statvfs(mnt, &fs) < 0) {
		warn("statvfs '%s':", mnt);
		return NULL;
	}

	return fmt_human_2(fs.f_frsize * fs.f_blocks);
}

const char *
disk_used(const char *mnt)
{
	struct statvfs fs;

	if (statvfs(mnt, &fs) < 0) {
		warn("statvfs '%s':", mnt);
		return NULL;
	}

	return fmt_human_2(fs.f_frsize * (fs.f_blocks - fs.f_bfree));
}
