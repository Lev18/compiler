#include <string.h>
#include <ctype.h>
#include "lexer.h"

#define TOKEN_IMPL

Symbols symbol_table [] = {
  {.text = '{', .type = TOK_OPEN_CURLY },
  {.text = '}', .type = TOK_CLOSE_CURLY},
  {.text = '[', .type = TOK_OPEN_PAREN },
  {.text = '[', .type = TOK_CLOSE_PAREN},
  {.text = '(', .type = TOK_OPEN_PAREN },
  {.text = ')', .type = TOK_CLOSE_PAREN},
  {.text = ';', .type = TOK_SEMICOL}
};

#define liter_token_count (sizeof(symbol_table) / sizeof(symbol_table[0]))

const char* trim_left(const char* elem) {
    const char* ptr = elem;
    while (*(ptr) == ' ') {
        ++ptr;
    }
    return ptr;
}

void trim(string_buf* arr) {
    size_t in = 0;
    while (in < arr->len) {
        const char* orig = arr->str[in];
        const char* trimed = trim_left(orig);
        arr->str[in] = strdup(trimed);
        free((void*)orig);
        ++in;
    }
}

void insert_token(Tokens* all_tokens, const char* st, const char* end, Token_Type type) {
    int size = end - st;
    Token* token = (Token*)malloc(sizeof(Token));
    token->text = (char*)malloc(size + 1);
    token->tok_type = type;

    memcpy((char*)token->text, st, size);
    token->text[size] = '\0';
    do_append(all_tokens, token, Token*);
}

void line_tokenizer(Tokens* tokens, const char* line) {

  const char* forward = line;
  const char* lexemeBeg = line;
  
  int str_len = strlen(line);
  int in = 0;

  while (*forward != '\0' && in < str_len) {
    if (*forward == '#') {
        ++forward;
        insert_token(tokens, lexemeBeg, forward, TOK_PREP);
        break;
    }

    if (isalnum(*forward)) {
      while(*forward != '\0' && isalnum(*forward)) {
        ++forward;
      }
      insert_token(tokens, lexemeBeg, forward, TOK_SYMBOL);
      lexemeBeg = forward;
      forward = trim_left(forward);
    }

    for (int i = 0; i < liter_token_count; ++i) {
        if (*forward == symbol_table[i].text) {
            ++forward;
            insert_token(tokens, lexemeBeg, forward, symbol_table[i].type);
            lexemeBeg = forward;
            trim_left(forward);
            break;
        }
    }

    if (*forward == '<') {
      ++forward;
      if (*forward == '=') {
        ++forward;
      } 
      insert_token(tokens, lexemeBeg, forward, TOK_SYMBOL);
      lexemeBeg = forward;
      trim_left(forward);
    }

    if (*forward == '-') {
            ++forward;
      if (*forward == '>') {
        ++forward;
      }

      insert_token(tokens, lexemeBeg, forward, TOK_SYMBOL);
      lexemeBeg = forward;
      trim_left(forward);
    }

    if (*forward == '+') {
            ++forward;
      if (*forward == '+') {
        ++forward;
      }

      insert_token(tokens, lexemeBeg, forward, TOK_SYMBOL);
      lexemeBeg = forward;
      trim_left(forward);
    }
    ++in;
    forward = trim_left(forward);
    lexemeBeg = forward;
  } 
}

void clear_str_buff(string_buf* str) {
    size_t i = 0;
    while (i < str->len) {
        if (str->str[i])
            free((void*)str->str[i]);
        ++i;
    }
    free(str->str);
}

const char* token_type_name(Token_Type type) {
    switch (type) {
        case TOK_EOF:
            return "end of file";
        case TOK_PREP:
            return "preprocessor directive";
        case TOK_SYMBOL:
            return "symbolic referance";
        case TOK_OPEN_PAREN:
            return "open paren";
        case TOK_CLOSE_PAREN:
            return "close paren";
        case TOK_OPEN_CURLY:
            return "open curly brace";
        case TOK_CLOSE_CURLY:
            return "close curly brace";
        case TOK_SEMICOL:
            return "semiclolon";
        default:
            return "unreachable";
    }
} 


