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

#define INT_VAL(val)    ((value) {.intval = val})
#define LONG_VAL(val)   ((value) {.longval = val})
#define CHAR_VAL(val)   ((value) {.charval = val})
#define STR_VAL(val)    ((value) {.str = val})
#define DOUBLE_VAL(val) ((value) {.doubleval = val})
#define FLOAT_VAL(val)  ((value) {.floatval = val})

#define IS_INT_VAL(val_type)     (val_type == VALUE_INT)
#define IS_LONG_VAL(val_type)    (val_type == VALUE_LONG)
#define IS_DOUBLE_VAL(val_type)  (val_type == VALUE_DOUBLE)
#define IS_FLOAT_VAL(val_type)   (val_type == VALUE_FLOAT)
#define IS_STRING_VAL(val_type)  (val_type == VALUE_STRING)
#define IS_CHAR_VAL(val_type)    (val_type == VALUE_CHAR)

static void print_value(value val)
{
	switch (val.type) {
		case VALUE_INT :
			printf("%d", VALUE_AS_INT(val));
			break;
	   	case VALUE_LONG :
			printf("%ld", VALUE_AS_LONG(val));
			break;
	   	case VALUE_DOUBLE :
			printf("%lf", VALUE_AS_DOUBLE(val));
			break;
	   	case VALUE_FLOAT :
			printf("%f", VALUE_AS_FLOAT(val));
			break;
	   	case VALUE_CHAR :
			printf("%s", VALUE_AS_CHAR(val)->value);
			break;
	   	case VALUE_STRING :
			printf("%s", VALUE_AS_STRING(val)->value);
			break;
	}
	putchar('\n');
}


#endif
