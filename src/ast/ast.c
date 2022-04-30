/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "ast.h"
#include <string.h>

public struct ASTnode *create_ast_node(char *title, int type, int value, struct ASTnode *left, 
		struct ASTnode *right, struct position pos)
{
	struct ASTnode *n = ngc_malloc(sizeof(struct ASTnode));
	n->title = strdup(title);
	n->type = type;
	n->left = left;
	n->right = right;
	n->integer = value;
	pos_copy(pos, n->pos);
	return n;
}

public struct ASTnode *create_ast_leaf(char *title, int type, int value, struct position pos)
{
	return create_ast_node(title, type, value, NULL, NULL, pos);
}

public ASTnode_type tokentype_to_nodetype(token_type type)
{
	switch (type) {
		case T_STAR :
			return A_MULTIPLY;
		case T_SLASH :
			return A_DIVIDE;
		case T_DASH :
			return A_MINUS;
		case T_PLUS :
			return A_ADD;
	}
	return 0;
}

public char *get_nodetype_str(ASTnode_type type)
{
	// last member of ASTnode_type enum
	if (type > A_INTLIT)
		return "BAD";
	return ASTnode_type_str[type];
}

public int calculate_binary_tree(struct ASTnode *n)
{
	int left, right;
	if (n->left)
		left = calculate_binary_tree(n->left);
	if (n->right)
		right = calculate_binary_tree(n->right);
	switch (n->type) {
		case A_ADD :
			return left + right;
		case A_MINUS :
			return left - right;
		case A_MULTIPLY :
			return left * right;
		case A_DIVIDE :
			return left / right;
		case A_INTLIT :
			return n->integer;
	}
	return -1;
}

public void print_ast(struct ASTnode *n, int depth)
{
	if (!n)
		return;
	for (int i = 0; i < depth; i++) {
		putchar(' ');
	}
	printf("%s (%d:%d)", get_nodetype_str(n->type), n->pos.line, n->pos.col);
	if (n->type == A_INTLIT) {
		printf(" : %d", n->integer);
	}
	putchar('\n');
	if (n->left) {
		print_ast(n->left, depth + 4);
	}
	if (n->right) {
		print_ast(n->right, depth + 4);
	}
}
