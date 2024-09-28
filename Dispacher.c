#include "Dispacher.h"

Dispacher* dispacherInit(Producer* head, Producer* tail, UnboundedBuffer* sport, UnboundedBuffer* news, UnboundedBuffer* weather) {
    Dispacher* dis = (Dispacher*) malloc(sizeof(Dispacher));
    dis->s = sport;
    dis->n = news;
    dis->w = weather;
    dis->producers = initPro(head, tail);
    return dis;
}

Pair* getProPair(Dispacher* dis) {
    Pair* p = NULL;
    while (p == NULL) {
        Producer* pro = getProducer(dis->producers);
        if (pro == NULL) return NULL;
        else p = getArticle(pro);
        // if (p != NULL)
    }
    return p;
}

void sendToCoEditors(Dispacher* dis, Pair* p) {
    p->next = NULL;
    if (p->subject == 0) {
        insertPairUn(dis->s, p);
    }
    else if (p->subject == 1) {
        insertPairUn(dis->n, p);
    }
    else if (p->subject == 2) {
        insertPairUn(dis->w, p);
    }
    else {
        perror("what is this subject:");
    } 
}

void freeDispacher(Dispacher* dis) {
    freeProList(dis->producers);
    free(dis);
}

void* startDispacher(void* self) {
    Dispacher* dis = (Dispacher*) self;
    Pair* p = getProPair(dis);
    while (p != NULL) {
        // printf("Producer %d ", p->id);
        // if (p->subject == 0) printf("SPORTS");
        // if (p->subject == 1) printf("NEWS");
        // if (p->subject == 2) printf("WEATHER");
        // printf(" %d\n", p->number);
        sendToCoEditors(dis, p);
        p = getProPair(dis);
    }
    dis->n->done = true;
    dis->w->done = true;
    dis->s->done = true;
    freeDispacher(dis);
}

