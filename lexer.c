#ifndef LEXER_H
#define LEXER_H



void line_tokenizer(const char* line);
void insert_token(const char* st, const char* end);
const char* trim_left(const char* elem);

#endif
