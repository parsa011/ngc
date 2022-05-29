/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "symtab.h"

symbol_table *symtab;

public void symtab_init()
{
	symtab = ngc_malloc(sizeof(symbol_table));
	symtab->buflen = 0;
}

/*
 *	@brief : Append given entry to end of chain
 *	do panic when there is an entry with given entry name
 */
public void symtab_add(symtab_entry *entry)
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
public void symtab_create_entry(char *text, value val, type *tp, struct position pos)
{
	symtab_entry *entry = ngc_malloc(sizeof(symtab_entry));
	entry->name = strdup(text);
	set_val_by_type(&entry->val, &val, T_EQUAL);
	pos_copy(pos, entry->pos);
	type *entry_type = &entry->entry_type;
	type_copy(tp, entry_type);
	symtab_add(entry);
}

public symtab_entry *symtab_get_by_name(char *name, bool show_error)
{
	for (symtab_entry *entry = symtab->entries; entry; entry = entry->next){
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
	for (symtab_entry *entry = symtab->entries; entry; entry = entry->next) {

		int type = symbol_entry_type(entry);
		printf("%s -> %s%s%s (%d:%d)", entry->name, COLORUNDLINE, get_valyetype_str(type), COLORDEFAULT, entry->pos.line, entry->pos.col);
		if (is_pointer(entry)) {
			printf(" (pointer)");
		}
		printf(COLORYELLOW);
		if (type == TYPE_INT)
			printf(" ---> %d", VALUE_AS_INT(entry->val));
		else if (type == TYPE_LONG) 
			printf(" ---> %ld", VALUE_AS_LONG(entry->val));
		else if (type == TYPE_FLOAT)
			printf(" ---> %f", VALUE_AS_FLOAT(entry->val));
		else if (type == TYPE_DOUBLE)
			printf(" ---> %lf", VALUE_AS_DOUBLE(entry->val));
		else if (type == TYPE_STRING)
			printf(" ---> %s", VALUE_AS_STRING(entry->val)->value);
		printf(COLORDEFAULT);
		if (entry->entry_type.is_const) {
			printf(" CONST");
		}
		putchar('\n');
	}
}
