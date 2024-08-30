#include <stdio.h>
#include "rect.h"

static void* Rect_ctor(void* _self, va_list* app) {
    struct Rect* self = _self;
    ((const struct Class*)Point)->ctor(&self->p1, app);
    ((const struct Class*)Point)->ctor(&self->p2, app);
    return self;
}

static void Rect_draw(const void* _self) {
    const struct Rect* self = _self;

    printf("rect at (%d,%d), (%d,%d)\n", self->p1.x, self->p1.y, self->p2.x, self->p2.y);
}

static const struct Class_Rect _Rect = {
    sizeof(struct Rect),
    Rect_ctor,
    NULL,
    Rect_draw
};

const void* Rect = &_Rect;