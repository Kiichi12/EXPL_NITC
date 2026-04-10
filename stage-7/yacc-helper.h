#ifndef YACC_HELPER_H
#define YACC_HELPER_H

#include "tree.h"
#include "memory.h"
#include "constants.h"
#include "typetable.h"

// Error reporting function
void yyerror(char *s);


// Function prototypes
void handleGdecComplete(void);
void handleGidScalar(struct tnode *id, struct TypeInfo *typeData);
void handleGidArray1D(struct tnode *id, struct TypeInfo *typeData, int size);
void handleGidArray2D(struct tnode *id, struct TypeInfo *typeData, int rows, int cols);
void handleGidFunction(struct tnode *id, struct TypeInfo *typeData, struct Paramstruct *params);
void handleParamInstall(struct Paramstruct *params);
void handleFdefPrint(char *funcName, struct tnode *body);
void handleFdefNoArgsPrint(char *funcName, struct tnode *body);
void handleMainPrint(struct tnode *body);
void handleLidInstall(char *name, struct TypeInfo *typeData);
int verifyFunctionSignature(struct Gsymbol *g, struct TypeInfo *retType, struct Paramstruct *params);
void printFunctionInfo(char *funcName);

#endif
