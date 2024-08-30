#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "list.h"

#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE, LINE)
#define new DEBUG_NEW

typedef struct {
    int* mas;
} Mass;

void destroy(void* element_data) {
    Mass* deleted = (Mass*)element_data;
    free(deleted->mas);
}

typedef struct {
    int array[8];
    float d_variable;
} Value;



int main(int argc, char* argv[]) {

    assert(!slist_create(0));
    slist_destroy(NULL, NULL);
    assert(!slist_init(NULL, 0, NULL));
    assert(!slist_item(NULL, 0));
    assert(!slist_prepend(NULL));
    assert(!slist_current(NULL, 0));
    assert(!slist_insert(NULL, 0));
    assert(!slist_init(NULL, 36, NULL));
    assert(!slist_item(NULL, 8));
    assert(!slist_current(NULL, 818));
    assert(!slist_insert(NULL, 181));
    
    void* slist6 = slist_create(sizeof(Mass));
    assert(slist_item(slist6, 0) == NULL);
    assert(slist_item(slist6, -1) == NULL);
    assert(slist_item(slist6, 1) == NULL);
    slist_destroy(slist6, NULL);

    void* slist = slist_create(sizeof(Value));

    assert(slist_next(slist, slist_stop(slist)) == slist_stop(slist));

    assert(0 == slist_count(slist));
    assert(slist_stop(slist) == slist_first(slist));

    Value value1 = { {1, 2, 3, 4, 5, 6, 7, 8}, 0.f };
    Value* insertedValue1 = (Value*)slist_prepend(slist);
    
    assert(insertedValue1 != NULL);
    assert(slist_count(slist) == 1);

    int result = 0;
    if ((Value*)slist_item(slist, 0) == insertedValue1) {
        result = 1;
    }
    assert(result);




    void* slist5 = slist_create(sizeof(Mass));

    assert(slist_next(slist5, slist_stop(slist5)) == slist_stop(slist5));

    assert(0 == slist_count(slist5));
    assert(slist_stop(slist5) == slist_first(slist5));

    Mass* massiv = malloc(sizeof(Mass));
    if (massiv == NULL) {
        return 0;
    }
    massiv->mas = malloc(5 * sizeof(int));
    if (massiv->mas == NULL) {
        return 0;
    }
    for (size_t i = 0; i < 5; i++) {
        massiv->mas[i] = i;
    }
    
    Mass* inserted = (Mass*)slist_prepend(slist5);

    assert(inserted != NULL);
    assert(slist_count(slist5) == 1);

    int result2 = 0;
    if ((Mass*)slist_item(slist5, 0) == inserted) {
        result2 = 1;
    }
    assert(result2);

    *inserted = *massiv;

    slist_destroy(slist5, destroy);
    free(massiv);



    *insertedValue1 = value1;

    Value* item = (Value*)slist_item(slist, 0);

    for (size_t i = 0; 8 > i; ++i) { //робит
        assert(item->array[i] == value1.array[i]);
    }

    assert(fabsf(item->d_variable - value1.d_variable) < 1e-10f); //робит
    assert(NULL == slist_item(slist, 1)); //робит
    assert(slist_next(slist, slist_first(slist)) == slist_stop(slist)); //робит

    Value value2 = { {8, 7, 6, 5, 5, 3, 2, 1}, 0.f };
    Value* insertedValue2 = (Value*)slist_prepend(slist);
    *insertedValue2 = value2;
    
    assert(slist_next(slist, slist_next(slist, slist_first(slist))) == slist_stop(slist)); //робит

    slist_remove(slist, NULL);

    Value value3 = { {8, 9, 10, 11, 8, 3, 2, 1}, 0.f };
    Value* insertedValue3 = (Value*)slist_prepend(slist);
    *insertedValue3 = value3;

    assert(slist_next(slist, slist_next(slist, slist_first(slist))) == slist_stop(slist)); //робит

    slist_remove(slist, NULL);

    size_t first = slist_first(slist);
    int res = 0;
    if (insertedValue1 == (Value*)slist_current(slist, first))
        res = 1;
    assert(res);

    Value* insertedValue4 = (Value*)slist_insert(slist, slist_first(slist));
    *insertedValue4 = value3; 

    assert(slist_count(slist) == 2);

    assert(slist_next(slist, slist_next(slist, slist_first(slist))) == slist_stop(slist)); //робит
    
    slist_erase(slist, first, NULL);
    assert(slist_next(slist, slist_first(slist)) == slist_stop(slist)); //робит

    void* slist2 = slist_init(slist, sizeof(Value), NULL);
    assert(0 == slist_count(slist2));
    assert(slist_stop(slist2) == slist_first(slist2));

    Value value5 = { {8, 9, 10, 11, 8, 3, 2, 1}, 0.f };
    Value* insertedValue5 = (Value*)slist_insert(slist2, slist_first(slist2));
    *insertedValue5 = value5;

    Value* item2 = (Value*)slist_item(slist2, 0);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item2->array[i] == value5.array[i]);
    }

    slist_destroy(slist2, NULL);

    void* slist3 = slist_create(sizeof(Value));
    void* slist4 = slist_init(slist3, sizeof(Value), NULL);
    Value value6 = { {8, 9, 10, 11, 8, 3, 2, 1}, 0.f };
    Value* insertedValue6 = (Value*)slist_insert(slist4, slist_first(slist4));
    *insertedValue6 = value6;

    Value value8 = { {5, 6, 3, 11, 8, 3, 2, 0}, 0.f };
    Value* insertedValue8 = (Value*)slist_insert(slist4, slist_first(slist4));
    *insertedValue8 = value8;

    Value* item5 = (Value*)slist_item(slist4, 1);
    for (size_t i = 0; 8 > i; ++i) {
            assert(item5->array[i] == value8.array[i]);
        }

    assert(slist_insert(slist4, slist_stop(slist4)) == NULL);
    //assert(slist_erase(slist4, slist_stop(slist4), NULL));

    Value value9 = { {5, 6, 3, 11, 8, 3, 2, 0}, 0.f };
    Value* insertedValue9 = (Value*)slist_insert(slist4, slist_next(slist4, slist_first(slist4)));
    *insertedValue9 = value9;

    Value* item6 = (Value*)slist_item(slist4, 2);
    for (size_t i = 0; 8 > i; ++i) {
        assert(item6->array[i] == value9.array[i]);
    }

    assert(slist_count(slist4) == 3);
    assert(slist_item(slist4, -1) == NULL);
    assert(slist_current(slist4, slist_first(slist4)));
    assert(slist_current(slist4, slist_stop(slist4)) == NULL);


    slist_erase(slist4, slist_next(slist4, slist_next(slist4, slist_first(slist4))), NULL);
    assert(slist_count(slist4) == 2);

    assert(slist_first(slist4) != slist_stop(slist4));
    assert(slist_current(slist4, slist_first(slist4)));

    slist_erase(slist4, slist_next(slist4, slist_first(slist4)), NULL);
    assert(slist_count(slist4) == 1);

    slist_erase(slist4, slist_first(slist4), NULL);
    assert(slist_count(slist4) == 0);

    assert(slist_next(slist4, slist_stop(slist4)) == slist_stop(slist4));

    assert(0 == slist_count(slist4));
    assert(slist_stop(slist4) == slist_first(slist4));

    slist_destroy(slist4, NULL);

    _CrtDumpMemoryLeaks();
    return 0;
}