#include "../../src/lexer/lexer.h"
#include "../../src/token/token.h"
#include <stdbool.h>

#define array_length(a) sizeof(a)/ sizeof(a[0])

void lexer_expect(lexer *, token[], int, char *, bool);

