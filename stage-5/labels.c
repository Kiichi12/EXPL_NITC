#include "labels.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static LabelEntry labelTable[MAX_LABELS * 2]; // Larger table for L and F labels
static int labelEntryCount = 0;
static int currentLabelNum = 0;

LoopContext loopStack[100];
static int loopDepth = 0;

int getLabel() { return currentLabelNum++; }

void addLabel(char *name, int address) {
    labelTable[labelEntryCount].name = strdup(name);
    labelTable[labelEntryCount].address = address;
    labelEntryCount++;
}

int getLabelAddress(char *name) {
    for (int i = 0; i < labelEntryCount; i++) {
        if (strcmp(labelTable[i].name, name) == 0)
            return labelTable[i].address;
    }
    fprintf(stderr, "Error: Undefined label %s\n", name);
    exit(1);
}

void emitLabel(FILE *target_file, int label) 
{ 
    fprintf(target_file, "L%d:\n", label); 
}

void emitFuncLabel(FILE *target_file, int flabel) 
{ 
    fprintf(target_file, "F%d:\n", flabel); 
}

void buildLabelTable(FILE *fp) 
{
    char line[256];
    int address = CODE_START - 16; // Adjust for header
    rewind(fp);

    while (fgets(line, sizeof(line), fp)) {
        // Detect Label (L or F or MAIN)
        if ((line[0] == 'L' || line[0] == 'F' || (line[0] == 'M' && line[1] == 'A')) && strchr(line, ':')) {
            char name[32];
            sscanf(line, "%[^:]", name);
            addLabel(name, address);
        } else {
            address += INSTR_SIZE;
        }
    }
}

void translateLabels(FILE *in, FILE *out) {
    char line[256], op1[32], op2[32];
    rewind(in);
    
    // Copy Header directly (8 lines)
    for(int i=0; i<8; i++) {
        if(fgets(line, sizeof(line), in)) 
        {
            if(line[0] == 'M' && line[1] == 'A')
            {
                fprintf(out, "%d\n", getLabelAddress("MAIN"));
            }
            else
            {
                fprintf(out, "%s", line);
            }
        }
    }

    while (fgets(line, sizeof(line), in)) {
        if (strchr(line, ':')) continue; // Skip label definitions

        // Simple translation for JMP, JZ, JNZ, CALL
        if (sscanf(line, "JMP %s", op1) == 1) {
            fprintf(out, "JMP %d\n", getLabelAddress(op1));
        } else if (sscanf(line, "JZ %[^,], %s", op1, op2) == 2) {
            fprintf(out, "JZ %s, %d\n", op1, getLabelAddress(op2));
        } else if (sscanf(line, "JNZ %[^,], %s", op1, op2) == 2) {
            fprintf(out, "JNZ %s, %d\n", op1, getLabelAddress(op2));
        } 
        else if (sscanf(line, "CALL %s", op1) == 1) {
            if(op1[0] == 'F')
                fprintf(out, "CALL %d\n", getLabelAddress(op1));
            else
                fprintf(out, "CALL %s\n", op1);
        } 
        else {
            fprintf(out, "%s", line);
        }
    }
}

// Loop Stack Implementation
void pushLoopContext(int b, int c) 
{
    loopStack[loopDepth].breakLabel = b;
    loopStack[loopDepth].continueLabel = c;
    loopDepth++;
}
void popLoopContext()
{ 
    if(loopDepth > 0) loopDepth--; 
}

LoopContext* getCurrentLoopContext() 
{ 
    return (loopDepth > 0) ? &loopStack[loopDepth-1] : NULL; 
}

int isInsideLoop() 
{ 
    return loopDepth > 0; 
} 

