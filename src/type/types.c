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

	dest->type = src->type;

	switch (src->type) {
		case VALUE_INT :
			SET_VAL(dest->intval, src->intval, operation_type);
			break;

		case VALUE_LONG :
			SET_VAL(dest->longval, src->longval, operation_type);
			break;
		
		case VALUE_DOUBLE :
			SET_VAL(dest->doubleval, src->doubleval, operation_type);
			break;

		case VALUE_FLOAT :
			SET_VAL(dest->floatval, src->floatval, operation_type);
			break;

		case VALUE_STRING :
		case VALUE_CHAR :
			if (operation_type == T_INCEQUAL) {
				prosing_string_append(dest->str, src->str->value);
			} else if (operation_type == T_EQUAL)
				dest->str = src->str;
			else
				// TODO : show bad operation on string here
				panic("ERROR");
			break;
	}
#undef SET_VAL
}

public type_kind token_type_to_type_kind(token_type tp)
{
	switch (tp) {
		case T_INT :
			return TYPE_INT;
		case T_LONG :
			return TYPE_LONG;
		case T_DOUBLE :
			return TYPE_DOUBLE;
		case T_FLOAT :
			return TYPE_FLOAT;
		case T_CHAR :
			return TYPE_CHAR;
	}
}

public bool check_literal_and_type(token *tok, type *tp)
{
	if (tok->type == T_IDENT) {
		/* Find entry if given token is identifier token
		 */
		symtab_entry *entry = symtab_get_by_name(tok->buffer, true);
		if (!entry) {
			// TODO : BUG
			panic("NOT FOUND");
		}
		/* Convert type to it literal by hand to create token
		 */
		token_type tok_type;
		if (entry->entry_type.type == TYPE_INT)
			tok_type = T_INTLIT;
		else if (entry->entry_type.type == TYPE_LONG)
				tok_type = T_LONGLIT;
		else if (entry->entry_type.type == TYPE_DOUBLE)
			tok_type = T_DOUBLELIT;
		else if (entry->entry_type.type == TYPE_FLOAT)
			tok_type = T_FLOATLIT;
		else if (entry->entry_type.type == TYPE_CHAR)
			tok_type = T_CHARLIT;
		else if (entry->entry_type.type == TYPE_STRING)
			tok_type = T_STRLIT;
		/* create fake token to pass into check_literal_and_type()
		 * so in this case we don't need to get identifier for each type
		 */
		token *fake_token = token_init(tok_type);
		return check_literal_and_type(fake_token, tp);
	}
	switch (tp->type) {

		case TYPE_INT :
		case TYPE_LONG :
			return tok->type == T_INTLIT || tok->type == T_LONGLIT || tok->type == T_CHARLIT;

    	case TYPE_CHAR :
    	    if (tok->type == T_STRLIT && tp->is_pointer)
        	    return true;
    	    return tok->type == T_CHARLIT;
		
		case TYPE_FLOAT :
		case TYPE_DOUBLE :
			return (tok->type == T_CHARLIT || tok->type == T_INTLIT || tok->type == T_DOUBLELIT || tok->type == T_FLOATLIT);

	}
}
