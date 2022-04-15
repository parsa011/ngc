/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "token.h"

/*
 *	TODO : panic if id was out or token_type_str array range
 */
public char *get_token_str(int id)
{
	return token_type_str[id];
}

public struct token *token_init(token_type type)
{
	struct token *t = ngc_malloc(sizeof(struct token));
	t->type = type;
	return t;
}

public struct token *token_duplicate(struct token *n)
{
	struct token *t = ngc_malloc(sizeof(struct token));
	t->type = n->type;
	t->pos.line = n->pos.line;
	t->pos.col = n->pos.col;
	return t;
}

public void token_free(struct token *p)
{
	ngc_free(p);
}

public token_type guess_text_type(char *text)
{
	// TODO : implement this function
	return T_IDENT;
}
