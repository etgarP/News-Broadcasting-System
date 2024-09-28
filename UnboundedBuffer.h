#ifndef UNBOUNDED_BUFFER_H
#define UNBOUNDED_BUFFER_H

#include <stdio.h>
#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>
#include "BoundedBuffer.h"

typedef struct UnboundedBuffer {
    Pair *head, *tail;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    bool done;
} UnboundedBuffer;

// returns a initiated unbounded buffer
UnboundedBuffer* initUnbuffer();
// inserts a pair in the unbounded buffer
void insertPairUn(UnboundedBuffer* b, Pair* p);
// removes a pair from the unbounded buffer and returns it
Pair* removePairUn(UnboundedBuffer* b);
// frees the unbounded buffer's allocated memory
void freeUnbuffer(UnboundedBuffer *b);
bool isUnEmpty(UnboundedBuffer* b);

#endif /* BOUNDED_BUFFER_H */