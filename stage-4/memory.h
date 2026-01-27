#ifndef MEMORY_H
#define MEMORY_H
#include "constants.h"

typedef struct Gsymbol
{
    char *name;
    enum varType type;          
    int size;      // in words    
    int binding;
    struct Gsymbol *next;

    int arrayDim;  // 0 or 1 or 2    
    int rows;      // for 2D    
    int cols;      // for 2D
    int ptrLevel;  
} Gsymbol;


extern struct Gsymbol *Ghead;

struct Gsymbol *Lookup(char *name);
void Install(char *name, int type, int size);
void Install1DArray(char *name, int type, int size);
void Install2DArray(char *name, int type, int rows, int cols);
void InstallPointer(char *name, int type, int ptrLevel);
void moveStackPointer();

void printSymbolTable();   

#endif
