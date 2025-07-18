#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define STRING_IMPL
#include "lexer.h"


int main(int argc, char *argv[]){
    FILE* inFile;

    inFile = fopen(argv[argc - 1], "r");


    char *line = NULL;
    size_t len = 0;
    string_buf str =  {0};
    Tokens all_tokens = {0};

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
    fclose(inFile);
}
