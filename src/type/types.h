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
#include "../token/token.h"

//typedef enum {
//	TK_INT = T_INT,
//	TK_FLOAT = T_FLOAT,
//	TK_REAL = T_DOUBLE,
//	TK_LONG = T_LONG,
//	TK_STRING = T_STRLIT,
//	TK_CHAR = T_CHAR
//} type_kind;

/*
 *	basic struct of our types , it shows qualifiers and other things
 *	related to the type
 */
struct type {
	int type;
	bool is_unsigned;
	bool is_const;
	bool is_volatile;
	bool is_restrict;
	bool is_pointer;
};
#define type_copy(src, dest) { \
	dest->type = src->type; \
	dest->is_unsigned = src->is_unsigned; \
	dest->is_const = src->is_const; \
	dest->is_volatile = src->is_volatile; \
	dest->is_restrict = src->is_restrict; \
	dest->is_pointer = src->is_pointer; \
}

/*
 *	@brief : set value of dest by considering tp
 */
public void set_val_by_type(union value *, union value *, struct type *);

/*
 *	@brief : checks if given token type (given token type should be a lietral token_type) is Equivalent to type
 *	for example for a double type , we can have real lietrals or for a int we can have char or int and ...
 */
public bool check_literal_and_type(struct token *, struct type *);

#endif
