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
	TOKEN_EOF,

	TOKEN_PLUS, 		// +
	TOKEN_DASH,			// -
	TOKEN_STAR,			// *
	TOKEN_SLASH,		// /
	TOKEN_PERCENT,		// %
	TOKEN_PIPE,			// |
	TOKEN_PIPEPIPE,		// ||
	TOKEN_EQUAL,		// =
	TOKEN_AND,			// &
	TOKEN_ANDAND,		// &&
	TOKEN_DOT,			// .
	TOKEN_ELLIPSIS,		// ...
	TOKEN_COMMA,		// ,
	TOKEN_CARET,		// ^
	TOKEN_QUES,			// ?
	TOKEN_EXCLAM,		// !
	TOKEN_GT,			// >
	TOKEN_LT,			// <
	TOKEN_HASHTAG,		// #
	TOKEN_BSLASH,
	TOKEN_TILDE,		// ~
	TOKEN_COLON,		// :
	TOKEN_SEMI,			// ;

	TOKEN_OP_CB,		// {
	TOKEN_CL_CB,		// }
	TOKEN_OBRKT,		// [
	TOKEN_CBRKT,		// ]
	TOKEN_OP_P,			// {
	TOKEN_CL_P,			// }

	TOKEN_INC,			// ++
	TOKEN_DEC,			// --

	TOKEN_ISEQUAL,		// ==
	TOKEN_INCEQUAL,		// +=
	TOKEN_DECEQUAL,		// -=
	TOKEN_MUEQUAL,		// *=
	TOKEN_MODEQUAL,		// %=
	TOKEN_GREAEQ,		// >=
	TOKEN_LOWEQ,		// <=
	TOKEN_SHLEQUAL,		// <<=
	TOKEN_SHREQUAL,		// >>=
	TOKEN_DIVEQUAL,		// /=
	TOKEN_NOTEQUAL,		// !=
	TOKEN_ANDEQUAL,		// &=
	TOKEN_OREQUAL,		// |=
	TOKEN_XOREQUAL,		// ^=
	TOKEN_SHIFT_L,		// <<
	TOKEN_SHIFT_R,		// >>
	
	TOKEN_DO,
	TOKEN_WHILE,
	TOKEN_FOR,
	TOKEN_IF,
	TOKEN_ELSE,
	TOKEN_ENUM,
	TOKEN_STRUCT,
	TOKEN_UNION,
	TOKEN_AUTO,
	TOKEN_BREAK,
	TOKEN_CONTINUE,
	TOKEN_DEFAULT,
	TOKEN_SWITCH,
	TOKEN_CASE,
	TOKEN_VOLATILE,
	TOKEN_CONST,
	TOKEN_SIGNED,
	TOKEN_UNSIGNED,
	TOKEN_STATIC,
	TOKEN_EXTERN,
	TOKEN_GOTO,
	TOKEN_RETURN,
	TOKEN_SIZEOF,
	TOKEN_REGISTER,
	TOKEN_TYPEDEF,
	TOKEN_RESTRICT,
	TOKEN_LABEL,

	TOKEN_INT,
	TOKEN_CHAR,
	TOKEN_VOID,
	TOKEN_DOUBLE,
	TOKEN_FLOAT,
	TOKEN_LONG,

	TOKEN_STRLIT,		 // "string"
	TOKEN_DOUBLELIT,	 // 1.13
	TOKEN_FLOATLIT,	     // 1.13
	TOKEN_INTLIT,		 // 123
	TOKEN_LONGLIT,		 // 123
	TOKEN_OCTALLIT,		 // 012
	TOKEN_HEXLIT,		 // 0x123
	TOKEN_BINLIT,		 //	0b123 
	TOKEN_CHARLIT,		 // 'c'

	TOKEN_IDENT,
#if NGC_DEBUG
	TOKEN_PRINT,
#endif

	TOKEN_NEWLINE,

	TOKEN_BAD
} token_type;

// TODO : Create Dictionary-Like struct for this
private char *token_type_str[] = {
	"TOKEN_EOF",

	"TOKEN_PLUS", 		// +
	"TOKEN_DASH",		// -
	"TOKEN_STAR",		// *
	"TOKEN_SLASH",		// /
	"TOKEN_PERCENT",	// %
	"TOKEN_PIPE",		// |
	"TOKEN_PIPEPIPE",	// ||
	"TOKEN_EQUAL",		// =
	"TOKEN_AND",		// &
	"TOKEN_ANDAND",		// &&
	"TOKEN_DOT",		// .
	"TOKEN_ELLIPSIS",	// ...
	"TOKEN_COMMA",		// ,
	"TOKEN_CARET",		// ^
	"TOKEN_QUES",		// ?
	"TOKEN_EXCLAM",		// !
	"TOKEN_GT",			// >
	"TOKEN_LT",			// <
	"TOKEN_HASHTAG",	// #
	"TOKEN_BSLASH",	
	"TOKEN_TILDE",		// ~
	"TOKEN_COLON",		// :
	"TOKEN_SEMI",		// ;

	"TOKEN_OP_CB",		// {
	"TOKEN_CL_CB",		// }
	"TOKEN_OBRKT",		// [
	"TOKEN_CBRKT",		// ]
	"TOKEN_OP_P",		// (
	"TOKEN_CP_P",		// )

	"TOKEN_INC",			// ++
	"TOKEN_DEC",			// --

	"TOKEN_ISEQUAL",		// ==
	"TOKEN_INCEQUAL",		// +=
	"TOKEN_DECEQUAL",		// -=
	"TOKEN_MUEQUAL",		// *=
	"TOKEN_MODEQUAL",		// %=
	"TOKEN_GREAEQ",			// >=
	"TOKEN_LOWEQ",			// <=
	"TOKEN_SHLEQUAL",		// <<=
	"TOKEN_SHREQUAL",		// >>=
	"TOKEN_DIVEQUAL",		// /=
	"TOKEN_NOTEQUAL",		// !=
	"TOKEN_ANDEQUAL",		// &=
	"TOKEN_OREQUAL",		// |=
	"TOKEN_XOREQUAL",		// ^=
	"TOKEN_SHIFT_R",		// >>
	"TOKEN_SHIFT_L",		// <<

	"TOKEN_DO",
	"TOKEN_WHILE",
	"TOKEN_FOR",
	"TOKEN_IF",
	"TOKEN_ELSE",
	"TOKEN_ENUM",
	"TOKEN_STRUCT",
	"TOKEN_UNION",
	"TOKEN_AUTO",
	"TOKEN_BREAK",
	"TOKEN_CONTINUE",
	"TOKEN_DEFAULT",
	"TOKEN_SWITCH",
	"TOKEN_CASE",
	"TOKEN_VOLATILE",
	"TOKEN_CONST",
	"TOKEN_SIGNED",
	"TOKEN_UNSIGNED",
	"TOKEN_STATIC",
	"TOKEN_EXTERN",
	"TOKEN_GOTO",
	"TOKEN_RETURN",
	"TOKEN_SIZEOF",
	"TOKEN_REGISTER",
	"TOKEN_TYPEDEF",
	"TOKEN_RESTRICT",
	"TOKEN_LABEL",

	"TOKEN_INT",
	"TOKEN_CHAR",
	"TOKEN_VOID",
	"TOKEN_DOUBLE",
	"TOKEN_FLOAT",
	"TOKEN_LONG",

	"TOKEN_STRLIT",		 // "string"
	"TOKEN_DOUBLELIT",	 // 1.23
	"TOKEN_FLOATLIT",	 // 1.23
	"TOKEN_INTLIT",		 // 123
	"TOKEN_LONGLIT",	 // 123
	"TOKEN_OCTALLIT",	 // 012
	"TOKEN_HEXLIT",		 // 0x123
	"TOKEN_BINLIT",		 //	0b123 
	"TOKEN_CHARLIT",	 // 'c'

	"TOKEN_IDENT",
#if NGC_DEBUG
	"TOKEN_PRINT",
#endif

	"TOKEN_NEWLINE",

	"TOKEN_BAD"
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
 *	dont forget to make token free after use :)
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
 *	@brief : return keyword type related to given string , return TOKEN_IDENT if given char was not keyword
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
