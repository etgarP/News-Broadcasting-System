#include "BoundedBuffer.h"
#include <unistd.h>

Pair* initPair(int subject, int number, int id) {
    Pair *p = (Pair*) malloc(sizeof(Pair));
    p->subject = subject;
    p->number = number;
    p->next = NULL;
    p->id = id;
    return p;
}

BoundedBuffer* initBuffer(int size) {
    BoundedBuffer *b = (BoundedBuffer*) malloc(sizeof(BoundedBuffer));
    b->head = NULL;
    b->tail = NULL;
    b->done = b->done1 = b->done2 = false;
    sem_init(&b->empty, 0, size); // Initialize the empty semaphore with BUFFER_SIZE
    sem_init(&b->full, 0, 0); // Initialize the full semaphore with 0 (no items initially)
    sem_init(&b->mutex, 0, 1); // Initialize the mutex semaphore with 1 (unlocked)
    return b;
}

void insertPair(BoundedBuffer* b, Pair* p) {
    sem_wait(&b->empty);
    sem_wait(&b->mutex);
    p->next = NULL;
    if(b->tail != NULL) {
        b->tail->next = p;
        b->tail = p;
    } else {
        b->head = b->tail = p;
    }
    sem_post(&b->mutex);
    sem_post(&b->full);
}

Pair* removePair(BoundedBuffer* b) {
    sem_wait(&b->full);
    sem_wait(&b->mutex);
    Pair *save = b->head;
    if (save == NULL) {
        perror("WHAT remove");
    } else if (save->next != NULL) {
        b->head = save->next;
        save->next = NULL;
    } else {
        b->head = b->tail = NULL;
    }
    sem_post(&b->mutex);
    sem_post(&b->empty);
    return save;
}

Pair* tryRemovePair(BoundedBuffer* b) {
    if (sem_trywait(&b->full) == -1) {
        return NULL;
    }
    sem_wait(&b->mutex);
    if (b->head == NULL) {
        perror("WHAT try remove:");
    }
    Pair *save = b->head;
    // if (save->number == 32760) {
    //     printf("hello\n");
    // }
    if (save->next != NULL) {
        b->head = save->next;
    } else {
        b->head = b->tail = NULL;
    }
    sem_post(&b->mutex);
    sem_post(&b->empty);
    return save;
}

void freeBuffer(BoundedBuffer *b) {
    if (b->head != NULL) perror("free too soon bounded");
    sem_destroy(&b->mutex);
    sem_destroy(&b->empty);
    sem_destroy(&b->full);
    free(b);
}

bool bufferEmpty(BoundedBuffer* b) {
    if (b->tail == NULL || b->head == NULL) return true;
    return false;
}
