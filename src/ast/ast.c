/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "ast.h"
#include <string.h>

public ASTnode *create_ast_node(char *title, ASTnode_type type, value val, ASTnode *left, ASTnode *right, struct position pos)
{
	ASTnode *n = ngc_malloc(sizeof(ASTnode));
	n->title = strdup(title);
	n->type = type;
	n->left = left;
	n->right = right;
	pos_copy(pos, n->pos);
	//type *entry_node_type = &n->node_type_type;
	//type_copy(node_type, entry_node_type);
	set_val_by_type(&n->val, &val, T_EQUAL);
	return n;
}

public ASTnode *create_ast_leaf(char *title, ASTnode_type type, value val, struct position pos)
{
	return create_ast_node(title, type, val, NULL, NULL, pos);
}

// TODO
public void ast_free(ASTnode *n)
{

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
	if (type > ARRAY_LENGTH(ASTnode_type_str))
		return "BAD";
	return ASTnode_type_str[type];
}

public value calculate_tree(ASTnode *n, type_kind type)
{
	value val;
	if (type == TYPE_INT) {
		int res = (int) calculate_binary_tree(n, type);
		val.type = VALUE_INT;
		val.intval = res;
	} else if (type == TYPE_LONG) {
		long res = (long) calculate_binary_tree(n, type);
		val.type = VALUE_LONG;
		val.longval = res;
	} else if (type == TYPE_DOUBLE) {
		double res = calculate_binary_tree(n, type);
		val.type = VALUE_DOUBLE;
		val.doubleval = res;
	} else if (type == TYPE_FLOAT) {
		double res = calculate_binary_tree(n, type);
		val.type = VALUE_FLOAT;
		val.floatval = (float) res;
	} else if (type == TYPE_STRING || TYPE_CHAR) {
    	val.type = VALUE_STRING;
    	// TODO : string concant and ...
        val.str = process_string_tree(n);
	}
	return val;
}

public string *process_string_tree(ASTnode *tree)
{
	string *str = prosing_string_init(tree->val.str->value);
	if (tree->left == NULL) {
		return str;
	}
	string *left_str = process_string_tree(tree->left);
	prosing_string_append(left_str, str->value);
	prosing_string_free(str);
	return left_str;
}

public double calculate_binary_tree(ASTnode *n, value_type type)
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
		case A_GREATER :
			return left > right;
		case A_LOWER :
			return left < right;
		case A_LOWER_EQUAL :
			return left <= right;
		case A_GREATER_EQUAL :
			return left >= right;
		case A_CONST :
			{
				int val_type = n->val.type;
				if (type == VALUE_INT) {
					return VALUE_AS_INT(n->val);
				}
				else if (type == VALUE_LONG) {
					if (val_type == VALUE_INT) 
						return VALUE_AS_INT(n->val);
					return VALUE_AS_LONG(n->val);
				}
				else if (type == VALUE_DOUBLE) {
					if (val_type == VALUE_INT) 
						return VALUE_AS_INT(n->val);
					else if (val_type == VALUE_LONG)
						return (double) VALUE_AS_LONG(n->val);
					else if (val_type == VALUE_FLOAT)
						return VALUE_AS_FLOAT(n->val);
					return VALUE_AS_DOUBLE(n->val);
				}
				else if (type == VALUE_FLOAT) {
					if (val_type == VALUE_INT) 
						return VALUE_AS_INT(n->val);
					return VALUE_AS_FLOAT(n->val);
				}
			}
	}
	panic("Invalid Or Not-Implemented operation");
	return -1;
}

public void print_ast(ASTnode *n, int depth)
{
	if (!n)
		return;
	for (int i = 0; i < depth; i++) {
		putchar(' ');
	}
	printf("%s (%d:%d)", get_nodetype_str(n->type), n->pos.line, n->pos.col);

	if (n->type == A_CONST) {
		printf(" : ");
		int val_type = n->val.type;

		if (val_type == VALUE_INT)
			printf("%d", VALUE_AS_INT(n->val));
		else if (val_type == VALUE_LONG)
			printf("%ld", VALUE_AS_LONG(n->val));
		else if (val_type == VALUE_FLOAT || val_type == VALUE_LONG)
			printf("%f", val_type == VALUE_DOUBLE ? VALUE_AS_DOUBLE(n->val) : VALUE_AS_FLOAT(n->val));

	} else if (n->type == A_STR)
		printf("%s", VALUE_AS_STRING(n->val)->value);

	putchar('\n');
	if (n->left) {
		print_ast(n->left, depth + 4);
	}
	if (n->right) {
		print_ast(n->right, depth + 4);
	}
}
