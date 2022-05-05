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
#include "../parser/symtab.h"
#include "../type/types.h"

typedef enum {
	A_ADD, A_MINUS,
	A_MULTIPLY, A_DIVIDE,
	A_CONST,

	A_ASSIGN,
	A_LVAL,
	A_IDENT

} ASTnode_type; 

private char *ASTnode_type_str[] = {
	"A_ADD", "A_MINUS",
	"A_MULTIPLY", "A_DIVIDE",
	"A_CONST",

	"A_ASSIGN",
	"A_LVAL",
	"A_IDENT"
}; 

struct ASTnode {
	char *title;
	ASTnode_type type;
	struct ASTnode *left;
	struct ASTnode *right;
	struct position pos;
	union value val;
	struct type node_val_type;
};

/*
 *	@brief : This routine will create new instance of ast node
 *	but we dont set value here , you should set value after creating new one
 */
public struct ASTnode *create_ast_node(char *, ASTnode_type, union value, struct ASTnode *, struct ASTnode *, struct position);

/*
 *	@brief : create a left for abstract syntax tree
 *	leaf can be something like variables that are defined everywhere 
 *	like in function or in list of function arguments
 */
public struct ASTnode *create_ast_leaf(char *, ASTnode_type, union value, struct position);

/*
 *	@brief : Convert gien type to ast node type
 */
public ASTnode_type tokentype_to_nodetype(token_type);

/*
 *	@brief : calculate tree by considering type
 */
public union value calculate_tree(struct ASTnode *, int);

/*
 *	@brief : name of function is self-document bro XD
 */
public int calculate_binary_tree(struct ASTnode *);

/*
 *	@brief : Print given ast into human readable format
 */
public void print_ast(struct ASTnode *, int);

#endif
