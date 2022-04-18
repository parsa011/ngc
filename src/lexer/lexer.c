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
	l->buffer = prosing_string_init("");
	l->tok.text = prosing_string_init("");
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
	prosing_string_append_char(working_lexer->buffer, c);
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
		//panic("lexer->lex() : given lexer is not working lexer, lexer name : %s", l->file_name);
	}
	int c = skip_whitespace();
	
	prosing_string_reset(l->tok.text);
	prosing_string_append_char(l->tok.text, c);

	switch (c) {

		case EOF :
			set_working_lexer_token_type(T_EOF);
			break;

		case '+' :
			c = next_char();
			if (c == '=' ) {
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_INCEQUAL);
				break;
			} else if (c == '+') {
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_INC);
				break;
			} else
				put_back(c);
			set_working_lexer_token_type(T_PLUS);
			break;

		case '-' :
			c = next_char();
			if (c == '=' ) {
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_DECEQUAL);
				break;
			} else if (c == '-') {
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_DEC);
				break;
			} else
				put_back(c);
			set_working_lexer_token_type(T_DASH);
			break;

		case '*' :
			c = next_char();
			if (c == '=') {
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_MUEQUAL);
				break;
			} else
				put_back(c);
			set_working_lexer_token_type(T_STAR);
			break;

		case '/' :
			c = next_char();
			if (c == '=') {
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_DIVEQUAL);
				break;
			} else if (c == '*') {
				skip_ml_comment();
				lex(l);
				break;
			} else if (c == '/') {
				skip_ol_comment();
				lex(l);
				break;
			} else 
				put_back(c);
			set_working_lexer_token_type(T_SLASH);
			break;

		case '%' :
			c = next_char();
			if (c == '=') {
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_MODEQUAL);
				break;
			} else
				put_back(c);
			set_working_lexer_token_type(T_PERCENT);
			break;

		case '|' :
			c = next_char();
			if (c == '|') {
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_PIPEPIPE);
				break;
			} else if (c == '=') {
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_OREQUAL);
				break;
			} else
				put_back(c);
			set_working_lexer_token_type(T_PIPE);
			break;

		case '=' :
			c = next_char();
			if (c == '=') {
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_ISEQUAL);
				break;
			} else
				put_back(c);
			set_working_lexer_token_type(T_EQUAL);
			break;

		case '&' :
			c = next_char();
			if (c == '&') {
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_ANDAND);
				break;
			} else
				put_back(c);
			set_working_lexer_token_type(T_AND);
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
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_XOREQUAL);
				break;
			} else
				put_back(c);
			set_working_lexer_token_type(T_CARET);
			break;

		case '?' :
			set_working_lexer_token_type(T_QUES);
			break;
		
		case '!' :
			c = next_char();
			if (c == '=') {
				prosing_string_append_char(l->tok.text, c);
				set_working_lexer_token_type(T_NOTEQUAL);
				break;
			} else
				put_back(c);
			set_working_lexer_token_type(T_EXCLAM);
			break;

		case '>' :
			c = next_char();
			if (c == '>') {
				prosing_string_append_char(l->tok.text, c);
				c = next_char();
				if (c == '=') {
					prosing_string_append_char(l->tok.text, c);
					set_working_lexer_token_type(T_SHREQUAL);
					break;
				} else
					put_back(c);
				set_working_lexer_token_type(T_SHIFT_R);
				break;
			} else
				put_back(c);
			set_working_lexer_token_type(T_GT);
			break;


		case '<' :
			c = next_char();
			if (c == '<') {
				prosing_string_append_char(l->tok.text, c);
				c = next_char();
				if (c == '=') {
					prosing_string_append_char(l->tok.text, c);
					set_working_lexer_token_type(T_SHLEQUAL);
					break;
				} else
					put_back(c);
				set_working_lexer_token_type(T_SHIFT_L);
			} else
				put_back(c);
			set_working_lexer_token_type(T_LT);
			break;

		case '"' :
			l->tok.str = prosing_string_init("");
str_concat:
			c = next_char();
			while (c != '"') {
				if (c == EOF) {
					// TODO : Implement early_eof_error();
					break;
				}
				prosing_string_append_char(l->tok.str, c);
				c = next_char();
			}
			if ((c = skip_whitespace()) == '"')
				goto str_concat;
			else
				put_back(c);
			set_working_lexer_token_type(T_STRLIT);
			break;

		case '#' :
			set_working_lexer_token_type(T_HASHTAG);
			break;
		
		case '\\' :
			set_working_lexer_token_type(T_BSLASH);
			break;

		case '~' :
			set_working_lexer_token_type(T_TILDE);
			break;

		case ':' :
			set_working_lexer_token_type(T_COLON);
			break;

		case ';' :
			set_working_lexer_token_type(T_SEMI);
			break;

		case '{' :
			set_working_lexer_token_type(T_OP_CB);
			break;

		case '}' :
			set_working_lexer_token_type(T_CL_CB);
			break;

		case '[' :
			set_working_lexer_token_type(T_OBRKT);
			break;

		case ']' :
			set_working_lexer_token_type(T_CBRKT);
			break;

		case '(' :
			set_working_lexer_token_type(T_OP_P);
			break;

		case ')' :
			set_working_lexer_token_type(T_CL_P);
			break;

		default :
			// TODO : scan keywords and identifirers and ...
			if (isalpha(c) || c == '_') {
				scan_ident();
				set_working_lexer_token_type(guess_text_type(l->tok.text->value));
				break;
			}
			if (isdigit(c)) {
				l->tok.integer = scan_number(c);
				set_working_lexer_token_type(T_INTLIT);
				break;
			}
			set_working_lexer_token_type(T_BAD);
			show_lexer_error("Bad Token");
			break;
	}
}

private char *get_pointer_to_buffer(struct position *pos)
{
	char *p = working_lexer->buffer->value;
	struct position current_pos = new_pos_struct;
	while (*p) {
		if (current_pos.line == pos->line && current_pos.col == pos->col)
			break;
		if (*p == '\n') {
			current_pos.col = 0;
			current_pos.line++;
		} else
			current_pos.col++;
		p++;
	}
	return p;
}

private void show_lexer_error(char *msg)
{
	char *p = get_pointer_to_buffer(&working_lexer->pos);

	char info[64];
	get_lexer_pos_string(working_lexer, info);

	printf("%s: \033[33merror:\033[0m %s\n", info, msg);

	printf("%d |", working_lexer->pos.line);

	if (working_lexer->pos.col > 0) {
		char *first_of_line = p - working_lexer->pos.col;
		while (first_of_line < p) {
			putchar(*first_of_line++);
		}
		putchar('\n');
	}
}

public void print_line_info()
{
	char info[64];
	get_lexer_pos_string(working_lexer, info);
	puts(info);
}

public void get_lexer_pos_string(struct lexer *l, char *buf)
{
	snprintf(buf, 64, "%s:%d:%d", l->file_name, l->pos.line, l->pos.col);
}

private void skip_ol_comment() 
{
	int c = next_char();
	while (c != '\n') {
		prosing_string_append_char(working_lexer->tok.text, c);
		c = next_char();
	}
}

private void skip_ml_comment() 
{
	int c = next_char();
	while (1) {
		prosing_string_append_char(working_lexer->tok.text, c);
		if (c == EOF) {
			//TODO : EOF in comment
		}
		if (c == '*') {
			c = next_char();
			if (c == '/')
				break;
		}
		c = next_char();
	}
	next_char();
}

private void scan_ident()
{
	int c = next_char();
	while (isalnum(c)) {
		prosing_string_append_char(working_lexer->tok.text, c);
		c = next_char();
	}
	put_back(c);
}

// TODO : implement scaning other types of number like hex, octal
private int scan_number(char c)
{
	int base = 10, res = 0;
	if (c == '0') {
		c = next_char();
		if (c == 'x') {
			prosing_string_append_char(working_lexer->tok.text, c);
			base = 16;
			c = next_char();
		}
		else if (isdigit(c)) {
			base = 8;
		}		
	}
	while (isdigit(c)) {
		prosing_string_append_char(working_lexer->tok.text, c);
		res = res * base + CHAR_TO_NUM(c);
		c = next_char();
	}
	put_back(c);
	return res;
}
