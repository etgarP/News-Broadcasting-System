#ifndef PRODUCER_H
#define PRODUCER_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "BoundedBuffer.h"

typedef struct Producer {
    BoundedBuffer* b;
    int id;
    int articlesLeft;
    int s, n, w;
    bool done;
    struct Producer* next;
} Producer;

// returns a producer with everything it needs. gets the number of articles needded and q size
Producer* initProducer(int articlesNeeded, int queueSize, int id);
// returns true if the producer sent everything and its bounded buffer is empty
bool proDone(Producer* p);
// initiates the time, this needs to be used only once at the start of the program
void initTime();
// get a random article number from 1 to 3
int getArticleNumber();
// gets a pair that got a random subject number
Pair* getRandPair(Producer *p);
// sends the article to the bounded buffer
void sendArticle(Producer *p);
// sends all of the article the producer needs to send
void* sendArticles(void* self);
// used to try to get an article from a buffer. returns null if theres nothing to get right now
Pair* getArticle(Producer* p);
// frees the producers resources
void freeProducer(Producer* p);

#endif
