#ifndef _TYPE_DEF_H
# define _TYPE_DEF_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*
*	Contains our types definitions
*/

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

#endif
