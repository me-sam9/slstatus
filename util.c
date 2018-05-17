/* See LICENSE file for copyright and license details. */
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

const char *
bprintf(const char *fmt, ...)
{
	va_list ap;
	int ret;

	va_start(ap, fmt);
	if ((ret = vsnprintf(buf, sizeof(buf), fmt, ap)) < 0) {
		fprintf(stderr, "vsnprintf: %s\n", strerror(errno));
	} else if ((size_t)ret >= sizeof(buf)) {
		fprintf(stderr, "vsnprintf: Output truncated\n");
	}
	va_end(ap);

	return buf;
}

int
pscanf(const char *path, const char *fmt, ...)
{
	FILE *fp;
	va_list ap;
	int n;

	if (!(fp = fopen(path, "r"))) {
		fprintf(stderr, "fopen '%s': %s\n", path, strerror(errno));
		return -1;
	}
	va_start(ap, fmt);
	n = vfscanf(fp, fmt, ap);
	va_end(ap);
	fclose(fp);

	return (n == EOF) ? -1 : n;
}
