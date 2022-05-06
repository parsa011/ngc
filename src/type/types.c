/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "types.h"

public void set_val_by_type(union value *dest, union value *src, struct type *tp)
{
	switch (tp->type) {
		case T_INT :
			dest->intval = src->intval;
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
