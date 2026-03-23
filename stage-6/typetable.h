#ifndef TYPETABLE_H
#define TYPETABLE_H

#include "constants.h"
#include <stdio.h>

typedef struct TypeTableEntry TypeTableEntry;

typedef struct Fieldstruct
{
    char *name;
    TypeTableEntry *typeEntry;
    int fieldOffset;
    struct Fieldstruct *next;
} Fieldstruct;

struct TypeTableEntry
{
    char *name;
    int typeId;
    int fieldCount;
    Fieldstruct *fields;
    TypeTableEntry *next;
};

extern TypeTableEntry *typeTableHead;

void initTypeTable(void);

TypeTableEntry *lookupType(const char *name);
Fieldstruct *lookupField(TypeTableEntry *udeftype, const char *fieldName);
TypeTableEntry *installType(const char *name);
Fieldstruct *addField(TypeTableEntry *udeftype, const char *fieldName, TypeTableEntry *fieldType);

void printTypeTable(void);

#endif