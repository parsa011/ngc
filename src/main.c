/*
*	ngc programming language
*	Copyright
*		(C) 2022 Parsa Mahmoudy Sahebi
*
*	This file is part of ngc languge (new generation c)
*
*	Entry point of ngc compiler
*/

#include "parser/parser.h"
#include "parser/symtab.h"
#include <stdarg.h>
#include <stdlib.h>

bool interp_mode = false;

void usage(char *program_name)
{
	print("ngc compiler Usage :\n");
	printf("\t %s : file\n", program_name);
	panic(NULL);
}

void panic(const char *msg, ...)
{
	if (msg) {
		char buf[256];
		va_list ap;
		va_start(ap, msg);
		vsnprintf(buf, 256, msg, ap);
		va_end(ap);
		fprintf(stderr, "%s\n", buf);
	}
	exit(0);
}

public void print_prompt()
{
	printf(PROMPT);
}

int main(int argc, char *argv[])
{
	lexer *l = lexer_init();
	if (argc == 1) {
		interp_mode = true;
		l->fp = stdin;
		l->file_name = "[STDIN]";
	} else {
		if (strcmp(file_extension(argv[1]), NGC_FILE_TYPE) != 0) {
			panic("Given File is not a valid 'c' file : %s", argv[1]);
		}
		l->open_file(l, argv[1]);
	}
#if DEBUG_LEXER
	lexer_set_working_lexer(l);
	lex();
	while (l->tok.type != T_EOF) {
		print_token(&l->tok);
		lex();
	}
#else
	symtab_init();
	ASTnode *n = compile(l);
	print_symtab();
	l->close_file(l);
#endif
	//ast_free(n);
	ngc_free(l);
	return 0;
}
