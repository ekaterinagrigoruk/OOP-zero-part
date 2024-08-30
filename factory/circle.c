#include <stdio.h>
#include "circle.h"


static void* Circle_ctor(void* _self, va_list* app) {
    struct Circle* self = _self;
    ((const struct Class*)Point)->ctor(&self->center, app);
    self->rad = va_arg(*app, int);
    return self;
}

static void Circle_draw(const void* _self) {
    const struct Circle* self = _self;

    printf("circle at (%d,%d) rad = %d\n", self->center.x, self->center.y, self->rad);
}

static const struct Class_Circle _Circle = {
    sizeof(struct Circle),
    Circle_ctor,
    NULL,
    Circle_draw
};

const void* Circle = &_Circle;