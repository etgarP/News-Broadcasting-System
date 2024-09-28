#include "ProducersList.h"

ProducerList* initPro(Producer* head, Producer* tail) {
    ProducerList *p = (ProducerList*) malloc(sizeof(ProducerList));
    p->head = head;
    p->tail = tail;
    p->iter = head;
}

void deletePro(ProducerList* pl, Producer* p) {
    Producer* iter = pl->head;
    Producer* parent = NULL;
    while (iter != p) {
        parent = iter;
        iter = iter->next;
    }
    // if there isnt a father to p
    if (parent == NULL) { 
        // if theres someone after
        if (iter->next != NULL) {
            pl->head = iter->next;
        } else { // if there isnt someone after
            pl->head = pl->tail = NULL;
        }
    } else { // if there is a father to p
        // if theres someone after
        if (iter->next != NULL) {
            parent->next = iter->next;
        } else { // if there isnt someone after
            parent->next = NULL;
            pl->tail = parent;
        }
    }
    freeProducer(p);

}

Producer* getProducer(ProducerList* p){
    if (p->iter == NULL) {
        return NULL;
    }
    Producer* save = NULL;
    if (!proDone(p->iter)) {
        save = p->iter;
        p->iter = p->iter->next;
        if (p->iter == NULL) {
            p->iter = p->head;
        }
        return save;
    } else {
        save = p->iter;
        p->iter = p->iter->next;
        deletePro(p, save);
        if (p->iter == NULL) {
            p->iter = p->head;
        }
        return getProducer(p);
    }
}

void freeProList(ProducerList* p) {
    free(p);
}