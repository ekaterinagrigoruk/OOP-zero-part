#pragma once

typedef struct Tokens {
    size_t number_tokens;
    char** token_arr;
}Tokens;

Tokens* parse(const char* str);