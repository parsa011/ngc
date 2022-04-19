#ifndef _A_LITTLE_BASICS_H
# define _A_LITTLE_BASICS_H

#ifdef WIN32
#include <io.h>
#define F_OK 0
#define access _access

#else

#define COLORDEFAULT "\x1b[0m"
#define COLORBOLD 	"\x1b[1m"
#define COLORDIM		"\x1b[2m"
#define COLORITALIC	"\x1b[3m"
#define COLORUNDLINE "\x1b[4m"
#define COLORBLINK	"\x1b[5m"
#define COLORINVERT 	"\x1b[7m"
#define COLORRED 	"\x1b[31m"
#define COLORGREEN   "\x1b[32m"
#define COLORYELLOW  "\x1b[33m"
#define COLORBLUE	"\x1b[34m"
#define COLORMAGENTA "\x1b[35m"
#define COLORCYAN    "\x1b[36m"
#define COLORNORMAL  "\x1b[39m"
#define COLOROVLINE	"\x1b[53m"
#define COLORGRAY	"\x1b[90m"

#endif

#include "../../config.h"

#include <stdio.h>

#define print(str)		printf("%s", (str))
#define printl(str)		printf("%s\n", (str))

#ifndef EOL
# define EOL '\n'
#endif

#ifndef var
#define var	extern
#endif

typedef unsigned char	    uchar;
typedef unsigned short	    ushort;
typedef unsigned int	    uint;
typedef unsigned long       ulong;
typedef signed char         int8;
typedef unsigned char       uint8;
typedef signed short int    int16;
typedef unsigned short int  uint16;
typedef signed int          int32;
typedef unsigned int        uint32;
typedef signed long int     int64;
typedef unsigned long int   uint64;

/*
 * Boolean constants
 */
#if HAVE_BOOL
#include <stdbool.h>
#else
typedef enum {
	FALSE,
	TRUE
} bool;
#endif

/*
 * Some usefull constants for strings :D
 */
#ifndef IN
# define OUT 0
# define IN 1
#endif

/*
 * Min and Max :D
 */
#ifndef MAX
# define MAX(a, b) ((a) < (b) ? (b) : (a))
#endif
#ifndef MIN
# define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

/*
 * Two string Concatination
 */
#ifndef CONCAT
# define CONCAT(a,b) a ## b
#endif

#define ISNUMBER(c) (c >= '0' && c <= '9')

/* 
 * n string concatination
 */
#define strcpyall(buf, offset, ...) do{ \
	char *bp=(char*)(buf+offset); /*so we can add to the end of a string*/ \
	const char *s, \
	*a[] = { __VA_ARGS__,NULL}, \
	**ss=a; \
	while((s=*ss++)) \
	while((*s)&&(++offset<(int)sizeof(buf))) \
	*bp++=*s++; \
	if (offset!=sizeof(buf))*bp=0; \
}while(0)

/* 
 * foreach in c haha
 */
#define foreach(item, array) \
	for(int keep=1, \
			count=0,\
			size=sizeof (array)/sizeof *(array); \
			keep && count != size; \
			keep = !keep, count++) \
for(item = (array)+count; keep; keep = !keep)

/*
 * LENGTH of an array
 */
#define ARRAY_LENGTH(array) (sizeof(array) / sizeof (array[0]))

/*
 * is even and odd for number
 */
#define IS_EVEN( num )  (!IS_ODD( (num) ))
#define IS_ODD( num )   ((num) & 1)

#define CHAR_TO_NUM(c) (c - '0')

#endif
