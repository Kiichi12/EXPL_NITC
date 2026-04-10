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
    TypeTableEntry *type;   /* stores the fields, same as user-defined type  */
    MethodEntry *methods;

    /* Stage 8: single-inheritance support */
    struct ClassTableEntry *parent; /* NULL if no parent */

    struct ClassTableEntry *next;
};

extern ClassTableEntry *classTableHead;

void initClassTable();

ClassTableEntry *lookupClass(char *name);
MethodEntry     *lookupMethod(ClassTableEntry *cls, char *methodName);

ClassTableEntry *findClassForMethod(char *methodName);

/*
 * installClass – Stage 8 version.
 *   parentName  : name of the parent class, or NULL for a root class.
 *
 * When parentName is non-NULL the function:
 *   1. Copies all member fields of the parent into the new class's TypeTableEntry
 *      (same order, same offsets).
 *   2. Copies the signatures and labels of all parent methods into the new
 *      class's method list (inherited methods keep the parent's flabel).
 */
ClassTableEntry *installClass(char *name, char *parentName);

/*
 * addMethod – same as before but now handles overriding:
 *   - If a method with the same name already exists in cls->methods (copied
 *     from parent), its flabel is updated to the new label and a new GST entry
 *     is created.  The signature must match exactly.
 *   - Otherwise a brand-new method entry is appended.
 */
MethodEntry *addMethod(ClassTableEntry *cls, char *methodName,
                       enum varType retType, TypeTableEntry *retTypeEntry,
                       Paramstruct *params);

/*
 * isDescendant – returns 1 if 'child' is the same class as 'ancestor' or is a
 * (direct or indirect) subclass of 'ancestor', 0 otherwise.
 */
int isDescendant(ClassTableEntry *child, ClassTableEntry *ancestor);

void printClassTable();

#endif /* CLASSTABLE_H */
