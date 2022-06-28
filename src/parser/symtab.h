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
#include "../type/types.h"

typedef struct symbol_table_t symbol_table;
typedef struct symtab_entry_t symtab_entry;

/*
 *	main data structure for symbol table
 *	for now our symbol table is simple based on single linked list
 *	data structure 
 *	TODO : Impelement a hashtable for symbol table
 */
struct symbol_table_t {
	symtab_entry *entries;
	symtab_entry *last;	/* we hold last entry because its gonna be so slow to get last entry each time that */
	int buflen;
};

/*
 *	entries for symbol table
 *	single-linked list
 */
struct symtab_entry_t {
	symtab_entry *next;
	char *name;
	value val;
	type entry_type;
	struct position pos;
};
#define symbol_entry_type(e) (e->entry_type.type)

/*
 *	our global symbol table
 */
public symbol_table symtab;

/*
 *	@brief : Initialize our gloabal symbol table with default value of 
 *	SYMTAB_SIZE
 */
public void symtab_init();

/*
 *	@brief : Add given entry to global symbol table , it will add to
 *	'next' of last entry, and if last is empty so it's gonna be first one
 */	
public void symtab_add(symtab_entry *);

/*
 *	@brief : Create New entry for symbold table with value type
 */
public void symtab_create_entry(char *, value, type *, struct position);

/*
 *	@brief : return entry by its name
 */
public symtab_entry *symtab_get_by_name(char *, bool);

/*
 *	@brief : print symbol table in human readable format (it will print 
 *				'symtab' lobal symbol table by default)
 */
public void print_symtab();

#endif
