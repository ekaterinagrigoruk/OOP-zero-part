#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "factory.h"
#include "point.h"
#include "circle.h"
#include "line.h"
#include "rect.h"

static void* create_point(const Tokens* token_arr);
static void* create_circle(const Tokens* token_arr);
static void* create_line(const Tokens* token_arr);
static void* create_rectangle(const Tokens* token_arr);
static bool coordinate_check(int length, int x);

static bool coordinate_check(int length, int coordinate) {
    int digits = 1;
    int divider = 10;
    if (coordinate != 0) {
        while (coordinate >= divider) {
            coordinate = coordinate / divider;
            digits++;
        }
    }
    if (digits != length) {
        return false;
    }
    return true;
}

static void* create_point(const Tokens* tokens) {
    if (tokens == NULL || tokens->number_tokens != 3) {
        return NULL;
    }

    const int x1 = atoi(*(tokens->token_arr + 1));
    const int y1 = atoi(*(tokens->token_arr + 2));

    int res1 = coordinate_check((int)strlen(*(tokens->token_arr + 1)), x1);
    int res2 = coordinate_check((int)strlen(*(tokens->token_arr + 2)), y1);
    if (res1 + res2 != 2) {
        return NULL;
    }
    struct Shape* shape = new(Point, x1, y1);
    return shape;
}

static void* create_circle(const Tokens* tokens) {
    if (tokens == NULL || tokens->number_tokens != 4) {
        return NULL;
    }

    const int x1 = atoi(*(tokens->token_arr + 1));
    const int y1 = atoi(*(tokens->token_arr + 2));
    const int rad = atoi(*(tokens->token_arr + 3));

    int res1 = coordinate_check((int)strlen(*(tokens->token_arr + 1)), x1);
    int res2 = coordinate_check((int)strlen(*(tokens->token_arr + 2)), y1);
    int res3 = coordinate_check((int)strlen(*(tokens->token_arr + 3)), rad);
    if (res1 + res2 + res3 != 3) {
        return NULL;
    }
    struct Shape* shape = new(Circle, x1, y1, rad);
    return shape;
}

static void* create_line(const Tokens* tokens) {
    if (tokens == NULL || tokens->number_tokens != 5) {
        return NULL;
    }

    const int x1 = atoi(*(tokens->token_arr + 1));
    const int y1 = atoi(*(tokens->token_arr + 2));
    const int x2 = atoi(*(tokens->token_arr + 3));
    const int y2 = atoi(*(tokens->token_arr + 4));

    int res1 = coordinate_check((int)strlen(*(tokens->token_arr + 1)), x1);
    int res2 = coordinate_check((int)strlen(*(tokens->token_arr + 2)), y1);
    int res3 = coordinate_check((int)strlen(*(tokens->token_arr + 3)), x2);
    int res4 = coordinate_check((int)strlen(*(tokens->token_arr + 4)), y2);
    if (res1 + res2 + res3 + res4 != 4) {
        return NULL;
    }
    struct Shape* shape = new(Line, x1, y1, x2, y2);
    return shape;
}

static void* create_rectangle(const Tokens* tokens) {
    if (tokens == NULL || tokens->number_tokens != 5) {
        return NULL;
    }

    const int x1 = atoi(*(tokens->token_arr + 1));
    const int y1 = atoi(*(tokens->token_arr + 2));
    const int x2 = atoi(*(tokens->token_arr + 3));
    const int y2 = atoi(*(tokens->token_arr + 4));

    int res1 = coordinate_check((int)strlen(*(tokens->token_arr + 1)), x1);
    int res2 = coordinate_check((int)strlen(*(tokens->token_arr + 2)), y1);
    int res3 = coordinate_check((int)strlen(*(tokens->token_arr + 3)), x2);
    int res4 = coordinate_check((int)strlen(*(tokens->token_arr + 4)), y2);
    if (res1 + res2 + res3 + res4 != 4) {
        return NULL;
    }
    struct Shape* shape = new(Rect, x1, y1, x2, y2);
    return shape;
}

enum ShapeKind {
    point = 0,
    circle = 1,
    line = 2,
    rectangle = 3
};

static void* (*func_arr[4])(const Tokens*) = { create_point, create_circle, create_line, create_rectangle };

static const char point_[] = "point";
static const char circle_[] = "circle";
static const char line_[] = "line";
static const char rectangle_[] = "rect";

Shape* create_shape(const Tokens* tokens) {
    if (tokens == NULL) {
        return NULL;
    }
    if (strcmp(*(tokens->token_arr), point_) == 0) {
        return func_arr[point](tokens);
    }
    else if (strcmp(*tokens->token_arr, circle_) == 0) {
        return func_arr[circle](tokens);
    }
    else if (strcmp(*tokens->token_arr, line_) == 0) {
        return func_arr[line](tokens);
    }
    else if (strcmp(*tokens->token_arr, rectangle_) == 0) {
        return func_arr[rectangle](tokens);
    }
    else {
        return NULL;
    }
}

void free_tokens(Tokens* tokens) {
    for (int i = 0; i < tokens->number_tokens; i++) {
        free(*(tokens->token_arr + i));
    }
    free(tokens->token_arr);
    free(tokens);
}