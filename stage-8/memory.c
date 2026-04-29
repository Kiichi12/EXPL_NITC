#include "memory.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "constants.h"
#include "register.h"

struct Gsymbol *Ghead = NULL;
static struct Lsymbol *Lhead = NULL;

static int nextBinding = STACK_START; 

static int nextLocalBinding = 1;

static int nextFunctionLabel = 0;

void advanceNextBinding(int amount)
{
    nextBinding += amount;
}

struct Gsymbol *Lookup(char *name)
{
    struct Gsymbol *temp = Ghead;
    while (temp) 
    {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

struct Lsymbol *LLookup(char *name)
{
    struct Lsymbol *temp = Lhead;
    while(temp)
    {
        if(strcmp(temp->name, name) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void Install(char *name, int type, int size)
{
    if (Lookup(name) != NULL) 
    {
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

void InstallUdefType(char *name, TypeTableEntry *typeEntry)
{
    if (Lookup(name) != NULL) 
    {
        fprintf(stderr, "Error: Redeclaration of variable %s\n", name);
        exit(1);
    }

    struct Gsymbol *entry = malloc(sizeof(struct Gsymbol));
    entry->name = strdup(name);
    entry->type = TYPE_USERDEF;
    entry->typeEntry = typeEntry;
    entry->size = 1;    
    entry->binding = nextBinding;
    nextBinding++;
    entry->next = Ghead;
    Ghead = entry;

    entry->arrayDim = 0;
    entry->rows = 0;
    entry->cols = 0;
    entry->ptrLevel = 0;
}

void Install1DArray(char *name, int type, int size)
{
    if (Lookup(name) != NULL) 
    {
        fprintf(stderr, "Error: Redeclaration of array %s\n", name);
        exit(1);
    }

    struct Gsymbol *entry = malloc(sizeof(struct Gsymbol));
    entry->name = strdup(name);
    entry->type = type;
    entry->typeEntry = NULL;
    entry->size = size;
    entry->binding = nextBinding;
    nextBinding += size;
    entry->next = Ghead;
    Ghead = entry;

    entry->arrayDim = 1;
    entry->rows = size; // for convenience
    entry->cols = 1;
    entry->ptrLevel = 0;
}

void InstallPointer(char *name, int type, int ptrLevel)
{
    if (Lookup(name) != NULL) 
    {
        fprintf(stderr, "Error: Redeclaration of variable %s\n", name);
        exit(1);
    }

    struct Gsymbol *entry = malloc(sizeof(struct Gsymbol));
    entry->name = strdup(name);
    entry->type = type;
    entry->typeEntry = NULL;
    entry->size = 1;    
    entry->binding = nextBinding;
    nextBinding += 1;
    entry->next = Ghead;
    Ghead = entry;

    entry->arrayDim = 0;
    entry->rows = 0;
    entry->cols = 0;
    entry->ptrLevel = ptrLevel;     
}

void printSymbolTable(void)
{
    struct Gsymbol *t = Ghead;
    printf("\n=================GLOBAL SYMBOL TABLE===================\n");
    if (!t) { printf("(Empty symbol table)\n\n"); return; }
    while (t)
    {
        printf("\n== Name: %s\n", t->name);
        if (t->paramlist)
        {
            printf("│  Category: FUNCTION\n");
            const char *rtn =
                t->type == TYPE_INT    ? "int"    :
                t->type == TYPE_STRING ? "string" :
                (t->type == TYPE_USERDEF || t->type == TYPE_CLASS) && t->typeEntry
                    ? t->typeEntry->name : "unknown";
            printf("│  Return Type: %s\n", rtn);
            printf("│  Function Label: F%d\n", t->flabel);
            printf("│  Parameters: ");
            if (t->paramlist->type == TYPE_NULL) printf("No arguments");
            else PrintParamList(t->paramlist);
            printf("\n");
        }
        else
        {
            printf("│  Category: VARIABLE\n");
            const char *tn =
                t->type == TYPE_INT    ? "int"  :
                t->type == TYPE_STRING ? "str"  :
                (t->type == TYPE_USERDEF || t->type == TYPE_CLASS) && t->typeEntry
                    ? t->typeEntry->name : "unknown";
            printf("│  Type: %s\n",    tn);
            printf("│  Size: %d\n",    t->size);
            printf("│  Binding: %d\n", t->binding);
            if      (t->arrayDim == 1)  printf("│  Array: 1D (size %d)\n", t->rows);
            else if (t->ptrLevel > 0)   printf("│  Pointer Level: %d\n",   t->ptrLevel);
            else if (t->size == 2)      printf("│  Class variable (2 words)\n");
            else                        printf("│  Scalar\n");
        }
        t = t->next;
    }
    printf("\n===============================================\n");
}
void printLST() {
    struct Lsymbol *temp = Lhead;
    printf("\n---------- LOCAL SYMBOL TABLE ----------\n");
    if (temp == NULL) {
        printf("(No local variables)\n");
    } else {
        printf("%-10s | %-10s | %-8s | %-8s\n", "Name", "Type", "PtrLvl", "Binding");
        printf("----------------------------------------\n");
        while (temp) {
            char *typeName;
            if(temp->type==TYPE_INT)
            {
                typeName = "int";
            }
            else if(temp->type==TYPE_STRING)
            {
                typeName = "str";
            }
            else if((temp->type==TYPE_USERDEF || temp->type == TYPE_CLASS) && temp->typeEntry)
            {
                typeName = temp->typeEntry->name;
            }
            else
            {
                typeName = "unknown";
            }
            printf("%-10s | %-10s | %-8d | %-8d\n", temp->name, typeName, temp->ptrLevel, temp->binding);
            temp = temp->next;
        }
    }
    printf("----------------------------------------\n");
}

void PrintParamList(struct Paramstruct *list) {
    if (list == NULL) {
        printf("(no parameters)");
        return;
    }
    
    printf("(");
    struct Paramstruct *p = list;
    int first = 1;
    while (p) {
        if (!first) printf(", ");
        if(p->type == TYPE_USERDEF && p->typeEntry) 
        {
            printf("%s: %s", p->name, p->typeEntry->name);
        }
        else 
        {
            printf("%s: %s", p->name, 
                p->type == TYPE_INT ? "int" : 
                p->type == TYPE_STRING ? "string" : "unknown");
        }
        p = p->next;
        first = 0;
    }
    printf(")");
}

int CompareParamLists(struct Paramstruct *list1, struct Paramstruct *list2) {
    if (list1 == NULL && list2 == NULL)
        return 1;
    
    if (list1 == NULL || list2 == NULL)
    {
        return 0;
    }

    if(list1->type == list2->type && list1->type == TYPE_NULL)
    {
        // printf("memory.c: Function with no args\n");
        return 1;
    }
    
    int count1 = CountParams(list1);
    int count2 = CountParams(list2);
    
    if (count1 != count2)
        return 0;
    
    while (list1 && list2) 
    {
        if((list1->type == TYPE_USERDEF || list1->type == TYPE_CLASS || list2->type == TYPE_USERDEF || list2->type == TYPE_CLASS) && (list1->typeEntry != list2->typeEntry))
        {
            printf("memory.c: Type mismatch in parameter list(udeftype or class)\n");
            return 0;
        }
        else if (list1->type != list2->type)
        {
            printf("memory.c: Type mismatch in parameter list\n");
            return 0;
        }
        else if (strcmp(list1->name, list2->name) != 0)
        {
            printf("memory.c: Name mismatch in parameter list\n");
            return 0;
        }
        list1 = list1->next;
        list2 = list2->next;
    }
    
    return 1;
}

void moveStackPointer(FILE* target_file) 
{
    if (Ghead || nextBinding > STACK_START) 
    {
        printf("next binding: %d\n", nextBinding);
        fprintf(target_file, "MOV SP, %d\n", nextBinding - 1);
    } 
    else 
    {
        fprintf(target_file, "MOV SP, %d\n", STACK_START - 1);
    }
    fprintf(target_file, "MOV BP, SP\n");
    fprintf(target_file, "PUSH R0\n");  // return value of MAIN
}

void locAlloc(FILE * target_file)
{
    if(Lhead)
    {    
        struct Lsymbol* l = Lhead;
        while(l)
        { 
            if(l->binding > 0) 
            {
                // if(l->size > 1)
                fprintf(target_file, "ADD SP, %d\n", l->size);
                // fprintf(target_file, "PUSH R0\n"); // must change to size based addition to SP
            }
            l=l->next; 
        }
    }
}

struct Paramstruct *CreateParam(char *name, int type, TypeTableEntry *typeEntry, int ptrLevel) {
    struct Paramstruct *p = malloc(sizeof(struct Paramstruct));
    p->name = strdup(name);
    p->type = type;
    p->typeEntry = typeEntry;
    p->ptrLevel = ptrLevel; 
    p->next = NULL;
    return p;
}

struct Paramstruct *AppendParam(struct Paramstruct *list, struct Paramstruct *param) {
    if (list == NULL) return param;
    struct Paramstruct *temp = list;
    while (temp->next) temp = temp->next;
    temp->next = param;
    return list;
}

int CountParams(struct Paramstruct *list) {
    int count = 0;
    while (list) {
        count++;
        list = list->next;
    }
    return count;
}

int GetNextFunctionLabel(void) {
    return nextFunctionLabel++;
}

void ResetFunctionLabels(void) {
    nextFunctionLabel = 0;
}

void InstallFunction(char *name, int type, TypeTableEntry *typeEntry, struct Paramstruct *paramlist) {
    if (Lookup(name) != NULL) {
        fprintf(stderr, "Error: Redeclaration of function/variable %s\n", name);
        exit(1);
    }
    
    struct Gsymbol *entry = malloc(sizeof(struct Gsymbol));
    if (entry == NULL) {
        fprintf(stderr, "Memory allocation failed for function entry\n");
        exit(1);
    }
    
    entry->name = strdup(name);
    entry->type = type;
    // printf("func-name:%s, func-type:%d\n", name, type);
    entry->typeEntry = typeEntry;
    entry->size = 0; // not applicable for functions
    entry->binding = 0; // will be set during code generation
    entry->arrayDim = 0;
    entry->rows = 0;
    entry->cols = 0;
    entry->ptrLevel = 0;
    
    if(paramlist != NULL)
        entry->paramlist = paramlist;
    else
    {
        entry->paramlist = malloc(sizeof(struct Paramstruct));
        entry->paramlist->type = TYPE_NULL;
    }
    entry->flabel = GetNextFunctionLabel();
    
    entry->next = Ghead;
    Ghead = entry;
}

// void verifyFunctionSignature(struct Gsymbol* g, struct TypeInfo* ret, struct Paramstruct* p) 
// {
//     if(!g) 
//     { 
//         printf("Func not declared\n"); 
//         exit(1); 
//     }
//     if(g->type != ret->type || !CompareParamLists(g->paramlist, p)) 
//     {
//         printf("Signature mismatch for %s\n", g->name); 
//         exit(1);
//     }
// }

void LInstall(char *name, int type, TypeTableEntry *typeEntry, int ptrLevel) 
{
    if (LLookup(name)) {
        fprintf(stderr, "Error: Local variable %s redeclared\n", name);
        exit(1);
    }
    struct Lsymbol *entry = malloc(sizeof(struct Lsymbol));
    entry->name = strdup(name);
    // printf("Name: %s\n", name);
    entry->type = type;
    // printf("Type: %d\n", type);
    entry->typeEntry = typeEntry;
    entry->ptrLevel = ptrLevel;
    entry->binding = nextLocalBinding; 
    entry->next = Lhead;
    Lhead = entry;

    if (type == TYPE_CLASS) 
    {
        entry->size = 2;
        nextLocalBinding += 2;
    } 
    else 
    {
        entry->size = 1;
        nextLocalBinding += 1;
    }
}

void resetLocalSymbolTable() {
    struct Lsymbol *temp = Lhead;
    while (temp) {
        struct Lsymbol *next = temp->next;
        free(temp->name);
        free(temp);
        temp = next;
    }
    Lhead = NULL;
    nextLocalBinding = 1; 
}

void InstallParamsToLST(struct Paramstruct *list) 
{
    int argOffset = -3;
    struct Paramstruct *p = list;
    while (p) {
        struct Lsymbol *entry = malloc(sizeof(struct Lsymbol));
        entry->name = strdup(p->name);
        entry->type = p->type;
        entry->typeEntry = p->typeEntry;
        entry->ptrLevel = p->ptrLevel;
        entry->binding = argOffset--; 
        entry->next = Lhead;
        Lhead = entry;
        p = p->next;
    }
}

void InstallParamsToLSTMethod(struct Paramstruct *list, TypeTableEntry *classType)
{
    struct Lsymbol *selfEntry = malloc(sizeof(struct Lsymbol));
    selfEntry->name = strdup("self");
    selfEntry->type = TYPE_CLASS;
    selfEntry->typeEntry = classType;
    selfEntry->ptrLevel = 0;
    selfEntry->binding = -3;
    selfEntry->next = Lhead;
    Lhead = selfEntry;
    
    struct Paramstruct *p = list;
    int argOffset = -5;
    while (p) {
        if(p->type == TYPE_NULL) 
        {
            break;
        }
        struct Lsymbol *entry = malloc(sizeof(struct Lsymbol));
        entry->name = strdup(p->name);
        entry->type = p->type;
        entry->typeEntry = p->typeEntry;
        entry->ptrLevel = p->ptrLevel;
        entry->binding = argOffset--; 
        entry->next = Lhead;
        Lhead = entry;
        p = p->next;
    }
}
