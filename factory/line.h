#pragma once
#include "point.h"

struct Class_Line {
    struct Class_Shape shape;
};

struct Line {
    const struct Shape shape;
    struct Point p1;
    struct Point p2;
};

extern const void* Line;