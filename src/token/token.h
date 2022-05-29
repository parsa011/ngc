#ifndef _TOKEN_H
# define _TOKEN_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "../ngc.h"
#include "../type/value.h"

typedef enum {
	T_EOF,

	T_PLUS, 		// +
	T_DASH,			// -
	T_STAR,			// *
	T_SLASH,		// /
	T_PERCENT,		// %
	T_PIPE,			// |
	T_PIPEPIPE,		// ||
	T_EQUAL,		// =
	T_AND,			// &
	T_ANDAND,		// &&
	T_DOT,			// .
	T_ELLIPSIS,		// ...
	T_COMMA,		// ,
	T_CARET,		// ^
	T_QUES,			// ?
	T_EXCLAM,		// !
	T_GT,			// >
	T_LT,			// <
	T_HASHTAG,		// #
	T_BSLASH,
	T_TILDE,		// ~
	T_COLON,		// :
	T_SEMI,			// ;

	T_OP_CB,		// {
	T_CL_CB,		// }
	T_OBRKT,		// [
	T_CBRKT,		// ]
	T_OP_P,			// {
	T_CL_P,			// }

	T_INC,			// ++
	T_DEC,			// --

	T_ISEQUAL,		// ==
	T_INCEQUAL,		// +=
	T_DECEQUAL,		// -=
	T_MUEQUAL,		// *=
	T_MODEQUAL,		// %=
	T_GREAEQ,		// >=
	T_LOWEQ,		// <=
	T_SHLEQUAL,		// <<=
	T_SHREQUAL,		// >>=
	T_DIVEQUAL,		// /=
	T_NOTEQUAL,		// !=
	T_ANDEQUAL,		// &=
	T_OREQUAL,		// |=
	T_XOREQUAL,		// ^=
	T_SHIFT_L,		// <<
	T_SHIFT_R,		// >>
	
	T_DO,
	T_WHILE,
	T_FOR,
	T_IF,
	T_ELSE,
	T_ENUM,
	T_STRUCT,
	T_UNION,
	T_AUTO,
	T_BREAK,
	T_CONTINUE,
	T_DEFAULT,
	T_SWITCH,
	T_CASE,
	T_VOLATILE,
	T_CONST,
	T_SIGNED,
	T_UNSIGNED,
	T_STATIC,
	T_EXTERN,
	T_GOTO,
	T_RETURN,
	T_SIZEOF,
	T_REGISTER,
	T_TYPEDEF,
	T_RESTRICT,
	T_LABEL,

	T_INT,
	T_CHAR,
	T_VOID,
	T_DOUBLE,
	T_FLOAT,
	T_LONG,

	T_STRLIT,		 // "string"
	T_DOUBLELIT,	 // 1.13
	T_FLOATLIT,	     // 1.13
	T_INTLIT,		 // 123
	T_LONGLIT,		 // 123
	T_OCTALLIT,		 // 012
	T_HEXLIT,		 // 0x123
	T_BINLIT,		 //	0b123 
	T_CHARLIT,		 // 'c'

	T_IDENT,

	T_NEWLINE,

	T_BAD
} token_type;

// TODO : Create Dictionary-Like struct for this
private char *token_type_str[] = {
	"T_EOF",

	"T_PLUS", 		// +
	"T_DASH",		// -
	"T_STAR",		// *
	"T_SLASH",		// /
	"T_PERCENT",	// %
	"T_PIPE",		// |
	"T_PIPEPIPE",	// ||
	"T_EQUAL",		// =
	"T_AND",		// &
	"T_ANDAND",		// &&
	"T_DOT",		// .
	"T_ELLIPSIS",	// ...
	"T_COMMA",		// ,
	"T_CARET",		// ^
	"T_QUES",		// ?
	"T_EXCLAM",		// !
	"T_GT",			// >
	"T_LT",			// <
	"T_HASHTAG",	// #
	"T_BSLASH",	
	"T_TILDE",		// ~
	"T_COLON",		// :
	"T_SEMI",		// ;

	"T_OP_CB",		// {
	"T_CL_CB",		// }
	"T_OBRKT",		// [
	"T_CBRKT",		// ]
	"T_OP_P",		// (
	"T_CP_P",		// )

	"T_INC",			// ++
	"T_DEC",			// --

	"T_ISEQUAL",		// ==
	"T_INCEQUAL",		// +=
	"T_DECEQUAL",		// -=
	"T_MUEQUAL",		// *=
	"T_MODEQUAL",		// %=
	"T_GREAEQ",			// >=
	"T_LOWEQ",			// <=
	"T_SHLEQUAL",		// <<=
	"T_SHREQUAL",		// >>=
	"T_DIVEQUAL",		// /=
	"T_NOTEQUAL",		// !=
	"T_ANDEQUAL",		// &=
	"T_OREQUAL",		// |=
	"T_XOREQUAL",		// ^=
	"T_SHIFT_L",		// <<
	"T_SHIFT_R",		// >>

	"T_DO",
	"T_WHILE",
	"T_FOR",
	"T_IF",
	"T_ELSE",
	"T_ENUM",
	"T_STRUCT",
	"T_UNION",
	"T_AUTO",
	"T_BREAK",
	"T_CONTINUE",
	"T_DEFAULT",
	"T_SWITCH",
	"T_CASE",
	"T_VOLATILE",
	"T_CONST",
	"T_SIGNED",
	"T_UNSIGNED",
	"T_STATIC",
	"T_EXTERN",
	"T_GOTO",
	"T_RETURN",
	"T_SIZEOF",
	"T_REGISTER",
	"T_TYPEDEF",
	"T_RESTRICT",
	"T_LABEL",

	"T_INT",
	"T_CHAR",
	"T_VOID",
	"T_DOUBLE",
	"T_FLOAT",
	"T_LONG",

	"T_STRLIT",		 // "string"
	"T_DOUBLELIT",	 // 1.23
	"T_FLOATLIT",	 // 1.23
	"T_INTLIT",		 // 123
	"T_LONGLIT",	 // 123
	"T_OCTALLIT",	 // 012
	"T_HEXLIT",		 // 0x123
	"T_BINLIT",		 //	0b123 
	"T_CHARLIT",	 // 'c'

	"T_IDENT",

	"T_NEWLINE",

	"T_BAD"
};

#define TOKEN_BUF_SIZE 64 

typedef struct token_t {
	token_type type;
	struct position pos;
	char buffer[TOKEN_BUF_SIZE];
	int bufp;
	value val;
} token;

/*
 *	@brief : return Token string from token_type_str array , panic if token id was not valid
 */
public char *get_token_str(int);

/*
 *	@brief : create and return new token
 *	> dont forget to make token free after use :)
 */
public token *token_init(token_type type);

/*
 *	@brief : make a duplicate of given token
 */
public token *token_duplicate(token *);

/*
 *	@brief : free given token
 */
public void token_free(token *);

/*
 *	@brief : return precedenf of given token type
 */
public int token_precedence(token_type);

/*
 *	@brief : return keyword type related to given string , return T_IDENT if given char was not keyword
 */
public token_type guess_text_type(char *);

/*
 *	@brief : print token with data and ...
 */
public void print_token(token *);

/*
 *	@brief : return precedence of given token type, (token should be an operator)
 */
public int token_precedence(token_type);

/*
 *	@brief : return true if given token type is a variable type
 */
public bool is_type_token(token_type);

/*
 *	@brief : return true if token is assign token 
 */
public bool is_assign_token(token_type);

#endif
