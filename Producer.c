#include "Producer.h"
#include <unistd.h>

Producer* initProducer(int articlesNeeded, int queueSize, int id) {
    Producer* p = (Producer*) malloc(sizeof(Producer));
    p->id = id;
    p->articlesLeft = articlesNeeded;
    p->done = false;
    p->s = p->w = p->n = 0;
    p->b = initBuffer(queueSize);
    p->next = NULL;
}

bool proDone(Producer* p) {
    if (p->done && bufferEmpty(p->b)) return true;
    return false;
}

void initTime() {
    srand(time(NULL));
}

int getArticleNumber() {
    int r = rand() % 3;
    return r;
}

Pair* getRandPair(Producer *p) {
    int article = getArticleNumber();
    Pair* pa = NULL;
    if (article == 0) {
        pa = initPair(article, p->s, p->id);
        p->s++;
    } 
    else if (article == 1) {
        pa = initPair(article, p->n, p->id);
        p->n++;
    } 
    else if (article == 2) {
        pa = initPair(article, p->w, p->id);
        p->w++;
    } 
    else {
        perror("Bad getArticle");
    }
    return pa;
}

void sendArticle(Producer *p) {
    Pair* pa = getRandPair(p);
    insertPair(p->b, pa);
}

void* sendArticles(void* self) {
    Producer* p = (Producer*) self;
    for (int i = 0; i < p->articlesLeft; i++) {
        sendArticle(p);
    }
    p->done = true;
}

Pair* getArticle(Producer* p) {
    Pair* article = tryRemovePair(p->b);
    return article;
}

void freeProducer(Producer* p) {
    freeBuffer(p->b);
    free(p);
}
