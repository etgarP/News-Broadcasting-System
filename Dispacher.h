#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <stdio.h>
#include "UnboundedBuffer.h"
#include "BoundedBuffer.h"
#include "Producer.h"
#include "ProducersList.h"

typedef struct Dispacher {
    ProducerList* producers;
    UnboundedBuffer *s, *n, *w;
} Dispacher;

// initiates the dispacher
Dispacher* dispacherInit(Producer* head, Producer* tail, UnboundedBuffer* sport, UnboundedBuffer* news, UnboundedBuffer* weather);
// gets a pair from a producer
Pair* getProPair(Dispacher* dis);
void sendToCoEditors(Dispacher* dis, Pair* p);
void freeDispacher(Dispacher* dis);
void* startDispacher(void* self);

#endif // DISPATCHER_H
