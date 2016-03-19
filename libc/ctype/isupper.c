/*
 *	libc/ctype/isupper.c
 *
 *	Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#include <ctype.h>

#undef isupper

int isupper(int c)
{
	return (__ctype[(c)+1]&(_U));
}
