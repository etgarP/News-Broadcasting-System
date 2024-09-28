#ifndef PRODUCERSLIST_H
#define PRODUCERSLIST_H

#include <stdio.h>
#include "UnboundedBuffer.h"
#include "BoundedBuffer.h"
#include "Producer.h"

typedef struct ProducerList {
    Producer* head;
    Producer* tail;
    Producer* iter;
} ProducerList;

// initiates the producers list
ProducerList* initPro(Producer* head, Producer* tail);
Producer* getProducer(ProducerList* p);
// frees the stack 
void freeProList(ProducerList* p);
#endif // PRODUCERSLIST_H
