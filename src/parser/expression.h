#ifndef _EXPRESSION_H
# define _EXPRESSION_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "parser_util.h"

/*
 *	@breif : return primay factor as a ASTnode tree
 */
public ASTnode *primary_factor(int ptp);

/*
 *	@brief : parse expression by pratt parsing algorithm
 */
public ASTnode *parse_expression(int ptp);

/*
 *	@brief : assign a value to variable or ...
 *	@grammer :
 *		
 *		assignment-expression ::= conditional-expression
 *								| unary-expression assignment-operator assignment-expression
 */
public ASTnode *parse_assignment_expression(); 

#endif
