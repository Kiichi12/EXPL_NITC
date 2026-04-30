#include "typetable.h"
#include "classtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

TypeTableEntry *typeTableHead = NULL;

static int nextTypeId = TYPE_USERDEF+1;

static TypeTableEntry *primTypeEntry(const char *name, int typeId)
{
    TypeTableEntry *e = malloc(sizeof(TypeTableEntry));
    e->name = strdup(name);
    e->typeId = typeId;
    e->fieldCount = 0;
    e->fields = NULL;
    e->next = NULL;
    return e;
}

void appendEntry(TypeTableEntry *entry)
{
    if (typeTableHead == NULL)
    {
        typeTableHead = entry;
    }
    else
    {
        TypeTableEntry *temp = typeTableHead;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = entry;
    }
}

void initTypeTable(void)
{
    TypeTableEntry *e = primTypeEntry("int", TYPE_INT);
    appendEntry(e);
    
    e = primTypeEntry("string", TYPE_STRING);
    appendEntry(e);
    
    e = primTypeEntry("bool", TYPE_BOOL);
    appendEntry(e);

    e = primTypeEntry("pointer", TYPE_POINTER);
    appendEntry(e);
    
    e = primTypeEntry("void", TYPE_NULL);
    appendEntry(e);

    e = primTypeEntry("null", TYPE_NULL);
    appendEntry(e);
}

TypeTableEntry *lookupType(const char *name)
{
    TypeTableEntry *t = typeTableHead;
    while(t)
    {
        if(strcmp(name, t->name) == 0)
        {
            return t;
        }
        t = t->next;
    }
    return NULL;
}

Fieldstruct *lookupField(TypeTableEntry *udeftype, const char *fieldName)
{
    if (!udeftype)
    {
        return NULL;
    } 
    Fieldstruct *f = udeftype->fields;
    while (f) {
        if (strcmp(f->name, fieldName) == 0)
            return f;
        f = f->next;
    }
    return NULL;
}


TypeTableEntry *installType(const char *name)
{
    if(lookupType(name) != NULL)
    {
        fprintf(stderr, "Error: Type '%s' already defined\n", name);
        exit(1);
    }
    TypeTableEntry *e = malloc(sizeof(TypeTableEntry));
    e->name = strdup(name);
    e->typeId = nextTypeId++;
    e->fieldCount = 0;
    e->fields = NULL;
    e->next = NULL;
    appendEntry(e);
    return e;
}

  

Fieldstruct *addField(TypeTableEntry *udeftype, const char *fieldName, TypeTableEntry *fieldType)
{
    if (udeftype->fieldCount >= MAX_FIELDS_IN_USER_TYPE) 
    {
        fprintf(stderr, "Error: too many member fields in type '%s' (max %d)\n", udeftype->name, MAX_FIELDS_IN_USER_TYPE);
        exit(1);
    }

    if (lookupField(udeftype, fieldName) != NULL) 
    {
        fprintf(stderr, "Error: Duplicate field '%s' in type '%s'\n", fieldName, udeftype->name);
        exit(1);
    }

    Fieldstruct *f = malloc(sizeof(Fieldstruct));
    f->name = strdup(fieldName);

    f->fieldOffset = udeftype->fieldCount;
    udeftype->fieldCount++;

    f->typeEntry = fieldType;

    if(f->typeEntry == NULL)
    {
        printf("FieldName: %s\n typentry is NULL\n", fieldName);
        exit(1);
    }
    f->next = NULL;
    ClassTableEntry *fieldClass = lookupClass(f->typeEntry->name);
    if(fieldClass)
    {
        udeftype->fieldCount++;
        Fieldstruct *vftptr = malloc(sizeof(Fieldstruct));

        vftptr->name = strdup("vftptr");
        vftptr->fieldOffset = udeftype->fieldCount;
        vftptr->typeEntry = NULL;
        vftptr->next = NULL;

        f->next = vftptr;
    }
    Fieldstruct *temp = udeftype->fields;
    if(!temp)
    {
        udeftype->fields = f;
        return f;
    }
    while(temp->next)
    {
        temp = temp->next;
    }
    temp->next = f;
    return f;
}

void printTypeTable(void)
{
    printf("\n============== TYPE TABLE ==============\n");
    TypeTableEntry *t = typeTableHead;
    while (t) {
        printf("Type: %-10s  id=%d  fields=%d\n",
               t->name, t->typeId, t->fieldCount);
        Fieldstruct *f = t->fields;
        while (f) {
            printf("    [%d] %s : %s\n",
                   f->fieldOffset, f->name, f->typeEntry->name);
            f = f->next;
        }
        t = t->next;
    }
    printf("========================================\n");
}
