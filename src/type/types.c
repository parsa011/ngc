/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "types.h"
#include "../parser/symtab.h"

public void set_val_by_type(union value *dest, union value *src, struct type *tp)
{
	switch (tp->type) {
		case T_INT :
			dest->intval = src->intval;
			break;

		case T_LONG :
			dest->longval = src->longval;
			break;

		case T_FLOAT :
		case T_DOUBLE :
			dest->realval = src->realval;
			break;

		case T_STRLIT :
		case T_CHAR :
			dest->str = src->str;
			break;
	}
}


public bool check_literal_and_type(struct token *tok, struct type *tp)
{
	switch (tp->type) {
		case T_INT :
		case T_LONG :
			switch (tok->type) {

				case T_INTLIT :
				case T_LONGLIT :
				case T_CHARLIT :
					return true;

				case T_IDENT :
					{
						struct symtab_entry *entry = symtab_get_by_name(tok->buffer);
						if (symbol_entry_type(entry) == T_INT || symbol_entry_type(entry) == T_CHAR)
							return true;
					}
			}
			return false;

		case T_CHAR :
			if (tp->is_pointer && tok->type == T_STRLIT)
				return true;
		
		case T_FLOAT :
		case T_DOUBLE :
			return (tok->type == T_CHARLIT || tok->type == T_INTLIT || tok->type == T_REALLIT);
	}
}
