/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*/

#include "lexer.h"
#include "lexer_file.h"
#include <ctype.h>

private struct lexer *working_lexer;

public struct lexer *lexer_init()
{
	struct lexer *l = ngc_malloc(sizeof(struct lexer));
	l->open_file = &lexer_open_file;
	l->close_file = &lexer_close_file;
	l->put_back_char = 0;
	l->pos = new_pos_struct;
	return l;
}

public void set_working_lexer(struct lexer *l)
{
	working_lexer = l;
}

public bool is_current_lexer(struct lexer *l)
{
	return working_lexer == l;
}

private void put_back(char c)
{
	working_lexer->put_back_char = c;
}

private char next_char()
{
	char c;
	char pt_back = get_lexer_put_back(working_lexer);
	if (pt_back) {
		c = pt_back;
		put_back(0);
		return c;
	}
	c = lexer_file_read_char(working_lexer->fp);
	if (c == '\n') {
		working_lexer->pos.line++;
		working_lexer->pos.col = 0;
	} else
		working_lexer->pos.col++;
	working_lexer->current_char = c;
	return c;
}

private char skip_whitespace()
{
	int c;
	do {
		c = next_char();
	} while (isspace(c));
	return c;
}

public void lex(struct lexer *l)
{
	if (!is_current_lexer(l)) {
		panic("lexer->lex() : given lexer is not working lexer, lexer name : %s", l->file_name);
	}
	int c = skip_whitespace();
	switch (c) {

		case EOF :
			l->tok.type = T_EOF;
			break;

		case '+' :
			c = next_char();
			if (c == '=' ) {
				l->tok.type = T_INCEQUAL;
				break;
			} else if (c == '+') {
				l->tok.type = T_INC;
				break;
			} else
				put_back(c);
			l->tok.type = T_PLUS;
			break;

		case '-' :
			c = next_char();
			if (c == '=' ) {
				l->tok.type = T_DECEQUAL;
				break;
			} else if (c == '-') {
				l->tok.type = T_DEC;
				break;
			} else
				put_back(c);
			l->tok.type = T_DASH;
			break;

		case '*' :
			c = next_char();
			if (c == '=') {
				l->tok.type = T_MUEQUAL;
				break;
			}
			l->tok.type = T_STAR;
			break;

		case '/' :
			c = next_char();
			if (c == '=') {
				l->tok.type = T_DIVEQUAL;
				break;
			}
			l->tok.type = T_SLASH;
			break;

		case '%' :
			c = next_char();
			if (c == '=') {
				l->tok.type = T_MODEQUAL;
				break;
			} else
				put_back(c);
			l->tok.type = T_PERCENT;
			break;

		case '|' :
			c = next_char();
			if (c == '|') {
				l->tok.type = T_PIPEPIPE;
				break;
			} else
				put_back(c);
			l->tok.type = T_PIPE;
			break;

		case '=' :
			c = next_char();
			if (c == '=') {
				l->tok.type = T_ISEQUAL;
				break;
			} else
				put_back(c);
			l->tok.type = T_EQUAL;
			break;

		case '&' :
			c = next_char();
			if (c == '&') {
				l->tok.type = T_ANDAND;
				break;
			} else
				put_back(c);
			l->tok.type = T_AND;
			break;
				
		case '.' :
			l->tok.type = T_DOT;
			break;

		case ',' :
			l->tok.type = T_COMMA;
			break;
		
		case '^' :
			c = next_char();
			if (c == '=') {
				l->tok.type = T_XOREQUAL;
				break;
			} else
				put_back(c);
			l->tok.type = T_CARET;
			break;

		case '?' :
			l->tok.type = T_QUES;
			break;
		
		case '!' :
			c = next_char();
			if (c == '=') {
				l->tok.type = T_NOTEQUAL;
				break;
			} else
				put_back(c);
			l->tok.type = T_EXCLAM;
			break;

		case '>' :
			c = next_char();
			if (c == '>') {
				c = next_char();
				if (c == '=') {
					l->tok.type = T_SHREQUAL;
					break;
				} else
					put_back(c);
				l->tok.type = T_SHIFT_R;
			} else
				put_back(c);
			l->tok.type = T_GT;
			break;


		case '<' :
			c = next_char();
			if (c == '<') {
				c = next_char();
				if (c == '=') {
					l->tok.type = T_SHLEQUAL;
					break;
				} else
					put_back(c);
				l->tok.type = T_SHIFT_L;
			} else
				put_back(c);
			l->tok.type = T_LT;
			break;

		case '#' :
			l->tok.type = T_HASHTAG;
			break;
		
		case '\\' :
			l->tok.type = T_BSLASH;
			break;

		case '~' :
			l->tok.type = T_TILDE;
			break;

		case ':' :
			l->tok.type = T_COLON;
			break;

		case ';' :
			l->tok.type = T_SEMI;
			break;

		case '{' :
			l->tok.type = T_OP_CB;
			break;

		case '}' :
			l->tok.type = T_CL_CB;
			break;

		case '[' :
			l->tok.type = T_OBRKT;
			break;

		case ']' :
			l->tok.type = T_CBRKT;
			break;

		case '(' :
			l->tok.type = T_OP_P;
			break;

		case ')' :
			l->tok.type = T_CP_P;
			break;
	}	
}
