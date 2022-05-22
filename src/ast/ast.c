/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "ast.h"
#include <string.h>

public struct ASTnode *create_ast_node(char *title, ASTnode_type type, union value val, struct type *val_type, struct ASTnode *left, 
		struct ASTnode *right, struct position pos)
{
	struct ASTnode *n = ngc_malloc(sizeof(struct ASTnode));
	n->title = strdup(title);
	n->type = type;
	n->left = left;
	n->right = right;
	pos_copy(pos, n->pos);
	struct type *entry_val_type = &n->node_val_type;
	type_copy(val_type, entry_val_type);
	set_val_by_type(&n->val, &val, val_type);
	return n;
}

public struct ASTnode *create_ast_leaf(char *title, ASTnode_type type, union value val, struct type *val_type, struct position pos)
{
	return create_ast_node(title, type, val, val_type, NULL, NULL, pos);
}

public ASTnode_type tokentype_to_nodetype(token_type type)
{
	switch (type) {
		case T_GT :
			return A_GREATER;
		case T_LT :
			return A_LOWER;
		case T_ISEQUAL :
			return A_ISEQUAL;
		case T_LOWEQ :
			return A_LOWER_EQUAL;
		case T_GREAEQ :
			return A_GREATER_EQUAL;
		case T_STAR :
			return A_MULTIPLY;
		case T_SLASH :
			return A_DIVIDE;
		case T_DASH :
			return A_MINUS;
		case T_PLUS :
			return A_ADD;
	}
	panic("Invalid token type (for convert to node type)");
	return 0;
}

public char *get_nodetype_str(ASTnode_type type)
{
	// last member of ASTnode_type enum
	if (type > ARRAY_LENGTH(ASTnode_type_str))
		return "BAD";
	return ASTnode_type_str[type];
}

public union value calculate_tree(struct ASTnode *n, int type)
{
	union value val;
	if (type == T_INT) {
		int res = (int) calculate_binary_tree(n, type);
		val.intval = res;
	} else if (type == T_LONG) {
		long res = (long) calculate_binary_tree(n, type);
		val.longval = res;
	} else if (type == T_FLOAT || type == T_DOUBLE) {
		double res = calculate_binary_tree(n, type);
		val.realval = res;
	}
	val.val_type.type = type;
	return val;
}

public double calculate_binary_tree(struct ASTnode *n, int type)
{
	double left, right;
	if (n->left)
		left = calculate_binary_tree(n->left, type);
	if (n->right)
		right = calculate_binary_tree(n->right, type);
	switch (n->type) {
		case A_ADD :
			return left + right;
		case A_MINUS :
			return left - right;
		case A_MULTIPLY :
			return left * right;
		case A_DIVIDE :
			return left / right;
		case A_CONST :
			if (type == T_INT)
				return n->val.intval;
			else if (type == T_LONG) {
				if (n->val.val_type.type == T_INT) 
					return n->val.intval;
				return n->val.longval;
			}
			else if (type == T_DOUBLE) {
				if (n->val.val_type.type == T_INT) 
					return n->val.intval;
				return n->val.realval;
			}
			else if (type == T_FLOAT) {
				if (n->val.val_type.type == T_INT) 
					return n->val.intval;
				return n->val.realval;
			}
	}
	// TODO : report but , invalid operation
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
	if (n->type == A_CONST) {
		printf(" : %d", n->val.intval);
		printf(" --> %s", get_token_str(n->val.val_type.type));
	}
	putchar('\n');
	if (n->left) {
		print_ast(n->left, depth + 4);
	}
	if (n->right) {
		print_ast(n->right, depth + 4);
	}
}
