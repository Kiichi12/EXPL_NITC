#include "memory.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "constants.h"

struct Gsymbol *Ghead = NULL;
static int nextBinding = STACK_START;   

static int nextFunctionLabel = 0;

struct Gsymbol *Lookup(char *name)
{
    struct Gsymbol *temp = Ghead;
    while (temp) {
        if (strcmp(temp->name, name) == 0)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void Install(char *name, int type, int size)
{
    if (Lookup(name) != NULL) {
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

void Install1DArray(char *name, int type, int size)
{
    if (Lookup(name) != NULL) {
        fprintf(stderr, "Error: Redeclaration of array %s\n", name);
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

    entry->arrayDim = 1;
    entry->rows = size;       // for convenience
    entry->cols = 1;
    entry->ptrLevel = 0;
}

void Install2DArray(char *name, int type, int rows, int cols)
{
    if (Lookup(name) != NULL) {
        fprintf(stderr, "Error: Redeclaration of array %s\n", name);
        exit(1);
    }

    struct Gsymbol *entry = malloc(sizeof(struct Gsymbol));
    entry->name = strdup(name);
    entry->type = type;
    entry->size = rows * cols;   // total cells
    entry->binding = nextBinding;
    nextBinding += entry->size;
    entry->next = Ghead;
    Ghead = entry;

    entry->arrayDim = 2;
    entry->rows = rows;
    entry->cols = cols;
    entry->ptrLevel = 0;
}

void InstallPointer(char *name, int type, int ptrLevel)
{
    if (Lookup(name) != NULL) {
        fprintf(stderr, "Error: Redeclaration of variable %s\n", name);
        exit(1);
    }

    struct Gsymbol *entry = malloc(sizeof(struct Gsymbol));
    entry->name = strdup(name);
    entry->type = type;
    entry->size = 1;                // pointer itself is 1 word
    entry->binding = nextBinding;
    nextBinding += 1;
    entry->next = Ghead;
    Ghead = entry;

    entry->arrayDim = 0;
    entry->rows = 0;
    entry->cols = 0;
    entry->ptrLevel = ptrLevel;     // 1 for *, 2 for **
}


// ============================================================================
// SYMBOL TABLE PRINTING AND UTILITIES
// ============================================================================

void printSymbolTable(void) {
    struct Gsymbol *temp = Ghead;
    
    printf("\n=================GLOBAL SYMBOL TABLE===================\n");
    
    if (temp == NULL) {
        printf("(Empty symbol table)\n\n");
        return;
    }
    
    while (temp) {
        printf("\n┌─ Name: %s\n", temp->name);
        
        // Determine if it's a function or variable
        if (temp->paramlist != NULL) {
            // FUNCTION ENTRY
            printf("│  Category: FUNCTION\n");
            printf("│  Return Type: %s\n", 
                   temp->type == TYPE_INT ? "int" : 
                   temp->type == TYPE_STRING ? "string" : "unknown");
            printf("│  Function Label: F%d\n", temp->flabel);
            printf("│  Parameters: ");
            if(temp->paramlist->type==TYPE_NONE)
            {
                printf("No arguments");
            }
            else
                PrintParamList(temp->paramlist);
            printf("\n");
        } else {
            // VARIABLE ENTRY
            printf("│  Category: VARIABLE\n");
            printf("│  Type: %s\n", 
                   temp->type == TYPE_INT ? "int" : 
                   temp->type == TYPE_STRING ? "string" : 
                   temp->type == TYPE_POINTER ? "pointer" : "unknown");
            printf("│  Size: %d\n", temp->size);
            printf("│  Binding: %d\n", temp->binding);
            
            if (temp->arrayDim == 1) {
                printf("│  Array Type: 1D Array (size: %d)\n", temp->rows);
            } else if (temp->arrayDim == 2) {
                printf("│  Array Type: 2D Array (%d x %d)\n", temp->rows, temp->cols);
            } else if (temp->ptrLevel > 0) {
                printf("│  Pointer Level: %d\n", temp->ptrLevel);
            } else {
                printf("│  Array Type: Scalar\n");
            }
        }
        
        temp = temp->next;
    }
    
    printf("\n===============================================\n");
}

// Print parameter list (utility)
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
        printf("%s: %s", p->name, 
               p->type == TYPE_INT ? "int" : 
               p->type == TYPE_STRING ? "string" : "unknown");
        p = p->next;
        first = 0;
    }
    printf(")");
}

// Compare two parameter lists (for Task 2: verify declaration matches definition)
int CompareParamLists(struct Paramstruct *list1, struct Paramstruct *list2) {
    // Both NULL
    if (list1 == NULL && list2 == NULL)
        return 1;
    
    // One NULL, other not
    if (list1 == NULL || list2 == NULL)
        return 0;
    
    // Compare type and count
    int count1 = CountParams(list1);
    int count2 = CountParams(list2);
    
    if (count1 != count2)
        return 0;
    
    // Compare each parameter
    while (list1 && list2) {
        if (list1->type != list2->type)
            return 0;
        if (strcmp(list1->name, list2->name) != 0)
            return 0;
        list1 = list1->next;
        list2 = list2->next;
    }
    
    return 1;
}

void moveStackPointer(FILE* target_file) {
    if (Ghead) {
        fprintf(target_file, "MOV SP, %d\n", Ghead->binding + Ghead->size);
    } else {
        printf("No variables declared\n");
    }
}

// Reset global symbol table (for testing multiple programs)
void resetGlobalSymbolTable(void) {
    struct Gsymbol *temp = Ghead;
    while (temp) {
        struct Gsymbol *next = temp->next;
        free(temp->name);
        
        // Free parameter list if it's a function
        if (temp->paramlist) {
            struct Paramstruct *p = temp->paramlist;
            while (p) {
                struct Paramstruct *pnext = p->next;
                free(p->name);
                free(p);
                p = pnext;
            }
        }
        
        free(temp);
        temp = next;
    }
    
    Ghead = NULL;
    nextBinding = STACK_START;
    nextFunctionLabel = 0;
}

// ============================================================================
// NEW FOR STAGE 5: FUNCTION MANAGEMENT
// ============================================================================

// Create a single parameter
struct Paramstruct *CreateParam(char *name, int type, int ptrLevel) {
    struct Paramstruct *p = malloc(sizeof(struct Paramstruct));
    p->name = strdup(name);
    p->type = type;
    p->ptrLevel = ptrLevel; 
    p->next = NULL;
    return p;
}

// append to the paramlist
struct Paramstruct *AppendParam(struct Paramstruct *list, struct Paramstruct *param) {
    if (list == NULL) return param;
    struct Paramstruct *temp = list;
    while (temp->next) temp = temp->next;
    temp->next = param;
    return list;
}

// count the number of parameters
int CountParams(struct Paramstruct *list) {
    int count = 0;
    while (list) {
        count++;
        list = list->next;
    }
    return count;
}

// Get and increment function label
int GetNextFunctionLabel(void) {
    return nextFunctionLabel++;
}

// Reset function labels (useful for testing)
void ResetFunctionLabels(void) {
    nextFunctionLabel = 0;
}

// Install a function entry in global symbol table
void InstallFunction(char *name, int type, struct Paramstruct *paramlist) {
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
    entry->size = 0;              // Not applicable for functions
    entry->binding = 0;           // Will be set during code generation
    entry->arrayDim = 0;
    entry->rows = 0;
    entry->cols = 0;
    entry->ptrLevel = 0;
    
    // Function-specific fields
    if(paramlist != NULL)
        entry->paramlist = paramlist;
    else
    {
        entry->paramlist = malloc(sizeof(struct Paramstruct)); // so that paramlist is not null and it is identified as a function
        entry->paramlist->type = TYPE_NONE;
    }
    entry->flabel = GetNextFunctionLabel();
    
    entry->next = Ghead;
    Ghead = entry;
}