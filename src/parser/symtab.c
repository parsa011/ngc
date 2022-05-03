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

public void symtab_add(struct symtab_entry *entry)
{
	assert(symtab);
	if (!symtab->entries) {
		symtab->entries = entry;
	} else {
		symtab->last->next = entry;
	}
	symtab->last = entry;
	symtab->last->next = NULL;
}

/*
 *	TODO : Impelement
 *	very simple now , for now we just support simple variables like
 *	this :
 *		int age = 10;
 *	we need to add qualifers and ...
 */
public void symtab_create_integer(char *text, int value, struct type *tp, struct position pos)
{
	struct symtab_entry *entry = ngc_malloc(sizeof(struct symtab_entry));
	entry->name = strdup(text);
	entry->val.intval = value;
	pos_copy(pos, entry->pos);
	type_copy(tp, entry->entry_type);
	symtab_add(entry);
}

public struct symtab_entry *symtab_get_by_name(char *name)
{
	for (struct symtab_entry *entry = symtab->entries; entry != NULL; entry = entry->next){
		if (STR_EQUAL(name, entry->name))
			return entry;
	}
	show_lexer_error("Identifier Didn't found");
	panic(NULL);
	return NULL;
}

public void print_symtab()
{
	for (struct symtab_entry *entry = symtab->entries; entry; entry = entry->next) {
		printf("%s (%d:%d)", entry->name, entry->pos.line, entry->pos.col);
		if (is_pointer(entry)) {
			printf(" (pointer)");
		}
		printf(" ---> \033[33m%d\033[0m", entry->val.intval);
		putchar('\n');
	}
}
