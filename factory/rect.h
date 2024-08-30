#pragma once
#include "point.h"

struct Class_Rect {
    struct Class_Shape shape;
};

struct Rect {
    const struct Shape shape;
    struct Point p1;
    struct Point p2;
};

extern const void* Rect;