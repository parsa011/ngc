#ifndef _NGC_H
# define _NGC_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include <stdbool.h>

#include "util/basic.h"
#include "util/mem.h"

/*
 *	These are some basic definitions, for readablity we define extern as public
 *	and private as static
 */
#define public extern
#define private static

/*
 *	@brief : just a simple struct to hold position of something, (it can be token and ...)
 */
struct position {
	int line;
	int col;
};

void usage();

void panic(const char *, ...);

#endif
