#include "classtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ClassTableEntry *classTableHead = NULL;
static int nextClassId = 1;

void initClassTable()
{
    classTableHead = NULL;
    nextClassId = 1;
}

void appendClassEntry(ClassTableEntry *entry)
{
    if (!classTableHead)
    {
        classTableHead = entry;
        return;
    }
    ClassTableEntry *t = classTableHead;
    while (t->next) t = t->next;
    t->next = entry;
}

ClassTableEntry *installClass(char *name)
{
    if(lookupClass(name)) {
        fprintf(stderr, "Error: Class '%s' already defined\n", name);
        exit(1);
    }
    
    TypeTableEntry *typeEntry = installType(name);

    ClassTableEntry *c = malloc(sizeof(ClassTableEntry));
    if (!c) {
        fprintf(stderr, "Error: Out of memory in installClass\n");
        exit(1);
    }

    c->name = strdup(name);
    c->classId = nextClassId++;
    c->type = typeEntry;
    c->methods = NULL;
    c->next = NULL;
    
    appendClassEntry(c);
    return c;
}

MethodEntry *addMethod(ClassTableEntry *c, char *methodName, enum varType retType, TypeTableEntry *retTypeEntry, Paramstruct *params)
{
    if(!c)
    {
        fprintf(stderr, "Error: addMethod is called with NULL class\n");
        exit(1);
    }

    if (lookupMethod(c, methodName)) {
        fprintf(stderr, "Error: Method '%s' already defined in class '%s'\n", methodName, c->name);
        exit(1);
    }

    InstallFunction(methodName, retType, retTypeEntry, params);

    struct Gsymbol *g = Lookup(methodName);
    int flabel = g->flabel;
    
    MethodEntry *m = malloc(sizeof(MethodEntry));
    if (!m) {
        fprintf(stderr, "Error: Out of memory in addMethod\n");
        exit(1);
    }
    
    m->name = strdup(methodName);
    m->retType = retType;
    m->retTypeEntry = retTypeEntry;
    m->params = params;
    m->next = c->methods;
    m->flabel = flabel;
    m->next = NULL;
    if(!c->methods)
    {
        c->methods = m;
    }
    else
    {
        MethodEntry *t = c->methods;
        while (t->next) 
            t = t->next;
        t->next = m;
    }
    
    return m;
}

ClassTableEntry *findClassForMethod(char *methodName)
{
    ClassTableEntry *c = classTableHead;
    while(c)
    {
        if(lookupMethod(c, methodName))
            return c;
        c = c->next;
    }
    return NULL;
}

ClassTableEntry *lookupClass(char *name)
{
    ClassTableEntry *c = classTableHead;
    while(c)
    {
        if(strcmp(c->name, name) == 0)
            return c;
        c = c->next;
    }
    return NULL;
}

MethodEntry *lookupMethod(ClassTableEntry *cls, char *methodName)
{
    if (!cls) 
        return NULL;
    MethodEntry *m = cls->methods;
    while (m)
    {
        if(strcmp(m->name, methodName) == 0)
            return m;
        m = m->next;
    }
    return NULL;
}

void printClassTable(void)
{
    printf("\n============== CLASS TABLE ==============\n");
    ClassTableEntry *c = classTableHead;
    if (!c)
    {
        printf("(empty)\n");
        printf("=========================================\n");
        return;
    }

    while (c)
    {
        printf("Class : %-12s  classId=%-3d  typeId=%d\n",
               c->name, c->classId,
               c->type ? c->type->typeId : -1);

        /* Fields (stored in the TypeTableEntry, same as structs) */
        if (c->type && c->type->fields)
        {
            printf("  Fields (%d):\n", c->type->fieldCount);
            Fieldstruct *f = c->type->fields;
            while (f)
            {
                printf("    [offset %d] %-12s : %s\n",
                       f->fieldOffset,
                       f->name,
                       f->typeEntry ? f->typeEntry->name : "?");
                f = f->next;
            }
        }
        else
        {
            printf("  Fields : (none)\n");
        }

        /* Methods */
        if (c->methods)
        {
            printf("  Methods:\n");
            MethodEntry *m = c->methods;
            while (m)
            {
                printf("    %-12s  retType=%-2d  label=F%d",
                       m->name, m->retType, m->flabel);
                if (m->retTypeEntry)
                    printf("  retTypeName=%s", m->retTypeEntry->name);
                /* print parameter list */
                if (m->params)
                {
                    printf("  params=(");
                    Paramstruct *p = m->params;
                    int first = 1;
                    while (p)
                    {
                        if (!first) printf(", ");
                        if (p->type == TYPE_USERDEF && p->typeEntry)
                            printf("%s:%s", p->name, p->typeEntry->name);
                        else
                            printf("%s:%d", p->name, p->type);
                        first = 0;
                        p = p->next;
                    }
                    printf(")");
                }
                else
                {
                    printf("  params=(none)");
                }
                printf("\n");
                m = m->next;
            }
        }
        else
        {
            printf("  Methods : (none)\n");
        }

        c = c->next;
        if (c) printf("  ---\n");
    }
    printf("=========================================\n");
}
