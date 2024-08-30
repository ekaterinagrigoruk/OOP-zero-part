#pragma once
#include "point.h"

struct Class_Circle {
    struct Class_Shape shape;
};

struct Circle {
    const struct Shape shape;
    struct Point center;
    int rad;
};

extern const void* Circle;