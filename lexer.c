#include <string.h>
#include <ctype.h>
#include "lexer.h"

#define TOKEN_IMPL

Symbols liter_toks [] = {
    {.text = '{', .type = TOK_OPEN_CURLY },
    {.text = '}', .type = TOK_CLOSE_CURLY},
    {.text = '[', .type = TOK_OPEN_PAREN },
    {.text = '[', .type = TOK_CLOSE_PAREN},
    {.text = '(', .type = TOK_OPEN_PAREN },
    {.text = ')', .type = TOK_CLOSE_PAREN},
    {.text = ';', .type = TOK_SEMICOL}
};

const char *symbol_table[] = {
    "int", "main", "return",
};

#define liter_token_count (sizeof(liter_toks) / sizeof(liter_toks[0]))
#define keywd_count (sizeof(symbol_table) / sizeof(symbol_table[0]))


void init_c_lexer(Lexer* lexer, const char *in, const char *end, size_t length) {
    lexer->input_stream = in;
    lexer->cursor_pos = in;
    lexer->eof = end;
    lexer->string_len = length;
}

const char* trim_left(const char* elem) {
    const char* ptr = elem;
    while (*(ptr) == ' ' || *(ptr) == '\n' || *(ptr) == ('\t')) {
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

int insert_token(Tokens* all_tokens, const char* st, const char* end, Token_Type type) {
    int size = end - st;
    Token* token = (Token*)malloc(sizeof(Token));
    token->start = st;
    token->end = end;
    token->length = size;
    token->tok_type = type;

    do_append(all_tokens, token, Token*);
    return 1;
}

int get_next_token(Lexer *lexer, Tokens* tokens) {
    const char* forward = lexer->cursor_pos;
    const char* lexemeBeg = lexer->cursor_pos;

    int in = 0;

    forward = trim_left(forward);
    while (forward != lexer->eof) {
        // TODO: trim left
        if (*forward == '#') {
            while (*forward != '>' && *forward != '"') {
                ++forward;
            }
            ++forward;
            lexer->cursor_pos = forward;
            return insert_token(tokens, lexemeBeg, forward, TOK_PREP);
        }

        if (isalnum(*forward)) {
            while(forward != lexer->eof && isalnum(*forward)) {
                ++forward;
            }
            lexer->cursor_pos = forward;
            return insert_token(tokens, lexemeBeg, forward, TOK_OPER);
        }

        for (int i = 0; i < liter_token_count; ++i) {
            if (*forward == liter_toks[i].text) {
                ++forward;
                insert_token(tokens, lexemeBeg, forward, liter_toks[i].type);
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
            insert_token(tokens, lexemeBeg, forward, TOK_OPER);
            lexemeBeg = forward;
            trim_left(forward);
        }

        if (*forward == '-') {
            ++forward;
            if (*forward == '>') {
                ++forward;
            }

            insert_token(tokens, lexemeBeg, forward, TOK_OPER);
            lexemeBeg = forward;
            trim_left(forward);
        }

        if (*forward == '+') {
            ++forward;
            if (*forward == '+') {
                ++forward;
            }

            insert_token(tokens, lexemeBeg, forward, TOK_OPER);
            lexemeBeg = forward;
            trim_left(forward);
        }
        ++in;
        forward = trim_left(forward);
        lexemeBeg = forward;
        return TOK_PREP;
    } 

    return 0;
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
        case TOK_OPER:
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
