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
 *	very simple now , for now we just support simple variables like
 *	this :
 *		int age = 10;
 *	we need to add qualifers and ...
 */
public void symtab_create_entry(char *text, union value val, struct type *tp, struct position pos)
{
	struct symtab_entry *entry = ngc_malloc(sizeof(struct symtab_entry));
	entry->name = strdup(text);
	// TODO set entry value by considering type
	set_val_by_type(entry->val, val, tp);
	pos_copy(pos, entry->pos);
	type_copy(tp, entry->entry_type);
	symtab_add(entry);
}

public struct symtab_entry *symtab_get_by_name(char *name)
{
	for (struct symtab_entry *entry = symtab->entries; entry; entry = entry->next){
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
		int type = symbol_entry_type(entry);
		if (type == TK_INT)
			printf(" ---> \033[33m%d\033[0m", entry->val.intval);
		else if (type == TK_REAL)
			printf(" ---> \033[33m%f\033[0m", entry->val.realval);
		putchar('\n');
	}
}
