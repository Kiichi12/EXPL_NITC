#ifndef CLASSTABLE_H
#define CLASSTABLE_H

#include "constants.h"
#include "typetable.h"
#include "memory.h"  
#include <stdio.h>

typedef struct ClassTableEntry ClassTableEntry;

typedef struct MethodEntry
{
    char *name;
    enum varType retType;
    TypeTableEntry *retTypeEntry;
    Paramstruct *params;
    int flabel;

    struct MethodEntry *next;
} MethodEntry;

struct ClassTableEntry
{
    char *name;
    int classId;
    TypeTableEntry *type; // stores the fields just like in userdeftype
    MethodEntry *methods;

    struct ClassTableEntry *next;
};

extern ClassTableEntry *classTableHead;

void initClassTable();

ClassTableEntry *lookupClass(char *name);
MethodEntry *lookupMethod(ClassTableEntry *cls, char *methodName);

ClassTableEntry *findClassForMethod(char *methodName);

ClassTableEntry *installClass(char *name);

MethodEntry *addMethod(ClassTableEntry *cls, char *methodName, enum varType retType, TypeTableEntry *retTypeEntry, Paramstruct *params);

void printClassTable();

#endif
