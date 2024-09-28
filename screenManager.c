#include "screenManager.h"

void printMessege(int id, int type, int howMany) {
    printf("Producer %d ", id);
    if (type == 0) printf("SPORTS");
    if (type == 1) printf("NEWS");
    if (type == 2) printf("WEATHER");
    printf(" %d\n", howMany);
}

bool stillGoing(BoundedBuffer* b) {
    if (b->done1 && b->done2 && b->done && bufferEmpty(b)) {
        return false;
    }
    return true;
}

void* startScreenManager(void* self) {
    BoundedBuffer* source = (BoundedBuffer*) self;
    while (stillGoing(source)) {
        // if (source->done1 && source->done2 && source->done) {
        //     printf("here");
        // }
        Pair* p = tryRemovePair(source);
        if (p == NULL) continue;
        printMessege(p->id, p->subject, p->number);
        free(p);
    }
    printf("DONE");
    freeBuffer(source);
}