#include "../../src/lexer/lexer.h"
#include "../../src/token/token.h"

static struct lexer *l;
#define array_length(a) sizeof(a)/ sizeof(a[0])

void init()
{
	l = lexer_init();
}

void lexer_expect(struct lexer *l, struct token toks[], int len,char *test_name)
{
	//int len = sizeof(struct token) / sizeof(toks[0]);
	bool error = false;
	for (int i = 0; i < len; i++) {
		lex(l);
		if (l->tok.type != toks[i].type) {
			printf("Expected <'%s'>, But Was <'%s'>\n", get_token_str(toks[i].type), get_token_str(l->tok.type));
			error = true;
		}
	}
	if (error) {
		printf("%s -> \033[33mfaild\033[0m\n", test_name);
	} else {
		printf("%s -> \033[32msuccess\033[0m\n", test_name);
	}
}

void test1()
{
	// ++ -- - / -= ++
	struct token toks[] = {
		{.type = T_INC},
		{.type = T_DEC},
		{.type = T_DASH},
		{.type = T_SLASH},
		{.type = T_DECEQUAL},
		{.type = T_INC}
	};
	l->open_file(l, "test1.txt");
	set_working_lexer(l);
	lexer_expect(l, toks, array_length(toks), "test1");
}

void test2()
{
	struct token toks[] = {
		{.type = T_OP_P},
		{.type = T_CL_P},
		{.type = T_CL_P},
		{.type = T_OP_CB},
		{.type = T_OP_CB},
		{.type = T_OP_CB},
		{.type = T_CL_CB},
		{.type = T_CL_CB},
		{.type = T_OBRKT},
		{.type = T_CBRKT},
		{.type = T_CARET},
		{.type = T_AND},
		{.type = T_STAR},
		{.type = T_CL_P},
		{.type = T_HASHTAG},
		{.type = T_EXCLAM},
	};
	l->open_file(l, "test2.txt");
	l->pos = new_pos_struct;
	lexer_expect(l, toks, array_length(toks),"test2");
}

void test3()
{
	struct token toks[] = {
		{.type = T_SHLEQUAL},
		{.type = T_SHIFT_R},
		{.type = T_QUES},
		{.type = T_SHLEQUAL},
		{.type = T_DASH},
		{.type = T_DECEQUAL},
		{.type = T_INCEQUAL},
		{.type = T_MODEQUAL},
		{.type = T_EXCLAM},
		{.type = T_TILDE},
		{.type = T_PIPEPIPE},
		{.type = T_OREQUAL},
	};
	l->open_file(l, "test3.txt");
	l->pos = new_pos_struct;
	lexer_expect(l, toks, array_length(toks),"test3");
}

int main()
{
	init();
	test1();
	test2();
	test3();
}
