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
 *	TODO : Impelement
 */
public void symtab_create_integer(char *text, int value)
{

}
