/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "ast.h"

struct ASTnode *create_ast_node(int type, struct ASTnode *left, struct ASTnode *right, struct position pos)
{
	struct ASTnode *n = ngc_malloc(sizeof(struct ASTnode));
	n->type = type;
	n->left = left;
	n->right = right;
	pos_copy(pos, n->pos);
	return n;
}

struct ASTnode *create_ast_leaf(int type, struct position pos)
{
	return create_ast_node(type, NULL, NULL, pos);
}
