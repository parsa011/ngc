#include "run_test.h"

void lexer_expect(struct lexer *l, struct token toks[], int len, char *test_name, bool trace)
{
	//int len = sizeof(struct token) / sizeof(toks[0]);
	bool error = false;
	for (int i = 0; i < len; i++) {
		lex(l);
		if (trace) {
			print_token(&l->tok);
		}
		if (l->tok.type != toks[i].type) {
			printf("\033[35m[X]\033[0m Expected <'%s'>, But Was <'%s'> --- pos = %d:%d --- text : %s\n", 
					get_token_str(toks[i].type), get_token_str(l->tok.type), l->tok.pos.line, l->tok.pos.col,
					l->tok.buffer);
			error = true;
		}
	}
	if (error) {
		printf("%s -> \033[33mfaild\033[0m\n", test_name);
	} else {
		printf("%s -> \033[32msuccess\033[0m\n", test_name);
	}
}
