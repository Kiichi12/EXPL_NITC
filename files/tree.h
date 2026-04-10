#ifndef TREE_H
#define TREE_H

#include "constants.h"
#include "memory.h"
#include "typetable.h"
#include "classtable.h"

extern char *current_function_name;
extern ClassTableEntry *selfClassEntry;

typedef struct tnode 
{
    union 
    {
        int val;
        char *strVal;
    };

    enum varType type;              /* type of the expression / variable      */
    TypeTableEntry *typeEntry;      /* only for user-defined / class types     */
    struct Fieldstruct *fieldEntry; /* only for NODE_FIELD nodes               */

    char *varname;                  /* name of the variable / function         */

    enum nodeType nodetype;
    struct Gsymbol *Gentry;         /* GST entry for global vars / functions   */

    struct tnode *left, *right;
} tnode;

typedef struct IR 
{
    struct tnode *ast;
    struct Gsymbol *func;
} IR;

/* type-info scratch struct used during parsing */
struct TypeInfo 
{
    enum varType type;
    TypeTableEntry *typeEntry;
    int ptrLevel;
};

/* ------------------------------------------------------------------ */
/* Node constructors                                                    */
/* ------------------------------------------------------------------ */

struct tnode *makeNumNode(int val);
struct tnode *makeStringConstNode(char *lexeme);
struct tnode *makeNullNode();

struct tnode *makeNewVarNode(char *name);
struct tnode *makeVarNode(char *name); 
struct tnode *makeArrayNode(tnode *id, tnode *expr);

struct tnode *makePointerNode(tnode *expr);
struct tnode *makeDerefNode(tnode *expr);

struct tnode *makeArithNode(int nodetype, struct tnode *l, struct tnode *r);

struct tnode *makeBoolNode(int nodetype, struct tnode *l, struct tnode *r);
struct tnode *makeNotNode(struct tnode *expr);

struct tnode *makeAssignNode(struct tnode *id, struct tnode *expr);
struct tnode *makeArrayAssignNode(tnode *arrayNode, tnode *valExpr);

struct tnode *makeReadNode(struct tnode *id);
struct tnode *makeWriteNode(struct tnode *expr);

struct tnode *makeConnectorNode(struct tnode *l, struct tnode *r);

struct tnode *makeWhileNode(struct tnode *condition, struct tnode *body);
struct tnode *makeBreakNode();
struct tnode *makeContinueNode();
struct tnode *makeDoWhileNode(struct tnode *body, struct tnode *condition);
struct tnode *makeRepeatUntilNode(struct tnode *body, struct tnode *condition);

struct tnode *makeIfElseNode(struct tnode *condition, struct tnode *ifBody, struct tnode *elseBody);
struct tnode *makeIfNode(struct tnode *condition, struct tnode *ifBody);

struct tnode *makeFuncallNode(char *funcname, struct tnode *arglist);
struct tnode *makeReturnNode(struct tnode *E, char *funcName);

struct tnode *makeFieldNode(struct tnode *base, char *fieldName);

struct tnode *makeAllocNode(struct tnode *varNode);
struct tnode *makeFreeNode(struct tnode *varNode);
struct tnode *makeInitializeNode();

struct tnode *makeSelfNode();

struct tnode *makeNewNode(char *className);
struct tnode *makeDeleteNode(struct tnode *varNode);
struct tnode *makeMethodCallNode(struct tnode *obj, char *methodName, struct tnode *arglist);

/* ------------------------------------------------------------------ */
/* Helpers                                                              */
/* ------------------------------------------------------------------ */

/*
 * compArgParam – validates actual argument list against formal param list.
 * Updated in Stage 8 to accept subtype arguments for class-typed params.
 */
int compArgParam(struct Paramstruct **param, struct tnode *arg);

const char *nodeTypeToString(int nodetype);
void printAST(struct tnode *t, int level);
void deleteTree(tnode *root);

#endif /* TREE_H */
