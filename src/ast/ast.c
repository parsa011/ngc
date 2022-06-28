/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "ast.h"
#include "../lexer/lexer.h"
#include <string.h>

public ASTnode *create_ast_node(char *title, ASTnode_type type, value val, ASTnode *left, ASTnode *right, struct position pos)
{
	ASTnode *n = ngc_malloc(sizeof(ASTnode));
	n->title = strdup(title);
	n->type = type;
	n->left = left;
	n->right = right;
	pos_copy(pos, n->pos);
	set_val_by_type(&n->val, &val, TOKEN_EQUAL);
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
		case TOKEN_ANDAND :
			return A_AND;
		case TOKEN_PIPEPIPE :
			return A_OR;
		case TOKEN_GT :
			return A_GREATER;
		case TOKEN_LT :
			return A_LOWER;
		case TOKEN_ISEQUAL :
			return A_ISEQUAL;
	    case TOKEN_NOTEQUAL :
	        return A_NOTEQUAL;
		case TOKEN_LOWEQ :
			return A_LOWER_EQUAL;
		case TOKEN_GREAEQ :
			return A_GREATER_EQUAL;
		case TOKEN_STAR :
			return A_MULTIPLY;
		case TOKEN_SLASH :
			return A_DIVIDE;
		case TOKEN_DASH :
			return A_MINUS;
		case TOKEN_PLUS :
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

public value calculate_tree(ASTnode *n, type tp)
{
	value val;
	if (IS_INT_TYPE(tp.type)) {
		int res = (int) process_binary_tree(n, tp);
		val.type = VALUE_INT;
		val.intval = res;
	} else if (IS_LONG_TYPE(tp.type)) {
		long res = (long) process_binary_tree(n, tp);
		val.type = VALUE_LONG;
		val.longval = res;
	} else if (IS_DOUBLE_TYPE(tp.type)) {
		double res = process_binary_tree(n, tp);
		val.type = VALUE_DOUBLE;
		val.doubleval = res;
	} else if (IS_FLOAT_TYPE(tp.type)) {
		double res = process_binary_tree(n, tp);
		val.type = VALUE_FLOAT;
		val.floatval = (float) res;
	} else if (IS_CHAR_TYPE(tp.type) && IS_POINTER_TYPE(tp) || IS_STRING_TYPE(tp.type) || IS_CHAR_TYPE(tp.type)) {
    	val.type = IS_CHAR_TYPE(tp.type) && IS_POINTER_TYPE(tp) || IS_STRING_TYPE(tp.type)
			? VALUE_STRING : VALUE_CHAR;
    	val.str = process_string_tree(n);
	}
	return val;
}

public string *process_string_tree(ASTnode *tree)
{
	if (!IS_STRING_VAL(tree->val.type)) {
		show_lexer_error("Not Valid String");
		panic(NULL);
	}
	string *str = prosing_string_init(tree->val.str->value);
	if (tree->left == NULL) {
		return str;
	}
	string *left_str = process_string_tree(tree->left);
	prosing_string_append(left_str, str->value);
	prosing_string_free(str);
	return left_str;
}

public double process_binary_tree(ASTnode *n, type tp)
{
	double left, right;
	if (n->left)
		left = process_binary_tree(n->left, tp);
	if (n->right)
		right = process_binary_tree(n->right, tp);
	switch (n->type) {
		case A_AND :
			return left && right;
		case A_OR :
			return left || right;
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
	    case A_ISEQUAL :
	        return left == right;
	    case A_NOTEQUAL :
	        return left != right;
		case A_CONST :
			{
				int val_type = n->val.type;
				if (IS_INT_TYPE(tp.type)) {
					return VALUE_AS_INT(n->val);
				}
				else if (IS_LONG_TYPE(tp.type)) {
					if (IS_INT_VAL(val_type))
						return VALUE_AS_INT(n->val);
					return VALUE_AS_LONG(n->val);
				}
				else if (IS_DOUBLE_TYPE(tp.type)) {
					if (IS_INT_VAL(val_type))
						return VALUE_AS_INT(n->val);
					else if (IS_LONG_VAL(val_type))
						return (double) VALUE_AS_LONG(n->val);
					else if (IS_FLOAT_VAL(val_type))
						return VALUE_AS_FLOAT(n->val);
					return VALUE_AS_DOUBLE(n->val);
				}
				else if (IS_FLOAT_TYPE(tp.type)) {
					if (IS_INT_VAL(val_type))
						return VALUE_AS_INT(n->val);
					return VALUE_AS_FLOAT(n->val);
				}
			}
		default :
			show_lexer_error("Wrong Value Type and Data Type");
			panic(NULL);
	}
	return -1;
}

public void print_ast(ASTnode *n, int depth)
{
	if (!n)
		return;
	for (int i = 0; i < depth; i++) {
		putchar(' ');
	}
	printf("%s (%d:%d) --->", get_nodetype_str(n->type), n->pos.line, n->pos.col);
	
	if (n->type == A_CONST) {
		print_value(n->val);
	} else if (n->type == A_STR)
		printf(" '%s'", VALUE_AS_STRING(n->val)->value);
	
	printf(" %s\n", get_valuetype_str(n->val.type));
	if (n->left) {
		print_ast(n->left, depth + 4);
	}
	if (n->right) {
		print_ast(n->right, depth + 4);
	}
}
