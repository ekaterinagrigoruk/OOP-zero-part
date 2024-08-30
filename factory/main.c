#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "factory.h"
#include "parser.h"
#include "shape.h"

#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE, LINE)
#define new DEBUG_NEW


int main(int argc, char** argv) {

    printf("Enter 1 if you want to open your file or 2 if you want to open the default file \n");
    int answer = 0;
    scanf_s("%d", &answer);
    char* name_file = malloc(100 * sizeof(char));
    if (name_file == NULL) {
        return -1;
    }
    if (answer == 1) {
        int res = getchar();
        if (res == EOF) {
            return -1;
        }
        gets_s(name_file, 100);
    }
    if (answer == 2) {
        const char factory_file[] = "factory.txt";
        strcpy_s(name_file, sizeof(factory_file), factory_file);
    }
    FILE* f;
    errno_t err;
    err = fopen_s(&f, name_file, "r");
    if (err != 0 || f == NULL) {
        printf("File doesn't exist");
        return;
    }

    int count_line = 0;
    while (!feof(f)) {
        count_line++;
        char str[100];
        void* res = fgets(str, 100, f);
        if (res == NULL) {
            printf("File read error");
            return;
        }
        Tokens* tokens = parse(str);
        Shape* shape = create_shape(tokens);
        
        if (shape == NULL) {
            printf("Data error in line number %d \n", count_line);
        }
        else {
            draw(shape);
            delete(shape);
        }
        free_tokens(tokens);
    }
    fclose(f);
    free(name_file);

    _CrtDumpMemoryLeaks();
    return 0;
}