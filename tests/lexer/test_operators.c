#include "../../src/lexer/lexer.h"
#include "../../src/token/token.h"

int main()
{
	struct token toks[] = {
		{.type = T_PLUS},
		{.type = T_DEC},
		{.type = T_DASH},
		{.type = T_SLASH},
		{.type = T_DECEQUAL},
		{.type = T_INC}
	};
	int len = sizeof(toks) / sizeof(toks[0]);
	struct lexer *l = lexer_init();
	l->open_file(l, "test_operators.txt");
	set_working_lexer(l);
	for (int i = 0; i < len; i++) {
		lex(l);
		if (l->tok.type != toks[i].type) {
			printf("Expected <'%s'>, But Was <'%s'>\n", get_token_str(toks[i].type), get_token_str(l->tok.type));
		}
	}

}
