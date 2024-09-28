#ifndef COEDITOR_H
#define COEDITOR_H

#include "BoundedBuffer.h"
#include "UnboundedBuffer.h"

typedef struct CoEditor {
    UnboundedBuffer* source;
    BoundedBuffer* destination;
    bool done;
    int which;
} CoEditor;

// initiates the co editor, gets the source unbounded buffer, and the destination bounded buffer
CoEditor* initCoEditor(BoundedBuffer* destination, UnboundedBuffer* source, int which);
void* startCoEditor(void* self);

#endif // COEDITOR_H