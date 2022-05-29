#ifndef _PARSER_H
# define _PARSER_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser_util.h"
#include "../type/types.h"
#include "../ast/ast.h"
#include "symtab.h"

/*
 *	@brief : This is entry point of parser , we will call this everwhere that we need
 *	to compiler file
 */
public ASTnode *compile(lexer *);

/*
 *	@brief : checks current token to determine what to do now
 */
private ASTnode *statements();

/*
 *	@brief : Parse Declare variable statements
 */
private ASTnode *declare_variable();

/*
 *	@brief : process and assign values to variables
 */
private ASTnode *parse_assign_variable();

/*
 *	@brief : get value by considering type kind and it's informations
 */
private ASTnode *get_rvalue_for_type(type);

/*
 *	@brief : return AST of a str expression
 */
private ASTnode *parse_str_literal();

/*
 *	@breif : return primay factor as a ASTnode tree
 */
private ASTnode *primary_factor(int, type *);

/*
 *	@brief : parse binary expression by pratt parsing algorithm
 */
private ASTnode *parse_binary_expression(int, type *);

private ASTnode *parse_if_statement();

#endif
