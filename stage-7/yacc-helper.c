#include "yacc-helper.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern struct Gsymbol *Ghead;
extern struct Lsymbol *Lhead;

void handleGdecComplete(void) 
{
    printf("\n--- Global Declarations Complete ---\n");
    printSymbolTable();
}

void handleGidScalar(struct tnode *id, struct TypeInfo *typeData) 
{
    if (typeData->type == TYPE_USERDEF)
    {
        InstallUdefType(id->varname, typeData->typeEntry);
    }
    else if (typeData->ptrLevel > 0) 
    {
        InstallPointer(id->varname, typeData->type, typeData->ptrLevel);
    } 
    else 
    {
        Install(id->varname, typeData->type, 1);
    }
}

void handleGidArray1D(struct tnode *id, struct TypeInfo *typeData, int size) 
{
    if (typeData->type == TYPE_USERDEF)
    {
        Install1DArray(id->varname, TYPE_USERDEF, size);
        struct Gsymbol *e;
        e = Lookup(id->varname);
        e->typeEntry = typeData->typeEntry;
    }
    else 
    {
        Install1DArray(id->varname, typeData->type, size);
    }
}

void handleGidFunction(struct tnode *id, struct TypeInfo *typeData, struct Paramstruct *params) {
    InstallFunction(id->varname, typeData->type, typeData->typeEntry, params);
}

void handleParamInstall(struct Paramstruct *params) {
    InstallParamsToLST(params);
}

void handleParamInstallMethod(struct Paramstruct *params, ClassTableEntry *cls) 
{
    InstallParamsToLSTMethod(params, cls->type);
}

void handleLidInstall(char *name, struct TypeInfo *typeData) {
    LInstall(name, typeData->type, typeData->typeEntry, typeData->ptrLevel);
}

int verifyFunctionSignature(struct Gsymbol *g, struct TypeInfo *retType, struct Paramstruct *params) {
    if (!g) {
        yyerror("Function not declared");
        exit(1);
    }
    if((retType->type == TYPE_USERDEF || retType->type == TYPE_CLASS) && g->typeEntry != retType->typeEntry) {
        yyerror("Function definition does not match declaration(udeftype or class)");
        exit(1);
    }
    if ((g->type && retType->type && g->type != retType->type) || !CompareParamLists(g->paramlist, params)) {
        printf("g->type: %d, retType->type: %d, g->type != retType->type: %d\n", g->type, retType->type, g->type != retType->type);
        yyerror("Function definition does not match declaration");
        exit(1);
    }
    return 1;
}

void handleFdefPrint(char *funcName, struct tnode *body) {
    printf("\n========================================\n");
    printf("FUNCTION: %s\n", funcName);
    printLST();
    printf("AST for function %s:\n", funcName);
    printAST(body, 0);
    printf("========================================\n");
    // resetLocalSymbolTable();
}

void handleFdefNoArgsPrint(char *funcName, struct tnode *body) {
    printf("\n========================================\n");
    printf("FUNCTION: %s (No Args)\n", funcName);
    printLST();
    printf("AST for function %s:\n", funcName);
    printAST(body, 0);
    printf("========================================\n");
    // resetLocalSymbolTable();
}

void handleMainPrint(struct tnode *body) {
    printf("\n========================================\n");
    printf("FUNCTION: main\n");
    printLST();
    printf("AST for main:\n");
    printAST(body, 0);
    printf("========================================\n");
}
