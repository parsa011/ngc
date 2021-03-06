#ifndef _PARSER_UTIL_H
# define _PARSER_UTIL_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*
*	Some utily functions for parser like match token and ...
*/

#include "../ngc.h"
#include "../lexer/lexer.h"
#include "../type/types.h"
#include "../ast/ast.h"
#include "symtab.h"

/*
 *	this is like our lexer, it will point to our working lexer , so we can have access
 *	to lexer taht we are working with , in all parsing function
 */
public lexer *current_lexer;

#define next_token() (lex())
#define current_token (current_lexer->tok)
#define PRINT_TOK()   (print_token(&current_token))

/*
 *	@brief : set working lexer to given lexer, and also activate given lexer in lexer phase
 *	by calling lexer_set_working_lexer()
 */
public void select_lexer(lexer *);

/*
 *	@brief : check if current token type is equals to given type , if is's not , will print
 *	given message to output
 */
public void match(token_type, char *);

/*
 *	@brief : check if current token type equals to T_EOF
 */
public bool is_eof();

/*
 *	@brief : checks if current token is a keyword of types like int, float and....
 *	takes a boolean to check if need to call next token or no
 */
public bool is_type_keyword(bool);

/*
 *	@brief : checks if current token is const or volatile (a qualifier)
 */
public bool is_qualifier(bool);

/*
 *	@brief : checks if current token is end of a binary expression or no
 *	token should be something like semicolon or comm or ...
 */
public bool is_endof_expression();

/*
 *	@brief : Skip tokens , until we take something with given token type
 */
public void skip_token_until(token_type);

/*
 *	@brief : check if current token is semicolon , it will use match with some default args to check , nothing  more :)
 */
public void semi();

public void left_paren();
public void right_paren();

/*
 *	@brief : Check is current token is assign token or (assign token like = , += and ...)
 */
public void assign_token();

/*
 *	just check if current_token type is equal to tp
 */
public bool token_is(token_type tp);

#endif
