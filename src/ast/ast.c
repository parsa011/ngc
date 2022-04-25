/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "ast.h"

public struct ASTnode *create_ast_node(char *title, int type, struct ASTnode *left, struct ASTnode *right, struct position pos)
{
	struct ASTnode *n = ngc_malloc(sizeof(struct ASTnode));
	n->title = title;
	n->type = type;
	n->left = left;
	n->right = right;
	pos_copy(pos, n->pos);
	return n;
}

public struct ASTnode *create_ast_leaf(char *title, int type, struct position pos)
{
	return create_ast_node(title, type, NULL, NULL, pos);
}

// TODO : Implement
public void print_ast(struct ASTnode *tree)
{
	
}
