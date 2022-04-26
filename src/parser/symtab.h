#ifndef _SYMTAB_H
# define _SYMTAB_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*
*	Symbol Table
*/

#include "../ngc.h"
#include "../lexer/lexer.h"

#define SYMTAB_SIZE 40

/*
 *	main data structure for symbol table
 */
struct symbol_table {
	struct symtab_entry **entries;
	int buflen;
	int bufsize;
};

struct symtab_entry {
	char *name;
	struct type entry_type;
};

#endif
