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
 *	basic struct of our types , it shows qualifiers and other things
 *	related to the type
 */
struct type {
	int type;
	bool is_unsigned;
	bool is_const;
	bool is_volatile;
	bool is_restrict;
	bool is_pointer;
};
#define type_copy(src, dest) { \
	dest.type = src->type; \
	dest.is_unsigned = src->is_unsigned; \
	dest.is_const = src->is_const; \
	dest.is_volatile = src->is_volatile; \
	dest.is_restrict = src->is_restrict; \
	dest.is_pointer = src->is_pointer; \
}

/*
 *	main data structure for symbol table
 *	for now our symbol table is simple based on single linked list
 *	data structure 
 *	TODO : Impelement a hashtable for symbol table
 */
struct symbol_table {
	struct symtab_entry *entries;
	struct symtab_entry *last;	/* we hold last entry because its gonna be so slow to get last entry each time that */
	int buflen;
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
	union value val;
};
#define is_pointer(e) (e->entry_type.is_pointer)
#define is_const(e)	(e->entry_type.is_const)

public struct symbol_table *symtab;

/*
 *	@brief : Initialize our gloabal symbol table with default value of 
 *	SYMTAB_SIZE
 */
public void symtab_init();

/*
 *	@brief : Add given entry to global symbol table , it will add to
 *	'next' of last entry, and if last is empty so it's gonna be first one
 */	
public void symtab_add(struct symtab_entry *);

/*
 *	@brief : Create New entry for symbold table with value type
 */
public void symtab_create_integer(char *, int, struct type *, struct position);

/*
 *	@brief : return entry by its name
 */
public struct symtab_entry *symtab_get_by_name(char *);

/*
 *	@brief : print symbol table in human readable format (it will print 
 *				'symtab' lobal symbol table by default)
 */
public void print_symtab();

#endif
