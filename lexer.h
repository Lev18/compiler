#ifndef LEXER_H
#define LEXER_H

#include <stdbool.h>
#include <stdlib.h>
#include "dynstr.h"

typedef enum {
    TOK_EOF = 0,
    TOK_PREP,
    TOK_SYMBOL,
    TOK_OPEN_PAREN,
    TOK_CLOSE_PAREN,
    TOK_OPEN_CURLY,
    TOK_CLOSE_CURLY,
    TOK_SEMICOL
}Token_Type;

typedef struct {
    const char *file_path;
    size_t row;
    size_t col;
}Location;

typedef struct {
    Token_Type tok_type;
    char *text;
    size_t text_len;
}Token;

typedef struct {
    const char text;
    Token_Type type;
}Symbols;

typedef struct {
    Token **str;
    size_t cap;
    size_t len;
}Tokens;

void line_tokenizer(Tokens* tokens, const char* line);
void insert_token(Tokens* all_tok, const char* st, const char* end, Token_Type type);
const char *trim_left(const char* elem);
const char *detect_token_type(Token *tokens);
void trim(string_buf* arr);
const char* token_type_name(Token_Type type);

#endif
