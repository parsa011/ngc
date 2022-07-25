/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "expression.h"

/*
 * return a leaf that contains a value corresponding to given type .
 * for example if given type kind is string literal , so current token should be
 * a strin literal , no numerical value
 */
public ASTnode *primary_factor(int ptp)
{
	ASTnode *n;
	switch (current_token.type) {

		case TOKEN_INTLIT :
		case TOKEN_LONGLIT :
		case TOKEN_DOUBLELIT :
		case TOKEN_FLOATLIT :
        case TOKEN_CHARLIT :
        case TOKEN_STRLIT :
            {
                ASTnode_type tp;
                if (current_token.type == TOKEN_CHARLIT || current_token.type == TOKEN_STRLIT)
                    tp = A_STR;
                else
                    tp = A_CONST;
    			n = create_ast_leaf(current_token.buffer, tp, current_token.val, current_token.pos);
    			next_token();
    			return n;
        	}

		case TOKEN_OP_P :
			next_token();
			n = parse_expression(0);
			match(TOKEN_CL_P, "Unclosed Parenthesis");
			return n;

		case TOKEN_IDENT :
			{
				symtab_entry *entry = symtab_get_by_name(current_token.buffer, true);
				ASTnode_type tp;
				if (entry->entry_type.type == TYPE_CHAR || entry->entry_type.type == TYPE_STRING)
					tp = A_STR;
				else
					tp = A_CONST;
				n = create_ast_leaf(current_token.buffer, tp, entry->val, current_token.pos);
				next_token();
				return n;
			}

		default :
			show_lexer_error("Bad Token");
			panic(NULL);
			break;

	}
	return NULL;
}

public ASTnode *parse_expression(int ptp)
{
	ASTnode *right, *left;
	/* get numerical part of expression
	 * here, our token should be a valid numerical token, it can a be a symbol that contains a numeric value
	 * or it can be constant
	 */
	left = primary_factor(ptp);
	int tokentype = current_token.type;
	/* save type of current token , it can be open parenthesis or a operation token like + , - and ...
	 */
	if (is_endof_expression())
		goto return_ast;
	token *token_copy;
	while (token_precedence(tokentype) > ptp) {
		/* take a copy of current token , we need position and buffer of it for making ASTnode
		 */
		token_copy = token_duplicate(&current_token);
		next_token();
		/* parse continuation of expression , it will parse just primary(number) if next operation token precedence is 
		 * less than current operation token precedence
		 */
		right = parse_expression(token_precedence(tokentype));
		/* join past trees with new tree from 'right'
		 */
		left = create_ast_node(token_copy->buffer, tokentype_to_nodetype(tokentype), current_token.val, left, right, token_copy->pos);
		tokentype = current_token.type;
		/* check if we can get out of this loop, chekcs if current token is like semi or comma or ...
		 */
		if (is_endof_expression())
			break;
	}
return_ast:
	return left;
}

/*
 *	it will parse statements like :
 *
 *		age = 10;
 *
 *	detect symbol(unary-expression) , parse it value then assign value to it by considering to assign token
 *	assign token can be something like =, += and ...
 */
public ASTnode *parse_assignment_expression()
{
	symtab_entry *entry = symtab_get_by_name(current_token.buffer, true);
	/* Show error if given entry is a Const variable
	 */
	if (IS_CONST_TYPE(entry->entry_type)) {
		show_lexer_error("Can't Change Const Value");
		panic(NULL);
	}
	ASTnode *left = create_ast_leaf(strdup(entry->name), A_IDENT, entry->val, current_token.pos);
	match(TOKEN_IDENT, "Identifier Expected");

	/* we can have some different type of assign token like =, += and ...
	 */
	int operation_type = current_token.type;
	assign_token();

	/* parse rvalue of expression and calculate it to store in value union 
	 */
	value val = calculate_tree(parse_expression(0), entry->entry_type);

	/* create AST leaf for our value
	 */
	ASTnode *rigth = create_ast_leaf("RVALUE", A_CONST, val, current_token.pos);
	/* Build Final tree
	 */
	ASTnode *tree = create_ast_node("ASSIGN", A_ASSIGN, val, left, rigth, current_token.pos);

	// TODO : check assign operator type , like -= , += and ...
	set_val_by_type(&entry->val, &val, operation_type);
	return tree;
}
