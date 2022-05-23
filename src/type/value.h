#ifndef _VALUE_H
# define _VALUE_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "../ngc.h"
#include "type_def.h"

/*
 *	value union is used for everwhere that need to store input data , such as tokens or abstract syntax tree and symbol table
 *	they can have different type of data, so they should be possible to store everykind of data.
 *	but for using it , they should have a type field to store their data type
 */
typedef struct value_t {
	struct type val_type;
	union {
		string *str;
		double realval;
		int intval;
		long longval;
		char charval;
	} val;
} value;

#define VALUE_AS_INT(val)  (val->intval)
#define VALUE_AS_LONG(val) (val->longval)
#define VALUE_AS_CHAR(val) (val->charval)
#define VALUE_AS_REAL(val) (val->realval)

#define INT_VAL(value)  ((union value) {.intval = value})
#define LONG_VAL(value) ((union value) {.longval = value})
#define CHAR_VAL(value) ((union value) {.charval = value})
#define REAL_VAL(value) ((union value) {.realval = value})

#endif
