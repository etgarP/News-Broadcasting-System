#include "coEditor.h"
#include <unistd.h>

CoEditor* initCoEditor(BoundedBuffer* destination, UnboundedBuffer* source, int which) {
    CoEditor* c = (CoEditor*) malloc(sizeof(CoEditor));
    c->destination = destination;
    c->source = source;
    c->which = which;
}

bool moreToGet(UnboundedBuffer* b) {
    if (b->done && isUnEmpty(b)) {
        return false;
    } 
    return true;
}

void* startCoEditor(void* self) {
    CoEditor* ce = (CoEditor*) self;
    int i = 0;
    while (moreToGet(ce->source)) {
        Pair* p = removePairUn(ce->source);
        usleep(100000);
        insertPair(ce->destination, p);

    }
    // printf("co number - %d: %d\n", ce->which, i);
    if (ce->which == 0) 
        ce->destination->done = true;
    if (ce->which == 1) 
        ce->destination->done1 = true;
    if (ce->which == 2) 
        ce->destination->done2 = true;
    freeUnbuffer(ce->source);
}
