#ifndef TREE_H
#define TREE_H

#include "constants.h"
#include "memory.h"

typedef struct tnode {
    union {
        int val;
        char *strVal;
    };              
    enum varType type;          //type of the variable
    char* varname;              //name of the variable
    enum nodeType nodetype;     //node type information
    struct Gsymbol *Gentry;     //pointer to GST entry for global variables and functions
    struct tnode *left, *right; //left and right branches
} tnode;

// to store type-info during parsing
struct TypeInfo {
    int type;
    int ptrLevel;
};

// #define YYSTYPE tnode*

struct tnode* makeNumNode(int val);
struct tnode* makeStringConstNode(char *lexeme);

struct tnode* makeNewVarNode(char* name);
struct tnode* makeVarNode(char* name);
struct tnode* makeArrayNode(tnode* id, tnode* expr);
struct tnode* make2dArrayNode(tnode* id, tnode* indExpr, tnode* valExpr);
struct tnode* makePointerNode(tnode* expr);
struct tnode* makeDerefNode(tnode* expr);


struct tnode* makeArithNode(int nodetype, struct tnode* l, struct tnode* r);

struct tnode* makeBoolNode(int nodetype, struct tnode* l, struct tnode* r);

struct tnode* makeAssignNode(struct tnode* id, struct tnode* expr);
struct tnode *makeArrayAssignNode(tnode* arrayNode, tnode* valExpr);
struct tnode* makeArray2DAssignNode(tnode* arrayNode, tnode* valExpr);

struct tnode* makeReadNode(struct tnode* id);
struct tnode* makeWriteNode(struct tnode* expr);

struct tnode* makeConnectorNode(struct tnode* l, struct tnode* r);

struct tnode* makeWhileNode(struct tnode* condition, struct tnode* body);
struct tnode* makeBreakNode();
struct tnode* makeContinueNode();
struct tnode* makeDoWhileNode(struct tnode* body, struct tnode* condition);
struct tnode* makeRepeatUntilNode(struct tnode* body, struct tnode* condition);

struct tnode* makeIfElseNode(struct tnode* condition, struct tnode* ifBody, struct tnode* elseBody);
struct tnode* makeIfNode(struct tnode* condition, struct tnode* ifBody);


const char* nodeTypeToString(int nodetype);
void printAST(struct tnode* t, int level);

struct tnode* makeFuncallNode(char *funcname, struct tnode *arglist);

void deleteTree(tnode *root);

#endif // TREE_H
