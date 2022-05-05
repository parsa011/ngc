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
		case TK_INT :
			dest->intval = src->intval;
			break;

		case TK_FLOAT :
			dest->realval = src->realval;
			printf("%f\n", dest->realval);
			break;

	}
}