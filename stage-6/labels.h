#ifndef LABELS_H
#define LABELS_H

#include <stdio.h>
#include "constants.h"

typedef struct {
    char *name;    // To support both L and F labels
    int address;
} LabelEntry;

typedef struct {
    int breakLabel;
    int continueLabel;
} LoopContext;

int getLabel();
void emitLabel(FILE *target_file, int label);
void emitFuncLabel(FILE *target_file, int flabel);

void addLabel(char *name, int address);
int getLabelAddress(char *name);

void buildLabelTable(FILE *fp);
void translateLabels(FILE *in, FILE *out);

// Loop Stack
void pushLoopContext(int breakLabel, int continueLabel);
void popLoopContext();
LoopContext* getCurrentLoopContext();
int isInsideLoop();

#endif
