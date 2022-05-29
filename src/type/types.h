#ifndef _TYPES_H
# define _TYPES_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "../ngc.h"
#include "value.h"
#include "../token/token.h"

/*
 *	@brief : set value of dest by considering tp
 */
public void set_val_by_type(value *, value *, token_type);

/*
 *	@brief : checks if given token type (given token type should be a lietral token_type) is Equivalent to type
 *	for example for a double type , we can have real lietrals or for a int we can have char or int and ...
 */
public bool check_literal_and_type(token *, type *);

#endif
