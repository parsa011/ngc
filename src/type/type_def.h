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

typedef enum {
	TYPE_INT,
	TYPE_LONG,
	TYPE_DOUBLE,
	TYPE_FLOAT,
	TYPE_STRING,
	TYPE_CHAR
} type_kind;

/*
 *	basic struct of our types , it shows qualifiers and other things
 *	related to the type
 */
typedef struct {
	type_kind type;
	bool is_unsigned;
	bool is_const;
	bool is_volatile;
	bool is_restrict;
	bool is_pointer;
} type;
#define type_copy(src, dest) { \
	dest->type = src->type; \
	dest->is_unsigned = src->is_unsigned; \
	dest->is_const = src->is_const; \
	dest->is_volatile = src->is_volatile; \
	dest->is_restrict = src->is_restrict; \
	dest->is_pointer = src->is_pointer; \
}

#define INT_TYPE()    ((type) {.type = TYPE_INT})
#define LONG_TYPE()   ((type) {.type = TYPE_LONG})
#define DOUBLE_TYPE() ((type) {.type = TYPE_DOUBLE})
#define FLOAT_TYPE()  ((type) {.type = TYPE_FLOAT})
#define STRING_TYPE() ((type) {.type = TYPE_STRING})
#define CHAR_TYPE()   ((type) {.type = TYPE_CHAR})

#define IS_CONST_TYPE(type) (type.is_const)


#endif
