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
public struct ASTnode *compile(struct lexer *);

/*
 *	@brief : checks current token to determine what to do now
 */
private struct ASTnode *statements();

/*
 *	@brief : Parse Declare variable statements
 */
private struct ASTnode *declare_variable();

/*
 *	@brief : process and assign values to variables
 */
private struct ASTnode *parse_assign_variable();

/*
 *	@brief : get value by considering type kind and it's informations
 */
private struct ASTnode *get_rvalue_for_type(token_type, struct type);

/*
 *	@brief : return AST of a char expression
 */
private struct ASTnode *parse_char_literal();

/*
 *	@breif : return primay factor as a ASTnode tree
 */
private struct ASTnode *primary_factor(int, struct type *);

/*
 *	@brief : parse binary expression by pratt parsing algorithm
 */
private struct ASTnode *parse_binary_expression(int, struct type *);

private struct ASTnode *parse_if_statement();

#endif
