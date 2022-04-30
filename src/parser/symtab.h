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
#include "../ast/ast.h"
#include "../lexer/lexer.h"

/*
 *	main data structure for symbol table
 */
struct symbol_table {
	struct symtab_entry *entries;
	int buflen;
};

struct type {
	int type;
	bool is_unsigned;
	bool is_const;
	bool is_volatile;
	bool is_restrict;
	bool is_pointer;
	bool is_pointer_const;
	bool is_pointer_volatile;
	bool is_pointer_restrict;
	//int ref : 16;
};

/*
 *	entries for symbol table
 *	single-linked list
 */
struct symtab_entry {
	struct symtab_entry *next;
	struct type entry_type;
	struct position pos;
	char *name;
};

public struct symbol_table *symtab;

/*
 *	@brief : Initialize our gloabal symbol table with default value of 
 *	SYMTAB_SIZE
 */
public void symtab_init();

/*
 *	@brief : Create New entry for symbold table with value type
 */
public void symtab_create_integer(char *, int);

#endif
