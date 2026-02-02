#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "constants.h"

struct tnode* makeNumNode(int val) 
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->val = val;
    t->type = TYPE_INT;
    t->varname = NULL;
    t->nodetype = NODE_NUM;
    t->left = t->right = NULL;
    return t;
}

struct tnode* makeStringConstNode(char *lexeme)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->strVal = strdup(lexeme);
    t->type = TYPE_STRING;
    t->varname = NULL;
    t->nodetype = NODE_STRING;    
    t->left = t->right = NULL;

    return t;
}

struct tnode* makeNewVarNode(char* name)
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->val = 0;
    t->varname = strdup(name);
    t->nodetype = NODE_ID;
    t->left = t->right = NULL;

    return t;
}

struct tnode* makeVarNode(char* name) {
    struct tnode* t = malloc(sizeof(struct tnode));
    t->varname = strdup(name);
    t->nodetype = NODE_ID;
    t->left = t->right = NULL;

    struct Gsymbol *g = Lookup(name);
    if (g) {
        t->Gentry = g;
        t->type = g->type;
    } else {
        t->Gentry = NULL;
        t->type = TYPE_NONE; // Allow parsing to continue, handle error in Task 2
    }
    return t;
}
struct tnode* makeArrayNode(tnode* id, tnode* expr)
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->val = expr->val;
    t->varname = strdup(id->varname);
    t->nodetype = NODE_ARRAY_ELEMENT;
    t->left = id;
    t->right = expr;

    struct Gsymbol* g = Lookup(id->varname);
    if (!g) {
        fprintf(stderr, "Undeclared array '%s'\n", id->varname);
        exit(1);
    }
    t->Gentry = g;
    t->type = g->type;

    if(expr->val >= g->size)
    {
        fprintf(stderr, "Array out of bounds: '%s'\n", id->varname);
        exit(1);
    }

    return t;
}

struct tnode* make2dArrayNode(tnode* id, tnode* indExpr1, tnode* indExpr2)
{
    struct tnode* t = malloc(sizeof(struct tnode));

    // t->val = indExpr->val;
    t->varname = strdup(id->varname);
    t->nodetype = NODE_2D_ARRAY_ELEMENT;
    t->left = id;
    t->right = makeConnectorNode(indExpr1, indExpr2);

    struct Gsymbol* g = Lookup(id->varname);
    if (!g) {
        fprintf(stderr, "Undeclared array '%s'\n", id->varname);
        exit(1);
    }
    t->Gentry = g;
    t->type = g->type;
    if(indExpr1->val >= g->rows)
    {
        fprintf(stderr, "Array out of bounds: '%s'\n", id->varname);
        exit(1);
    }
    if(indExpr2->val >= g->cols)
    {
        fprintf(stderr, "Array out of bounds: '%s'\n", id->varname);
        exit(1);
    }
    return t;
}

struct tnode* makePointerNode(tnode* var)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_POINTER;
    t->left = var;
    t->right = NULL;
    t->type = TYPE_POINTER;
    t->varname = var->varname;
    Gsymbol *g = Lookup(var->varname);
    t->val = g->binding;

    return t;
}

struct tnode* makeDerefNode(tnode* id)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_DEREF;
    t->left = id;
    t->right = NULL;

    t->varname = id->varname;
    t->Gentry = NULL;
    return t;
}


struct tnode* makeArithNode(int nodetype, struct tnode* l, struct tnode* r) 
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->type = TYPE_INT;  
    t->nodetype = nodetype;
    t->left = l;
    t->right = r;
    return t;
}

struct tnode* makeBoolNode(int nodetype, struct tnode* l, struct tnode* r)
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->type = TYPE_BOOL;
    t->nodetype = nodetype;
    t->left = l;
    t->right = r;
    return t;
}

struct tnode* makeAssignNode(struct tnode* id, struct tnode* expr)
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->val = 0;
    t->type = TYPE_NONE;
    t->varname = strdup(id->varname);
    t->nodetype = NODE_ASSIGN;
    t->left = id;
    t->right = expr;
    t->Gentry = id->Gentry;   

    return t;
}

struct tnode *makeArrayAssignNode(tnode* arrayNode, tnode* valExpr)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    struct Gsymbol* g = Lookup(arrayNode->varname);
    if (!g) {
        fprintf(stderr, "Undeclared array: %s\n", arrayNode->varname);
        exit(1);
    }
    if (g->type != valExpr->type) {
        fprintf(stderr, "Type mismatch in array assignment to %s\n", arrayNode->varname);
        exit(1);
    }
    t->varname = strdup(arrayNode->varname);
    t->nodetype = NODE_ARRAY_ASSIGN;
    t->type = TYPE_NONE;
    t->left = arrayNode;
    t->right = valExpr;
    t->Gentry = g;
    return t;
}


struct tnode* makeArray2DAssignNode(tnode* arrayNode, tnode* valExpr)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    struct Gsymbol* g = Lookup(arrayNode->varname);
    if (!g) {
        fprintf(stderr, "Undeclared array: %s\n", arrayNode->varname);
        exit(1);
    }
    if (g->type != valExpr->type) {
        fprintf(stderr, "Type mismatch in array assignment to %s\n", arrayNode->varname);
        exit(1);
    }

    t->varname = strdup(arrayNode->varname);
    t->nodetype = NODE_2D_ARRAY_ASSIGN;
    t->type = TYPE_NONE;
    t->left = arrayNode;
    t->right = valExpr;
    t->Gentry = g;
    return t;
}



struct tnode* makeReadNode(struct tnode* id) 
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->val = 0;
    t->type = TYPE_NONE;
    t->varname = strdup(id->varname);
    t->nodetype = NODE_READ;
    t->left = id;
    t->right = NULL;
    t->Gentry = id->Gentry;
    return t;
}

struct tnode* makeWriteNode(struct tnode* expr) 
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->val = 0;
    t->type = TYPE_NONE;
    t->varname = NULL;
    t->nodetype = NODE_WRITE;
    t->left = expr;
    t->right = NULL;
    return t;
}

struct tnode* makeConnectorNode(struct tnode* l, struct tnode* r) 
{
    struct tnode* t = malloc(sizeof(struct tnode));
    
    t->varname = NULL;
    t->nodetype = NODE_CONNECTOR;
    t->left = l;
    t->right = r;
    return t;
}

struct tnode* makeWhileNode(struct tnode* condition, struct tnode* body)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    
    t->nodetype = NODE_WHILE;
    t->left = condition;
    t->right = body;
    t->type = TYPE_NONE;
    return t;
}

struct tnode* makeBreakNode()
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_BREAK;
    t->type = TYPE_NONE;
    return t;
}

struct tnode* makeContinueNode()
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_CONTINUE;
    t->type = TYPE_NONE;
    return t;
}

struct tnode* makeDoWhileNode(struct tnode* body, struct tnode* condition)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_DOWHILE;
    t->left = body;      // body executes first in do-while
    t->right = condition;
    t->type = TYPE_NONE;
    return t;
}

struct tnode* makeRepeatUntilNode(struct tnode* body, struct tnode* condition)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_REPEAT;
    t->left = body;      // body executes first in repeat-until
    t->right = condition; 
    t->type = TYPE_NONE;
    return t;
}



struct tnode* makeIfElseNode(struct tnode* condition, struct tnode* ifBody, struct tnode* elseBody)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    struct tnode* tifelse = malloc(sizeof(struct tnode));

    tifelse->nodetype = NODE_CONNECTOR;
    tifelse->left = ifBody;
    tifelse->right = elseBody;
    tifelse->type = TYPE_NONE;

    t->nodetype = NODE_IFELSE;
    t->left = condition;
    t->right = tifelse;
    t->type = TYPE_NONE;
    
    return t;
}

struct tnode* makeIfNode(struct tnode* condition, struct tnode* ifBody)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    
    t->nodetype = NODE_IF;
    t->left = condition;
    t->right = ifBody;
    t->type = TYPE_NONE;
    return t;
}

struct tnode* makeFuncallNode(char *funcname, struct tnode *arglist)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_FUNCALL;
    t->varname = strdup(funcname);
    t->left = arglist;
    
    struct Gsymbol *g = Lookup(funcname);
    if (!g) {
        fprintf(stderr, "Undeclared function '%s'\n", funcname);
        exit(1);
    }
    
    if (g->paramlist == NULL && arglist != NULL) {
        fprintf(stderr, "Function '%s' takes no arguments\n", funcname);
        exit(1);
    }
    
    t->Gentry = g;
    t->type = g->type;  // Function return type
    
    return t;


}

const char* nodeTypeToString(int nodetype)
{
    switch (nodetype) {
        case NODE_NUM:        return "NUM";
        case NODE_STRING:     return "STRING";
        case NODE_ID:         return "ID";
        case NODE_ARRAY_ELEMENT: return "ARRAY_ELEMENT";
        case NODE_2D_ARRAY_ELEMENT: return "2D_ARRAY_ELEMENT";
        case NODE_2D_ARRAY_ASSIGN: return "2D_ARRAY_ASSIGN";
        case NODE_POINTER: return "POINTER";
        case NODE_DEREF: return "DEREFERENCE";


        case NODE_PLUS:       return "PLUS";
        case NODE_MINUS:      return "MINUS";
        case NODE_MUL:        return "MUL";
        case NODE_DIV:        return "DIV";

        case NODE_ASSIGN:     return "ASSIGN";
        case NODE_ARRAY_ASSIGN: return "ARRAY_ASSIGN";

        case NODE_READ:       return "READ";
        case NODE_WRITE:      return "WRITE";

        case NODE_CONNECTOR:  return "CONNECTOR";

        case NODE_WHILE:      return "WHILE";
        case NODE_IF:         return "IF";
        case NODE_IFELSE:     return "IFELSE";

        case NODE_BREAK:        return "BREAK";
        case NODE_CONTINUE:     return "CONTINUE";
        case NODE_DOWHILE:      return "DOWHILE";
        case NODE_REPEAT:       return "REPEAT";


        case NODE_LT:         return "LT";
        case NODE_LE:         return "LE";
        case NODE_GT:         return "GT";
        case NODE_GE:         return "GE";
        case NODE_EQ:         return "EQ";
        case NODE_NE:         return "NE";

        default:              return "UNKNOWN";
    }
}


void printAST(struct tnode* t, int level)
{
    if (t == NULL) return;

    for (int i = 0; i < level; i++)
        printf("  ");

    printf("|- %s", nodeTypeToString(t->nodetype));

    if (t->nodetype == NODE_NUM)
        printf(" (%d)", t->val);

    if (t->nodetype == NODE_ID ||
        t->nodetype == NODE_ASSIGN ||
        t->nodetype == NODE_READ)
        printf(" (%s)", t->varname);

    printf("\n");

    printAST(t->left, level + 1);
    printAST(t->right, level + 1);
}

void deleteTree(tnode *root) 
{
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);

    free(root);
}
