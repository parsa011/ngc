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

/* values are valid to have this types
 * these are literals , not tokens or .... , like :
 * 		1212 : int
 * 		1e2  : long
 * 	and ...
 */
typedef enum value_type {
	VALUE_INT,
	VALUE_LONG,
	VALUE_DOUBLE,
	VALUE_FLOAT,
	VALUE_STRING,
	VALUE_CHAR
} value_type;

static const char *value_type_str[] = {
	"VALUE_INT",
	"VALUE_LONG",
	"VALUE_DOUBLE",
	"VALUE_FLOAT",
	"VALUE_STRING",
	"VALUE_CHAR"
};

static const char *get_valyetype_str(value_type tp)
{
	return value_type_str[tp];
}

/*
 *	value union is used for everwhere that need to store input data , such as tokens or abstract syntax tree and symbol table
 *	they can have different type of data, so they should be possible to store every kind of data.
 */
typedef struct value_t {
	value_type type;
	union {
		string *str;
		double doubleval;
		float floatval;
		int intval;
		long longval;
		char charval;
	};
} value;

#define VALUE_AS_INT(val)    (val.intval)
#define VALUE_AS_LONG(val)   (val.longval)
#define VALUE_AS_DOUBLE(val) (val.doubleval)
#define VALUE_AS_FLOAT(val)  (val.floatval)
#define VALUE_AS_STRING(val) (val.str)
#define VALUE_AS_CHAR(val)   (val.str)        /* this is just for code readability */

#define INT_VAL(value)  ((value) {.intval = value})
#define LONG_VAL(value) ((value) {.longval = value})
#define CHAR_VAL(value) ((value) {.charval = value})
#define REAL_VAL(value) ((value) {.realval = value})

#endif
