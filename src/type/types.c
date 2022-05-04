/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "types.h"

public void set_val_by_type(union value dest, union value src, struct type *tp)
{
	if (tp->type == TK_INT) {
		dest.intval = src.intval;
	}
}