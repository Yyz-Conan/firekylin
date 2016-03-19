/*
 *	libc/unistd/dup.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/unistd.h>
#include <sys/fcntl.h>

static inline __syscall3(int, fcntl, int, fd, int ,cmd, long ,arg);

int dup(int fd)
{
	return fcntl(fd,F_DUPFD,0);
}
