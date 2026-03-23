#ifndef MEMORY_H
#define MEMORY_H
#include "constants.h"
#include "typetable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Paramstruct {
    char *name;                  
    enum varType type;                    
    TypeTableEntry *typeEntry;
    int ptrLevel;

    struct Paramstruct *next;    
} Paramstruct;

typedef struct Gsymbol {
    char *name;                  
    enum varType type;
    TypeTableEntry *typeEntry;
    int size;                    
    int binding;                 
    
    int arrayDim;                
    int rows, cols;              
    int ptrLevel;                
    
    Paramstruct *paramlist;
    int flabel;            
    
    struct Gsymbol *next;        
} Gsymbol;

typedef struct Lsymbol {
    char *name;
    enum varType type;
    TypeTableEntry *typeEntry;
    int binding;
    int size;             
    int ptrLevel; 
    
    struct Lsymbol *next;
} Lsymbol;

extern struct Gsymbol *Ghead;

struct Gsymbol *Lookup(char *name);
void Install(char *name, int type, int size);
void Install1DArray(char *name, int type, int size);
void InstallPointer(char *name, int type, int ptrLevel);
void InstallUdefType(char *name, TypeTableEntry *typeEntry);

// function management functions
void InstallFunction(char *name, int type, TypeTableEntry *typeEntry, struct Paramstruct *paramlist);
void InstallParamsToLST(struct Paramstruct *list) ;
void LInstall(char *name, int type, TypeTableEntry *typeEntry, int ptrLevel);
// void verifyFunctionSignature(struct Gsymbol* g, struct TypeInfo* ret, struct Paramstruct* p);
struct Paramstruct *CreateParam(char *name, int type, TypeTableEntry *typeEntry, int ptrLevel); 
struct Paramstruct *AppendParam(struct Paramstruct *list, struct Paramstruct *param);
int CountParams(struct Paramstruct *list);
int GetNextFunctionLabel(void);
void ResetFunctionLabels(void);

int CompareParamLists(struct Paramstruct *list1, struct Paramstruct *list2);   

struct Lsymbol *LLookup(char *name);

void moveStackPointer(FILE * target_file);
void locAlloc(FILE * target_file);

void printSymbolTable();
void printLST();
void PrintParamList(struct Paramstruct *list);

void resetLocalSymbolTable();
void resetGlobalSymbolTable(void);

#endif
