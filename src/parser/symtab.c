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
}

/*
 *	TODO : Impelement
 *	very simple now , for now we just support simple variables like
 *	this :
 *		int age = 10;
 *	we need to add qualifers and ...
 */
public void symtab_create_integer(char *text, int value, struct position pos)
{
	struct symtab_entry *entry = ngc_malloc(sizeof(struct symtab_entry));
	entry->name = strdup(text);
	entry->integer = value;
	entry->entry_type.type = T_INT;
	pos_copy(pos, entry->pos);
	symtab_add(entry);
}

public void print_symtab()
{
	for (struct symtab_entry *entry = symtab->entries; entry; entry = entry->next) {
		printf("%s (%d:%d)", entry->name, entry->pos.line, entry->pos.col);
		printf(" ---> \033[33m%d\033[0m", entry->integer);
		putchar('\n');
	}
}
