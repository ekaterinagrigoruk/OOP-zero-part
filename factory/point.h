#pragma once
#include "shape.h"

struct Class_Point {
    struct Class_Shape shape;
};

struct Point {
    const struct Shape shape;
    int x, y;
};

extern const void* Point;