#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

typedef struct Pair {
    int subject, number, id;
    struct Pair* next;
} Pair;

// has the bounded buffer
typedef struct BoundedBuffer {
    Pair *head, *tail;
    sem_t empty, full, mutex, slots;
    bool done, done1, done2;
} BoundedBuffer;

// returns a bounded buffer of given size
BoundedBuffer* initBuffer(int size);
// get subject, number of times and id and returns a pair
Pair* initPair(int subject, int number, int id);
// returns true if the buffer is empty
bool bufferEmpty(BoundedBuffer* b);
// inserts pair in the buffer
void insertPair(BoundedBuffer* b, Pair* p);
// removes pair from the buffer and returns it
Pair* removePair(BoundedBuffer* b);
// try to remove a pair, returns null if there isnt one to take
Pair* tryRemovePair(BoundedBuffer* b);
// frees resources from the Bounded buffer
void freeBuffer(BoundedBuffer *b);

#endif /* BOUNDED_BUFFER_H */