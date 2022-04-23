#ifndef _AST_H
# define _AST_H
/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "../ngc.h"

struct ASTnode {
	char *title;
	int type;
	struct ASTnode *left;
	struct ASTnode *right;
	struct position pos;
	union {
		string *str;
		double real;
		int integer;
	};
};

/*
 *	@brief : This routine will create new instance of ast node
 *	but we dont set value here , you should set value after creating new one
 */
struct ASTnode *create_ast_node(char *, int, struct ASTnode *, struct ASTnode *, struct position);

/*
 *	@brief : create a left for abstract syntax tree
 *	leaf can be something like variables that are defined everywhere 
 *	like in function or in list of function arguments
 */
struct ASTnode *create_ast_leaf(char *, int, struct position);

#endif
