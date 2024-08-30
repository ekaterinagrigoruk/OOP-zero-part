#include <stdio.h>
#include "line.h"

static void* Line_ctor(void* _self, va_list* app) {
    struct Line* self = _self;
    ((const struct Class*)Point)->ctor(&self->p1, app);
    ((const struct Class*)Point)->ctor(&self->p2, app);
    return self;
}

static void Line_draw(const void* _self) {
    const struct Line* self = _self;

    printf("line at (%d,%d), (%d,%d)\n", self->p1.x, self->p1.y, self->p2.x, self->p2.y);
}

static const struct Class_Line _Line = {
    sizeof(struct Line),
    Line_ctor,
    NULL,
    Line_draw
};

const void* Line = &_Line;