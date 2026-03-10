#include "yacc-helper.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// External globals from memory.c
extern struct Gsymbol *Ghead;
extern struct Lsymbol *Lhead;

// Action implementations

void handleGdeclComplete(void) {
    printf("\n--- Global Declarations Complete ---\n");
    printSymbolTable();
}

void handleGidScalar(struct tnode *id, struct TypeInfo *typeData) {
    if (typeData->ptrLevel > 0) {
        InstallPointer(id->varname, typeData->type, typeData->ptrLevel);
    } else {
        Install(id->varname, typeData->type, 1);
    }
}

void handleGidArray1D(struct tnode *id, struct TypeInfo *typeData, int size) {
    Install1DArray(id->varname, typeData->type, size);
}

void handleGidArray2D(struct tnode *id, struct TypeInfo *typeData, int rows, int cols) {
    Install2DArray(id->varname, typeData->type, rows, cols);
}

void handleGidFunction(struct tnode *id, struct TypeInfo *typeData, struct Paramstruct *params) {
    InstallFunction(id->varname, typeData->type, params);
}

void handleParamInstall(struct Paramstruct *params) {
    InstallParamsToLST(params);
}

void handleLidInstall(char *name, struct TypeInfo *typeData) {
    LInstall(name, typeData->type, typeData->ptrLevel);
}

int verifyFunctionSignature(struct Gsymbol *g, struct TypeInfo *retType, struct Paramstruct *params) {
    if (!g) {
        yyerror("Function not declared");
        exit(1);
    }
    if (g->type != retType->type || !CompareParamLists(g->paramlist, params)) {
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
