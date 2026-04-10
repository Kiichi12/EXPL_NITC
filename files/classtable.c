#include "classtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ClassTableEntry *classTableHead = NULL;
static int nextClassId = 1;

void initClassTable()
{
    classTableHead = NULL;
    nextClassId    = 1;
}

/* ------------------------------------------------------------------ */
/* Internal helpers                                                     */
/* ------------------------------------------------------------------ */

static void appendClassEntry(ClassTableEntry *entry)
{
    if (!classTableHead) { classTableHead = entry; return; }
    ClassTableEntry *t = classTableHead;
    while (t->next) t = t->next;
    t->next = entry;
}

/*
 * Copy a Paramstruct list (deep copy of names; typeEntry pointers are shared).
 */
static Paramstruct *copyParamList(Paramstruct *src)
{
    if (!src) return NULL;
    Paramstruct *head = NULL, *tail = NULL;
    while (src)
    {
        Paramstruct *p = malloc(sizeof(Paramstruct));
        p->name      = strdup(src->name);
        p->type      = src->type;
        p->typeEntry = src->typeEntry;
        p->ptrLevel  = src->ptrLevel;
        p->next      = NULL;
        if (!head) head = p; else tail->next = p;
        tail = p;
        src  = src->next;
    }
    return head;
}

/* ------------------------------------------------------------------ */
/* isDescendant                                                         */
/* ------------------------------------------------------------------ */

int isDescendant(ClassTableEntry *child, ClassTableEntry *ancestor)
{
    ClassTableEntry *c = child;
    while (c)
    {
        if (c == ancestor) return 1;
        c = c->parent;
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/* installClass                                                         */
/* ------------------------------------------------------------------ */

ClassTableEntry *installClass(char *name, char *parentName)
{
    if (lookupClass(name))
    {
        fprintf(stderr, "Error: Class '%s' already defined\n", name);
        exit(1);
    }

    /* Resolve parent (may be NULL) */
    ClassTableEntry *parent = NULL;
    if (parentName)
    {
        parent = lookupClass(parentName);
        if (!parent)
        {
            fprintf(stderr, "Error: Parent class '%s' not defined\n", parentName);
            exit(1);
        }
    }

    /* Create the TypeTableEntry for this class */
    TypeTableEntry *typeEntry = installType(name);

    /* ---- Copy parent fields (same offset, same order) ---- */
    if (parent && parent->type->fields)
    {
        Fieldstruct *pf = parent->type->fields;
        while (pf)
        {
            Fieldstruct *f  = malloc(sizeof(Fieldstruct));
            f->name         = strdup(pf->name);
            f->typeEntry    = pf->typeEntry;
            f->fieldOffset  = pf->fieldOffset;
            f->next         = NULL;

            /* append to typeEntry->fields */
            if (!typeEntry->fields)
                typeEntry->fields = f;
            else
            {
                Fieldstruct *tail = typeEntry->fields;
                while (tail->next) tail = tail->next;
                tail->next = f;
            }
            typeEntry->fieldCount++;
            pf = pf->next;
        }
    }

    /* ---- Build the ClassTableEntry ---- */
    ClassTableEntry *c = malloc(sizeof(ClassTableEntry));
    if (!c) { fprintf(stderr, "Error: Out of memory in installClass\n"); exit(1); }

    c->name    = strdup(name);
    c->classId = nextClassId++;
    c->type    = typeEntry;
    c->methods = NULL;
    c->parent  = parent;
    c->next    = NULL;

    /* ---- Copy parent methods (inherit labels, copy param lists) ---- */
    if (parent)
    {
        MethodEntry *pm = parent->methods;
        while (pm)
        {
            MethodEntry *m  = malloc(sizeof(MethodEntry));
            m->name         = strdup(pm->name);
            m->retType      = pm->retType;
            m->retTypeEntry = pm->retTypeEntry;
            m->params       = copyParamList(pm->params);
            m->flabel       = pm->flabel;   /* inherit parent's label */
            m->next         = NULL;

            /* append */
            if (!c->methods)
                c->methods = m;
            else
            {
                MethodEntry *tail = c->methods;
                while (tail->next) tail = tail->next;
                tail->next = m;
            }
            pm = pm->next;
        }
    }

    appendClassEntry(c);
    return c;
}

/* ------------------------------------------------------------------ */
/* addMethod                                                            */
/* ------------------------------------------------------------------ */

MethodEntry *addMethod(ClassTableEntry *c, char *methodName,
                       enum varType retType, TypeTableEntry *retTypeEntry,
                       Paramstruct *params)
{
    if (!c)
    {
        fprintf(stderr, "Error: addMethod called with NULL class\n");
        exit(1);
    }

    /* Check whether this method was inherited from the parent */
    MethodEntry *existing = lookupMethod(c, methodName);

    if (existing)
    {
        /* ---- Override: the method was inherited ----
         * The signature must match exactly.
         * We just assign a new label (new GST entry) and update flabel.
         */

        /* Verify return type matches */
        if (existing->retType != retType ||
            existing->retTypeEntry != retTypeEntry)
        {
            fprintf(stderr,
                "Error: Return type mismatch when overriding '%s' in class '%s'\n",
                methodName, c->name);
            exit(1);
        }

        /* Verify parameter list matches */
        if (!CompareParamLists(existing->params, params))
        {
            fprintf(stderr,
                "Error: Parameter list mismatch when overriding '%s' in class '%s'\n",
                methodName, c->name);
            exit(1);
        }

        /*
         * Install a NEW GST entry for this class's version of the method.
         * (The parent's GST entry keeps the parent's label.)
         * We use a mangled name to avoid collision: "ClassName_methodName".
         */
        char mangledName[512];
        snprintf(mangledName, sizeof(mangledName), "%s_%s", c->name, methodName);

        /* Don't double-install if somehow already there */
        if (!Lookup(mangledName))
            InstallFunction(mangledName, retType, retTypeEntry, params);

        struct Gsymbol *g = Lookup(mangledName);
        existing->flabel  = g->flabel;

        return existing;
    }

    /* ---- Brand-new method (not present in parent) ---- */

    /* Check if the plain name already exists in GST to avoid redeclaration */
    if (Lookup(methodName))
    {
        fprintf(stderr,
            "Error: Method '%s' already declared (GST conflict) in class '%s'\n",
            methodName, c->name);
        exit(1);
    }

    InstallFunction(methodName, retType, retTypeEntry, params);

    struct Gsymbol *g = Lookup(methodName);
    int flabel        = g->flabel;

    MethodEntry *m  = malloc(sizeof(MethodEntry));
    m->name         = strdup(methodName);
    m->retType      = retType;
    m->retTypeEntry = retTypeEntry;
    m->params       = params;
    m->flabel       = flabel;
    m->next         = NULL;

    if (!c->methods)
        c->methods = m;
    else
    {
        MethodEntry *tail = c->methods;
        while (tail->next) tail = tail->next;
        tail->next = m;
    }

    return m;
}

/* ------------------------------------------------------------------ */
/* Lookup helpers                                                       */
/* ------------------------------------------------------------------ */

ClassTableEntry *findClassForMethod(char *methodName)
{
    ClassTableEntry *c = classTableHead;
    while (c)
    {
        if (lookupMethod(c, methodName)) return c;
        c = c->next;
    }
    return NULL;
}

ClassTableEntry *lookupClass(char *name)
{
    ClassTableEntry *c = classTableHead;
    while (c)
    {
        if (strcmp(c->name, name) == 0) return c;
        c = c->next;
    }
    return NULL;
}

MethodEntry *lookupMethod(ClassTableEntry *cls, char *methodName)
{
    if (!cls) return NULL;
    MethodEntry *m = cls->methods;
    while (m)
    {
        if (strcmp(m->name, methodName) == 0) return m;
        m = m->next;
    }
    return NULL;
}

/* ------------------------------------------------------------------ */
/* printClassTable                                                      */
/* ------------------------------------------------------------------ */

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
        printf("Class : %-12s  classId=%-3d  typeId=%d",
               c->name, c->classId,
               c->type ? c->type->typeId : -1);
        if (c->parent)
            printf("  extends=%s", c->parent->name);
        printf("\n");

        /* Fields */
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
            printf("  Fields : (none)\n");

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
                    printf("  params=(none)");
                printf("\n");
                m = m->next;
            }
        }
        else
            printf("  Methods : (none)\n");

        c = c->next;
        if (c) printf("  ---\n");
    }
    printf("=========================================\n");
}
