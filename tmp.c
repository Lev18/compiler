#include <stdio.h>
#include <iostream>
#include <string.h>

int max_repeat_elem(const int* arr, size_t arr_size) {
  int max_rpt_elem = arr[0], mx_elem_cnt = 1;
  
  for (size_t i = 1; i < arr_size; ++i) {
    if (max_rpt_elem == arr[i]) {
      ++mx_elem_cnt;
    }
    else {
      --mx_elem_cnt;
      if (mx_elem_cnt == 0) {
        max_rpt_elem = arr[i];
        mx_elem_cnt = 1;
      }
    }
  }
    
  return mx_elem_cnt > 1 ? 1 : 0;
}

const char* trim(const char* elem) {
  const char* ptr = elem;
  while (*(ptr) == ' ') {
    ++ptr;
  }
  return ptr;
}

const char* tokens[10] = {0}; 
int tokens_count = 0;
void inser_token(const char* st, const char* end) {
  const char* iter = st;
  int size = 0;
  while(iter != end) {
    ++iter;
    ++size;
  }
  const char* token = (const char*)malloc(sizeof(char) * size);
  
  tokens[tokens_count++] = token;
}

void tokenize(const char* line) {
  const char* trimed = trim(line);
  const char* forward = trimed;
  const char* lexemeBeg = trimed;
  while (*forward != '\n') {
    
    if (isalpha(*forward)) {
      while(*forward != '\n' && isalpha(*forward)) {
        ++forward;
      }
      inser_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim(forward);
    }
    if (*forward == '('){
      ++forward;
      inser_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim(forward);
    }
    if (*forward == '<') {
      ++forward;
      if (*forward == '=') {
        ++forward;
      }
      inser_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim(forward);
    }
    if (*forward == '-') {
            ++forward;
      if (*forward == '>') {
        ++forward;
      }
      inser_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim(forward);
    }
    if (*forward == ')'){
      ++forward;
      inser_token(lexemeBeg, forward);
      lexemeBeg = forward;
      trim(forward);
    }
    forward = trim(forward);
    lexemeBeg = forward;
  } 
}

int main() {
  tokenize("     while(in < arr->len) {\n");
  return 0;
}
