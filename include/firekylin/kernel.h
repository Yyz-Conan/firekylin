/*
 *    include/firekylin/kernel.h
 *
 *    Copyright (C) 2016 ximo<ximoos@foxmail.com>
 */

#ifndef _KERNEL_H
#define _KERNEL_H

#include <sys/types.h>

#define irq_disable() 			\
    __asm__("cli");

#define irq_enable() 			\
    __asm__("sti");

/* Just should be used once in a function */
#define irq_lock()			\
    unsigned long  __flag;		\
    __asm__("pushf;popl %0;cli":"=m"(__flag))

/* Used must after irq_lock() */
#define irq_unlock()			\
    __asm__("pushl %0;popf"::"m"(__flag))

#define inb(port) 			\
    ({					\
	unsigned char __res;		\
	__asm__ __volatile__ (		\
            "in %%dx,%%al"  		\
	    : "=a"(__res) 		\
	    :"d"(port));		\
	__res;				\
    })

#define outb(port,value)   		\
    __asm__("out %%al,%%dx" : :"a"(value),"d"(port))

#define ins(port,buf,size)		\
    __asm__("rep insw" :: "D"(buf),"d"(port),"c"(size>>1))

#define outs(port,buf,size)		\
    __asm__("rep outsw" :: "S"(buf),"d"(port),"c"(size>>1))

#define memcpy(dst,src,size)		\
    __asm__("rep movsb":: "D"(dst),"S"(src),"c"(size));
    
#define memset(s,c,size)		\
    __asm__("rep stosb" ::"D"(s),"a"(c),"c"(size));

static inline int strncmp(char *s1, char *s2, int n)
{
	while (n--) {
		if (*s1 && (*s1 == *s2)) {
			s1++;
			s2++;
		} else {
			return (*s1 - *s2);
		}
	}
	return 0;
}  

static inline char * strncpy(char *dst, char *src, size_t n)
{
	char *t = dst;
	while (n-- && (*t++ = *src++))
		;
	return dst;
}

#define max(a,b)	((a)>=(b) ? (a) : (b))
#define min(a,b)	((a)<=(b) ? (a) : (b))

extern int printk(char * fmt, ...);
extern void panic(char * fmt, ...);

#endif
