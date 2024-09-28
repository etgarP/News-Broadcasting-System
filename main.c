#include <stdio.h>
#include <stdlib.h>
#include "BoundedBuffer.h"
#include "coEditor.h"
#include "BoundedBuffer.h"
#include "coEditor.h"
#include "Dispacher.h"
#include "Producer.h"
#include "ProducersList.h"
#include "UnboundedBuffer.h"
#include "screenManager.h"
#include "sys/stat.h"

void startScreenThread(BoundedBuffer* screenBuffer, pthread_t* thread) {
    pthread_create(thread, NULL, startScreenManager, (void*) screenBuffer);
}

void startProT(Producer* head, Producer* tail, int n, pthread_t* threads) {
    Producer *iter = head;
    for (int i = 0; i < n; i++) {
        pthread_create(threads + i, NULL, sendArticles, (void*) iter);
        iter = iter->next;
    }
}

void startDisT(Dispacher *dis, pthread_t *thread) {
    pthread_create(thread, NULL, startDispacher, (void*) dis);
}

void startCoT(CoEditor *cs, CoEditor *cn, CoEditor *cw, pthread_t thread[3]) {
    pthread_create(thread, NULL, startCoEditor, (void*) cs);
    pthread_create(thread + 1, NULL, startCoEditor, (void*) cn);
    pthread_create(thread + 2, NULL, startCoEditor, (void*) cw);
}

int isFile(char* path) {
    struct stat st;
    if (stat(path, &st)) {
        return 0;
    }
    return S_ISREG(st.st_mode);
}

int main(int argc, char** argv) {
    if(!isFile(argv[1])) {
        exit(-1);
    }
    initTime();
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) return -1;
    char line1[128], line2[128], line3[128], line4[123];
    Producer *head = NULL, *tail = NULL;
    bool start = true;
    int i = 0;
    while (fgets(line1, sizeof(line1), file) && fgets(line2, sizeof(line2), file) 
            && fgets(line3, sizeof(line3), file) && fgets(line4, sizeof(line4), file)) {
        i++;
        // getting info and validating
        int id = atoi(line1);
        int numOfPrud = atoi(line2);
        int size = atoi(line3);
        if (id < 0 || numOfPrud < 0 || size <= 0) {
            printf("bad config file");
            return -1;
        }
        // creating the producers
        if (start) head = tail = initProducer(numOfPrud, size, id);
        else {
            tail->next = initProducer(numOfPrud, size, id);
            tail = tail->next;
        }
        start = false;
    }
    fclose(file);
    //checking if nothing was found
    if (start) {
        printf("bad config file");
        return -1;
    }
    int coQSize = atoi(line1);
    if (coQSize <=0) return -1;
    UnboundedBuffer *s = initUnbuffer(), *n = initUnbuffer(), *w = initUnbuffer();
    BoundedBuffer *screenBuffer = initBuffer(coQSize);
    Dispacher *d = dispacherInit(head, tail, s, n, w);
    CoEditor *cs = initCoEditor(screenBuffer, s, 0), 
            *cn = initCoEditor(screenBuffer, n, 1), *cw = initCoEditor(screenBuffer, w, 2);
    
    pthread_t threads[i];
    startProT(head, tail, i, threads);
    pthread_t disThread;
    startDisT(d, &disThread);
    pthread_t coThreads[3];
    startCoT(cs, cn, cw, coThreads);
    pthread_t screenThread;
    startScreenThread(screenBuffer, &screenThread);

    // Wait for all threads to finish.
    for (int j = 0; j < i; j++) {
        pthread_join(threads[j], NULL);
    }
    pthread_join(disThread, NULL);
    for (int i = 0; i < 3; i++) {
        pthread_join(coThreads[i], NULL);
    }
    pthread_join(screenThread, NULL);
    return 0;
}
