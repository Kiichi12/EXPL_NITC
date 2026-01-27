#include "labels.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static LabelEntry labelTable[MAX_LABELS];
static int labelCount = 0;

LoopContext loopStack[100];
static int loopDepth = 0;


int getLabel()
{
    return labelCount++;    
}

void initLabelTable() {
    labelCount = 0;
    loopDepth = 0;
}

void addLabel(int label, int address) {
    labelTable[labelCount].label = label;
    labelTable[labelCount].address = address;
    labelCount++;
}

int getLabelAddress(int label) {
    for (int i = 0; i < labelCount; i++) {
        if (labelTable[i].label == label)
            return labelTable[i].address;
    }
    printf("Error: Undefined label L%d\n", label);
    exit(1);
}

void emitLabel(FILE *target_file, int label) {
    fprintf(target_file, "L%d:\n", label);
}

void buildLabelTable(FILE *fp)
{
    char line[(CODE_END - CODE_START)/2];
    int address = CODE_START;

    initLabelTable();
    rewind(fp);
    for(int  i = 0; i < 8; i++)
    {
        fgets(line, sizeof(line), fp);
    }
    while (fgets(line, sizeof(line), fp)) {

        if (line[0] == 'L' && (line[1] >= '0' && line[1] <= '9')) {
            int label;
            sscanf(line, "L%d:", &label);
            addLabel(label, address);
            
        } else {
            // Real instruction
            address=address+INSTR_SIZE;
            if(address >= CODE_END)
            {
                fprintf(stderr, "Error: Code area exceeded\n");
                exit(1);
            }
        }
    }
}

void translateLabels(FILE *in, FILE *out)
{
    char line[CODE_END - CODE_START];
    rewind(in);

    while (fgets(line, sizeof(line), in)) {

        // Skip label lines
        if (line[0] == 'L' && (line[1] >= '0' && line[1] <= '9'))
            continue;

        // JMP Lx
        if (strncmp(line, "JMP L", 5) == 0) {
            int label;
            sscanf(line, "JMP L%d", &label);
            fprintf(out, "JMP %d\n", getLabelAddress(label));
        }

        // JZ Rx, Lx
        else if (strncmp(line, "JZ", 2) == 0) {
            int reg, label;
            sscanf(line, "JZ R%d, L%d", &reg, &label);
            fprintf(out, "JZ R%d, %d\n", reg, getLabelAddress(label));
        }

        // JNZ Rx, Lx (for do-while)
        else if (strncmp(line, "JNZ", 3) == 0) {
            int reg, label;
            sscanf(line, "JNZ R%d, L%d", &reg, &label);
            fprintf(out, "JNZ R%d, %d\n", reg, getLabelAddress(label));
        }

        // Normal instruction
        else {
            fprintf(out, "%s", line);
        }
    }
}

void pushLoopContext(int breakLabel, int continueLabel)
{
    if (loopDepth >= 100) {
        fprintf(stderr, "Error: Loop nesting depth exceeded\n");
        exit(1);
    }
    loopStack[loopDepth].breakLabel = breakLabel;
    loopStack[loopDepth].continueLabel = continueLabel;
    loopDepth++;
}

void popLoopContext()
{
    if (loopDepth > 0) {
        loopDepth--;
    }
}

LoopContext* getCurrentLoopContext()
{
    if (loopDepth > 0) {
        return &loopStack[loopDepth - 1];
    }
    return NULL;
}

int isInsideLoop()
{
    return loopDepth > 0;
}



