/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "symtab.h"

struct symbol_table *symtab;

public void symtab_init()
{
	symtab = ngc_malloc(sizeof(struct symbol_table));
	symtab->buflen = 0;
}

/*
 *	@brief : Append given entry to end of chain
 *	do panic when there is an entry with given entry name
 */
public void symtab_add(struct symtab_entry *entry)
{
	assert(symtab);
	if (symtab_get_by_name(entry->name, false)) {
		show_lexer_error("There is a entry with This name");
		panic(NULL);
	}
	if (!symtab->entries) {
		symtab->entries = entry;
	} else {
		symtab->last->next = entry;
	}
	symtab->last = entry;
	symtab->last->next = NULL;
}

/*
 *	@brief : Create a symbol table entry with given informations
 */
public void symtab_create_entry(char *text, union value val, struct type *tp, struct position pos)
{
	struct symtab_entry *entry = ngc_malloc(sizeof(struct symtab_entry));
	entry->name = strdup(text);
	set_val_by_type(&entry->val, &val);
	pos_copy(pos, entry->pos);
	struct type *entry_type = &entry->entry_type;
	type_copy(tp, entry_type);
	symtab_add(entry);
}

public struct symtab_entry *symtab_get_by_name(char *name, bool show_error)
{
	for (struct symtab_entry *entry = symtab->entries; entry; entry = entry->next){
		if (STR_EQUAL(name, entry->name))
			return entry;
	}
	if (show_error) {
		show_lexer_error("Identifier Didn't found");
		panic(NULL);
	}
	return NULL;
}

public void print_symtab()
{
	for (struct symtab_entry *entry = symtab->entries; entry; entry = entry->next) {
		int type = symbol_entry_type(entry);
		printf("%s -> \033[04m%s\033[0m (%d:%d)", entry->name, get_token_str(type), 
				entry->pos.line, entry->pos.col);
		if (is_pointer(entry)) {
			printf(" (pointer)");
		}
		printf("\033[33m");
		if (type == T_INT)
			printf(" ---> %d", entry->val.intval);
		else if (type == T_LONG) 
			printf(" ---> %ld", entry->val.longval);
		else if (type == T_DOUBLE || type == T_FLOAT)
			printf(" ---> %f", entry->val.realval);
		printf("\033[0m");
		putchar('\n');
	}
}
