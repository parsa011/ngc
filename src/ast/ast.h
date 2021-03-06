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
	A_STR,

	// comparison
	A_LOWER, A_GREATER,
	A_ISEQUAL, A_NOTEQUAL, A_LOWER_EQUAL,
	A_GREATER_EQUAL,

	// Logicals
	A_AND,
	A_OR,

	A_GLUE,
	
	A_ASSIGN,
	A_DECLER,
	A_LVAL,
	A_IDENT,

	A_PRINT,
	
	A_EOF
} ASTnode_type; 

private char *ASTnode_type_str[] = {
	"A_ADD", "A_MINUS",
	"A_MULTIPLY", "A_DIVIDE",
	"A_CONST",
	"A_STR",

	// comparison
	"A_LOWER", "A_GREATER",
	"A_ISEQUAL", "A_NOTEQUAL", "A_LOWER_EQUAL",
	"A_GREATER_EQUAL",

	// Logicals
	"A_AND",
	"A_OR",

	"A_GLUE",
	
	"A_ASSIGN",
	"A_DECLER",
	"A_LVAL",
	"A_IDENT",

	"A_PRINT",

	"A_EOF"
}; 

typedef struct ASTnode_t ASTnode;

struct ASTnode_t {
	char *title;
	ASTnode_type type;
	ASTnode *left;
	ASTnode *right;
	struct position pos;
	value val;
};

/*
 *	@brief : This routine will create new instance of ast node
 *	but we dont set value here , you should set value after creating new one
 */
public ASTnode *create_ast_node(char *title, ASTnode_type type, value val, ASTnode *left, ASTnode *right, struct position pos);

/*
 *	@brief : create a left for abstract syntax tree
 *	leaf can be something like variables that are defined everywhere 
 *	like in function or in list of function arguments
 */
public ASTnode *create_ast_leaf(char *title, ASTnode_type type, value val, struct position pos);

/*
 *	@brief : free ast node (given node with it childrens)
 */
public void ast_free(ASTnode *ast);

/*
 *	@brief : Convert gien type to ast node type
 */
public ASTnode_type tokentype_to_nodetype(token_type tp);

/*
 *	@brief : do string concatination and ... of tree
 */
public string *process_string_tree(ASTnode *tree);

/*
 *	@brief : calculate tree by considering type
 */
public value calculate_tree(ASTnode *tree, type tp);

/*
 *	@brief : name of function is self-document bro XD
 */
public double process_binary_tree(ASTnode * tree, type tp);

/*
 *	@brief : Print given ast into human readable format
 */
public void print_ast(ASTnode *ast, int padding);

#endif
