#ifndef _A_LITTLE_BASICS_H
# define _A_LITTLE_BASICS_H

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
typedef char * 				string;

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

#endif
