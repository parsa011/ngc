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
#include "util/file_util.h"
#include "../lib/prosing.h"

#define NGC_DEBUG 1
#define DEBUG_LEXER 1

#define VERSION "0.0.1"

#define NGC_FILE_TYPE "c"

#define PROMPT	">> "

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

#define new_pos_struct ((struct position) { .line = 1, .col = 0 })
#define pos_copy(src, dest) { \
	dest.line = src.line; \
	dest.col = src.col; \
}
#define pos_decrease(pos) { \
	if (pos.col == 0) \
		pos.line-- \
	else \
		pos.col-- \
}

public bool interp_mode;

/*
 *	@brief : print usage and panic
 */
void usage();

/*
 *	@brief : print prompt when program is in interp mode
 */
public void print_prompt();

/*
 *	@brief : write messages and exit()
 */
void panic(const char *, ...);

#endif
