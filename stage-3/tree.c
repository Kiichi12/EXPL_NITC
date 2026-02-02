#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "constants.h"

struct tnode* makeNumNode(int val) 
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->val = val;
    t->type = INT;
    t->varname = NULL;
    t->nodetype = NODE_NUM;
    t->left = t->right = NULL;
    return t;
}

struct tnode* makeVarNode(char* name) 
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->val = 0;
    t->type = INT; // all variable are assumed to be integers in the current stage
    t->varname = strdup(name);
    t->nodetype = NODE_ID;
    t->left = t->right = NULL;
    return t;
}


struct tnode* makeArithNode(int nodetype, struct tnode* l, struct tnode* r) 
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->type = INT;  
    t->nodetype = nodetype;
    t->left = l;
    t->right = r;
    return t;
}

struct tnode* makeBoolNode(int nodetype, struct tnode* l, struct tnode* r)
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->type = BOOL;
    t->nodetype = nodetype;
    t->left = l;
    t->right = r;
    return t;
}

struct tnode* makeAssignNode(struct tnode* id, struct tnode* expr) 
{
    struct tnode* t = malloc(sizeof(struct tnode));
    struct tnode* tid = malloc(sizeof(struct tnode));

    t->val = 0;
    t->type = NONE;
    t->varname = strdup(id->varname);
    t->nodetype = NODE_ASSIGN;
    t->left = tid;
    t->right = expr;

    tid->val = expr->val;
    tid->type = INT;
    tid->varname = strdup(id->varname);
    tid->nodetype = NODE_ID;
    tid->left = NULL;
    tid->right = NULL;
    return t;
}


struct tnode* makeReadNode(struct tnode* id) 
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->val = 0;
    t->type = NONE;
    t->varname = strdup(id->varname);
    t->nodetype = NODE_READ;
    t->left = id;
    t->right = NULL;
    return t;
}

struct tnode* makeWriteNode(struct tnode* expr)
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->val = 0;
    t->type = NONE;
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
    t->type = NONE;
    return t;
}

struct tnode* makeBreakNode()
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_BREAK;
    t->type = NONE;
    return t;
}

struct tnode* makeContinueNode()
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_CONTINUE;
    t->type = NONE;
    return t;
}

struct tnode* makeDoWhileNode(struct tnode* body, struct tnode* condition)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_DOWHILE;
    t->left = body;      // body executes first in do-while
    t->right = condition;
    t->type = NONE;
    return t;
}

struct tnode* makeRepeatUntilNode(struct tnode* body, struct tnode* condition) 
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_REPEAT;
    t->left = body;      // body executes first in repeat-until
    t->right = condition; 
    t->type = NONE;
    return t;
}

struct tnode* makeIfElseNode(struct tnode* condition, struct tnode* ifBody, struct tnode* elseBody)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    struct tnode* tifelse = malloc(sizeof(struct tnode));

    tifelse->nodetype = NODE_CONNECTOR;
    tifelse->left = ifBody;
    tifelse->right = elseBody;
    tifelse->type = NONE;

    t->nodetype = NODE_IFELSE;
    t->left = condition;
    t->right = tifelse;
    t->type = NONE;
    
    return t;
}

struct tnode* makeIfNode(struct tnode* condition, struct tnode* ifBody)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    
    t->nodetype = NODE_IF;
    t->left = condition;
    t->right = ifBody;
    t->type = NONE;
    return t;
}

void deleteTree(tnode *root) 
{
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);

    free(root);
}
