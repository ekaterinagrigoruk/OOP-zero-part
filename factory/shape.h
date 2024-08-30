#pragma once
#include "class.h"

struct Class_Shape {
	struct Class _class;
    void (*draw)(const void* _self);
};

typedef struct Shape {
	const void* class;
}Shape;