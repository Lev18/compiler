#include "dynstr.h"
#include <string.h>
#include <ctype.h>

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

string_buf all_tokens;

void insert_token(const char* st, const char* end) {
    int size = end - st;
    char* token = (char*)malloc(size + 1);
    memcpy(token, st, size);
    token[size] = '\0';
    append(&all_tokens, token);
}

void line_tokenizer(const char* line) {

  const char* forward = line;
  const char* lexemeBeg = line;
  
  int str_len = strlen(line);
  int in = 0;
  while (*forward != '\0' ||  in < str_len) {
    
    if (isalnum(*forward)) {
      while(*forward != '\0' && isalnum(*forward)) {
        ++forward;
      }
      insert_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim_left(forward);
    }

    if (*forward == '(') {
      ++forward;
      insert_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim_left(forward);
    }

    if (*forward == '<') {
      ++forward;
      if (*forward == '=') {
        ++forward;
      }
      insert_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim_left(forward);
    }

    if (*forward == '-') {
            ++forward;
      if (*forward == '>') {
        ++forward;
      }

      insert_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim_left(forward);
    }

    if (*forward == ')') {
      ++forward;
      insert_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim_left(forward);
    }

    if (*forward == '{') {
      ++forward;
      insert_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim_left(forward);
    }

    if (*forward == '}') {
      ++forward;
      insert_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim_left(forward);
    }

    if (*forward == '+') {
            ++forward;
      if (*forward == '+') {
        ++forward;
      }

      insert_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim_left(forward);
    }


    ++in;
    forward = trim_left(forward);
    lexemeBeg = forward;
  } 
}

void clear_str_buff(string_buf* str) {
    int i = 0;
    while (i < str->len) {
        if (str->str[i])
            free((void*)str->str[i]);
        ++i;
    }
    free(str->str);
}

int main(int argc, char *argv[]){
    FILE* inFile;

    inFile = fopen(argv[1], "r");

    char *line = NULL;
    size_t len = 0;
    string_buf str =  {0};

    if (inFile == NULL){
        fprintf(stderr, "Unable to open file\n");
        return 1;
    }
    else {
        while (getline(&line, &len, inFile) != -1){
            line[strcspn(line, "\n")] = '\0';
            append(&str, strdup(line));
        }
        free(line);
    }
    trim(&str);

    int i = 0;
    while (i < str.len) {
        line_tokenizer(str.str[i]);
        ++i;
    }

    int tok_len = 0;
    while(tok_len < all_tokens.len) {
        printf("%s\n", all_tokens.str[tok_len]);
        ++tok_len;
    }

    clear_str_buff(&str);
    clear_str_buff(&all_tokens);

    fclose(inFile);
}
