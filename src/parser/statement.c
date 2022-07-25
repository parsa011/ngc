/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "statement.h"
#include "expression.h"
#include "decleration.h"

public ASTnode *parse_compound_statement()
{
	ASTnode *tree = NULL;
	ASTnode *left = NULL;
	/* if current token is a '{' it will be true, and in end of function
	 * we will check for a '}'. short of : need_close_curly_brace :)
	 */
	bool need_cl_cb = false;
	if (token_is(TOKEN_OP_CB)) {
		need_cl_cb = true;
		next_token();
	}
	
	if (!need_cl_cb) {
		return parse_statement();
	}
	
	while (!token_is(TOKEN_CL_CB)) {
		
	}
	match(TOKEN_CL_CB, "Unclosed Block");
	return tree;
}
		
public ASTnode *parse_statement()
{
	if (interp_mode) {
		print_prompt();
	}
	ASTnode *tree = NULL;
	switch (current_token.type) {
		case TOKEN_EOF :
			tree = create_ast_node("EOF", A_EOF, INT_VAL(0), NULL, NULL, current_lexer->pos);
			break;
			
		case TOKEN_PRINT :
		    parse_print_statement();
			tree = create_ast_node("Print", A_PRINT, INT_VAL(0), NULL, NULL, current_lexer->pos);
			break;

		case TOKEN_IF :
			tree = parse_if_statement();
			break;
			
		default :
			if (is_type_keyword(false) || is_qualifier(false)) {
				parse_variable_decleration();
				tree = create_ast_node("Decleration", A_DECLER, INT_VAL(0), NULL, NULL, current_lexer->pos);
			} else {
				parse_assignment_expression();
				tree = create_ast_node("Assign", A_ASSIGN, INT_VAL(0), NULL, NULL, current_lexer->pos);
			}
		break;
	}
	semi();
	return tree;
}

#if NGC_DEBUG
public void parse_print_statement()
{
print_again:
	next_token();
	ASTnode *tree = parse_expression(0);
	/* NOTE : we use tree->value.type for type_kind arg
	 * because value types enum and type_kind have same order so their members
	 * has corresponding values , HOPE to not change that :)))
	 * and we consider first elements type in expression as whole expressions
	 * type :)) take care about that
	 * But if first argumant was not a value, we search for first value to get
	 * type of it
	 * In tree like :
	 *
	 *		 A_GREATER :
	 *			   A_CONST 1
	 *			   A_CONST 2
	 *
	 * We will val_type of left child for whole expresion type
	 */
	ASTnode *n = tree;
check_tree_type:
	if (n->type != A_CONST && n->type != A_STR) {
		n = n->left;
		goto check_tree_type;
	}
	type_kind tp_kind = n->val.type;
	value val = calculate_tree(tree, CREATE_TYPE(n->val.type));
	print_value(val);
	if (current_token.type == TOKEN_COMMA)
		goto print_again;
	putchar('\n');
}
#endif

public ASTnode *parse_if_statement()
{
	ASTnode *condition_tree, *if_tree, *else_tree;
	match(TOKEN_IF, "If keyword Expected");
	left_paren();
	ASTnode *condition = parse_expression(0);
	if (calculate_tree(condition, CREATE_TYPE(TYPE_INT)).intval)
		print("Condition is true\n");
	right_paren();
	ASTnode *body = parse_compound_statement();
}
