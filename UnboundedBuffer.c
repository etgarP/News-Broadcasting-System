#include "UnboundedBuffer.h"

UnboundedBuffer* initUnbuffer() {
    UnboundedBuffer* b = (UnboundedBuffer*)malloc(sizeof(UnboundedBuffer));
    b->head = NULL;
    b->tail = NULL;
    pthread_mutex_init(&b->mutex, NULL);
    pthread_cond_init(&b->not_empty, NULL);
    b->done = 0;
    return b;
}

void insertPairUn(UnboundedBuffer* b, Pair* p) {
    pthread_mutex_lock(&b->mutex);
    p->next = NULL;
    if (b->head == NULL) {
        b->head = p;
        b->tail = p;
    } else {
        b->tail->next = p;
        b->tail = p;
    }
    pthread_cond_signal(&b->not_empty);
    pthread_mutex_unlock(&b->mutex);
}

Pair* removePairUn(UnboundedBuffer* b) {
    pthread_mutex_lock(&b->mutex);
    if (b->head == NULL) {
        pthread_cond_wait(&b->not_empty, &b->mutex);
    }
    Pair* save = b->head;
    b->head = b->head->next;
    if (b->head == NULL) {
        b->tail = NULL;
    }
    pthread_mutex_unlock(&b->mutex);
    return save;
}

void freeUnbuffer(UnboundedBuffer* b) {
    pthread_cond_destroy(&b->not_empty);
    pthread_mutex_destroy(&b->mutex);
    free(b);
}

bool isUnEmpty(UnboundedBuffer* b) {
    return (b->head == NULL);
}

void printUnbuffer(UnboundedBuffer* b) {
    Pair* p = b->head;
    while (p != NULL) {
        printf("Producer %d ", p->id);
        if (p->subject == 0) {
            printf("SPORTS");
        } else if (p->subject == 1) {
            printf("NEWS");
        } else if (p->subject == 2) {
            printf("WEATHER");
        }
        printf(" %d\n", p->number);
        p = p->next;
    }
}