#include <stdlib.h>
#include <assert.h>
#include "class.h"

void* new(const void* _class, ...) {
    const Class* class = _class;
    void* p = calloc(1, class->size);
    assert(p);
    *(const Class**)p = class;

    if (class->ctor) {
        va_list ap;
        va_start(ap, _class);
        p = class->ctor(p, &ap);
        va_end(ap);
    }
    return p;
}

void delete(void* self) {
    const Class** cp = self;

    if (self && *cp && (*cp)->dtor) {
        self = (*cp)->dtor(self);
    }
    free(self);
}
