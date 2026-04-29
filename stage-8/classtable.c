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

int isDescendant(ClassTableEntry *child, ClassTableEntry *ancestor)
{
    ClassTableEntry *c = child;
    while(c)
    {
        if(c == ancestor) 
        {
            return 1;
        }
        c = c->parent;
    }
    return 0;
}

Paramstruct *copyParamList(Paramstruct *pparam)
{
    if(!pparam)
        return NULL;

    Paramstruct *head = NULL;
    

    while(pparam)
    {
        if(pparam->type == TYPE_NULL) 
        {
            return pparam;
        }
        Paramstruct *temp = malloc(sizeof(Paramstruct));
        temp->name = strdup(pparam->name);
        temp->type = pparam->type;
        temp->typeEntry = pparam->typeEntry;
        temp->ptrLevel = pparam->ptrLevel;
        temp->next = NULL;
        
        if(!head)
            head = temp;
        else
        {
            Paramstruct *t = head;
            while(t->next) t = t->next;
            t->next = temp;
        }
        
        pparam = pparam->next;
    }
    
    return head;
}

ClassTableEntry *installClass(char *name, char *parentName)
{
    if(lookupClass(name)) {
        fprintf(stderr, "Classtable.c: installClass: Error: Class '%s' already defined\n", name);
        exit(1);
    }

    ClassTableEntry *parent = NULL;

    if(parentName)
    {
        parent = lookupClass(parentName);
        if(!parent)
        {
            fprintf(stderr, "Classtable.c: installClass: Error: Parent class '%s' not found\n", parentName);
            exit(1);
        }
    }
    
    TypeTableEntry *typeEntry = installType(name);

    ClassTableEntry *c = malloc(sizeof(ClassTableEntry));
    if (!c) {
        fprintf(stderr, "Classtable.c: installClass: Error: Out of memory\n");
        exit(1);
    }
    c->name = strdup(name);
    c->classId = nextClassId++;
    c->methods = NULL;
    c->type = NULL;
    
    if(parent)
    {
        MethodEntry *pm = parent->methods;

        while(pm)
        {
            MethodEntry *m = malloc(sizeof(MethodEntry));
            m->name = strdup(pm->name);
            m->retType = pm->retType;
            m->params = copyParamList(pm->params);
            m->flabel = pm->flabel;
            m->next = NULL;
            if(!c->methods)
                c->methods = m;
            else
            {
                MethodEntry *t = c->methods;
                while(t->next) t = t->next;
                t->next = m;
            }
            
            pm = pm->next;
        }

        if(parent->type->fields)
        {
            Fieldstruct *pf = parent->type->fields;
            while(pf)
            {
                Fieldstruct *f = malloc(sizeof(Fieldstruct));
                f->name = strdup(pf->name);
                f->typeEntry = pf->typeEntry;
                f->fieldOffset = pf->fieldOffset;
                f->next = NULL;
                if (!typeEntry->fields)
                    typeEntry->fields = f;
                else
                {
                    // printf("reached here\n");
                    Fieldstruct *t = typeEntry->fields;
                    while(t->next) t = t->next;
                    t->next = f;
                    // printf("got out\n");
                }
                typeEntry->fieldCount++;
                pf = pf->next;
            }
        }
    }

    c->type = typeEntry;
    c->parent = parent;
    // c->methods = NULL;
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

    MethodEntry *pm = lookupMethod(c, methodName);

    if (pm) 
    {
        if(pm->retType != retType || pm->retTypeEntry != retTypeEntry)
        {
            fprintf(stderr, "Error: addMethod: Return type mismatch when overriding '%s' in class '%s'\n", methodName, c->name);
            exit(1);
        }

        if(!CompareParamLists(pm->params, params))
        {
            if(!(pm->params->type==TYPE_NULL && !params))
            {
                fprintf(stderr, "Error: addMethod: Parameter list mismatch when overriding '%s' in class '%s'\n", methodName, c->name);
                exit(1);
            }
        }
        pm->flabel = GetNextFunctionLabel();
        return pm;
    }

    MethodEntry *m  = malloc(sizeof(MethodEntry));
    m->name = strdup(methodName);
    m->retType = retType;
    m->retTypeEntry = retTypeEntry;
    if(params)
    {
        m->params = params;
    }
    else
    {
        Paramstruct *temp = malloc(sizeof(Paramstruct));
        temp->type = TYPE_NULL;
        temp->name = NULL;
        temp->next = NULL;
        m->params = temp;
    }
    m->flabel = GetNextFunctionLabel();
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
