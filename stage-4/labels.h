#ifndef LABELS_H
#define LABELS_H
#include <stdio.h>
#include "constants.h"

typedef struct {
    int label;
    int address;
} LabelEntry;

typedef struct {
    int breakLabel;
    int continueLabel;
} LoopContext;

int getLabel();
void emitLabel(FILE *target_file, int label);

void initLabelTable();
void addLabel(int label, int address);
int getLabelAddress(int label);

void buildLabelTable(FILE *fp);
void translateLabels(FILE *in, FILE *out);


// extern LoopContext loopStack[100];
// extern int loopDepth;

void pushLoopContext(int breakLabel, int continueLabel);
void popLoopContext();
LoopContext* getCurrentLoopContext();
int isInsideLoop();



#endif
