#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

#define STRING_IMPL
#include "lexer.h" 

typedef struct {
    char *str;
    size_t len;
    size_t cap;
}Char_Array;

// this is shallow clearer it doesn't free memory 
void clear_arr(Char_Array *arr) {
    arr->str = NULL;
    arr->len = 0;
    arr->cap = 0;
}

int main(int argc, char *argv[]) {
    FILE* inFile;
    Char_Array arr = {0};
    Tokens all_tokens = {0};
    Lexer lexer = {0};

    inFile = fopen(argv[argc - 1], "r");
    assert(inFile != NULL && "Unable to open file");

    do {
        char c = fgetc(inFile);
        if (feof(inFile))
            break;
        do_append(&arr, c, char);
    }while(1);
    fclose(inFile);

    init_c_lexer(&lexer, arr.str, (arr.str + arr.len), arr.len);
    clear_arr(&arr);

    get_next_token(&lexer, &all_tokens);
    get_next_token(&lexer, &all_tokens);

    /*
    size_t len = 0;
    while (len < all_tokens.len) {
        const char *st = all_tokens.str[len]->start;
        while (st != all_tokens.str[len]->end) {
            printf("%c", *(st++));
        }
        printf("\n");
        ++len;
    }
    */
  size_t len = 0;
    while (len < all_tokens.len) {
        const char *st = all_tokens.str[len]->start;
        while (st != all_tokens.str[len]->end) {
            printf("%c", *(st++));
        }
        printf("\n");
        ++len;
    }
    printf("%zu\n", all_tokens.len);
    
    return 0;
}


/*

   int main2(int argc, char *argv[]){
   FILE* inFile;

   inFile = fopen(argv[argc - 1], "r");


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
   fclose(inFile);
   }
   trim(&str);

   size_t i = 0;
   while (i < str.len) {
   line_tokenizer(&all_tokens, str.str[i]);
   ++i;
   }

   for (size_t i = 0; i < all_tokens.len; ++i) {
   printf("(token->'%s'), (type-> %s)\n", all_tokens.str[i]->text, 
   token_type_name(all_tokens.str[i]->tok_type));
   }
   printf("%zu\n", all_tokens.len);

   clear_str_buff(&str);

   return 1;
   }
   */
