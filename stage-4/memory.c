#include "memory.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "constants.h"

struct Gsymbol *Ghead = NULL;
static int nextBinding = STACK_START;   // starting address as per spec

struct Gsymbol *Lookup(char *name)
{
    struct Gsymbol *temp = Ghead;
    while (temp) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void Install(char *name, int type, int size)
{
    if (Lookup(name) != NULL) {
        fprintf(stderr, "Error: Redeclaration of variable %s\n", name);
        exit(1);
    }

    struct Gsymbol *entry = malloc(sizeof(struct Gsymbol));
    entry->name = strdup(name);
    entry->type = type;
    entry->size = size;
    entry->binding = nextBinding;
    nextBinding += size;
    entry->next = Ghead;
    Ghead = entry;

    entry->arrayDim = 0;
    entry->rows = 0;
    entry->cols = 0;
    entry->ptrLevel = 0;
}

void Install1DArray(char *name, int type, int size)
{
    if (Lookup(name) != NULL) {
        fprintf(stderr, "Error: Redeclaration of array %s\n", name);
        exit(1);
    }

    struct Gsymbol *entry = malloc(sizeof(struct Gsymbol));
    entry->name = strdup(name);
    entry->type = type;
    entry->size = size;
    entry->binding = nextBinding;
    nextBinding += size;
    entry->next = Ghead;
    Ghead = entry;

    entry->arrayDim = 1;
    entry->rows = size;       // for convenience
    entry->cols = 1;
    entry->ptrLevel = 0;
}

void Install2DArray(char *name, int type, int rows, int cols)
{
    if (Lookup(name) != NULL) {
        fprintf(stderr, "Error: Redeclaration of array %s\n", name);
        exit(1);
    }

    struct Gsymbol *entry = malloc(sizeof(struct Gsymbol));
    entry->name = strdup(name);
    entry->type = type;
    entry->size = rows * cols;   // total cells
    entry->binding = nextBinding;
    nextBinding += entry->size;
    entry->next = Ghead;
    Ghead = entry;

    entry->arrayDim = 2;
    entry->rows = rows;
    entry->cols = cols;
    entry->ptrLevel = 0;
}

void InstallPointer(char *name, int type, int ptrLevel)
{
    if (Lookup(name) != NULL) {
        fprintf(stderr, "Error: Redeclaration of variable %s\n", name);
        exit(1);
    }

    struct Gsymbol *entry = malloc(sizeof(struct Gsymbol));
    entry->name = strdup(name);
    entry->type = type;
    entry->size = 1;                // pointer itself is 1 word
    entry->binding = nextBinding;
    nextBinding += 1;
    entry->next = Ghead;
    Ghead = entry;

    entry->arrayDim = 0;
    entry->rows = 0;
    entry->cols = 0;
    entry->ptrLevel = ptrLevel;     // 1 for *, 2 for **
}


void moveStackPointer(FILE* target_file)
{
    if(Ghead)
    {
        fprintf(target_file, "MOV SP, %d\n",Ghead->binding+Ghead->size);
    }
    else
    {
        printf("No variables declared\n");
    }
}

void printSymbolTable()
{
    struct Gsymbol *temp = Ghead;
    printf("----- Global Symbol Table -----\n");
    while (temp) {
        printf("Name: %s, Type: %d, Size: %d, Binding: %d\n",
               temp->name, temp->type, temp->size, temp->binding);
        temp = temp->next;
    }
}

