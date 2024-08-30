#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "factory.h"


static char* get_token(const char* str, int read_counter);
static void* allocate_memory(size_t count, size_t size);

static const char separators[] = "/ .,;\n";

Tokens* parse(const char* str) {
    Tokens* tokens = allocate_memory(1, sizeof(Tokens));
    tokens->number_tokens = 1;
    tokens->token_arr = allocate_memory(1, sizeof(char*));

    int token_number = 0;
    int read_counter = 0;
    int length_str = (int)strlen(str) - 1;
    while (read_counter <= length_str) {
        char* token = get_token(str, read_counter);
        *(tokens->token_arr + token_number) = token;
        token_number++;
        read_counter += (int)strlen(token);
        if (*(str + read_counter) != '\n' && *(str + read_counter) != '\0') {
            char** token_arr = tokens->token_arr;
            tokens->token_arr = realloc(tokens->token_arr, (tokens->number_tokens + 1) * sizeof(char*));
            if (tokens->token_arr == NULL) {
                free(token_arr);
                free_tokens(tokens);
                return NULL;
            }
            else{
                tokens->number_tokens++;
            }
        }
        read_counter++;
    }
    return tokens;
}

static char* get_token(const char* str, int read_counter) {
    int char_counter = 0;
    char* token = allocate_memory(10, sizeof(char));
    int count_separator = 0;
    int length_sep = (int)strlen(separators);
    while (1) {
        while (*(str + read_counter + char_counter) != separators[count_separator] &&
            *(str + read_counter + char_counter) != '\0' && count_separator != length_sep) {
            count_separator++;
        }
        if (count_separator == length_sep) {
            token[char_counter] = *(str + read_counter + char_counter);
            char_counter++;
            count_separator = 0;
        }
        else {
            return token;
        }
    }
}

static void* allocate_memory(size_t count, size_t size){
    void* memory = calloc(count, size);
    if (memory == NULL) {
        exit(-1);
    }
    return memory;
}