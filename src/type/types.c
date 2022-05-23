/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "types.h"
#include "../parser/symtab.h"

public void set_val_by_type(value *dest, value *src, token_type operation_type)
{
#define SET_VAL(dest, src, op) \
	do { \
		if (op == T_INCEQUAL) { \
			dest += src; \
		} else if (op == T_EQUAL) { \
			dest = src; \
		}\
	} while (false);

	struct type *src_type = &src->val_type;
	struct type *dest_type = &dest->val_type;
	type_copy(src_type, dest_type);

	switch (src->val_type.type) {
		case T_INT :
			SET_VAL(dest->val.intval, src->val.intval, operation_type);
			break;

		case T_LONG :
			SET_VAL(dest->val.longval, src->val.longval, operation_type);
			break;

		case T_FLOAT :
		case T_DOUBLE :
			SET_VAL(dest->val.realval, src->val.realval, operation_type);
			break;

		case T_STRLIT :
		case T_CHAR :
			break;
	}
#undef SET_VAL
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
						struct symtab_entry *entry = symtab_get_by_name(tok->buffer, true);
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
