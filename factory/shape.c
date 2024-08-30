#include <stdlib.h>
#include <stdio.h>
#include "shape.h"

void draw(const void* _self) {
    const Shape* self = _self;
    ((struct Class_Shape*)self->class)->draw(self);
}