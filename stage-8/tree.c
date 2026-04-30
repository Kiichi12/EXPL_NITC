#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "constants.h"

extern char* yytext;
extern int lineNumber;

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

struct tnode* makeNullNode()
{
    tnode *t = malloc(sizeof(tnode));
    t->val = 0;
    t->type = TYPE_NULL;
    t->typeEntry = NULL;
    t->varname = NULL;
    t->nodetype = NODE_NULL;
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

struct tnode* makeVarNode(char* name) 
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->varname = strdup(name);
    t->nodetype = NODE_ID;
    t->left = t->right = NULL;

    // search Local Symbol Table
    struct Lsymbol *l = LLookup(name);
    if (l) 
    {
        t->type = l->type;
        // printf("Type: %d\n", l->type);
        t->Gentry = NULL; // mark as local
        t->typeEntry = l->typeEntry;
        // printf("Local variable: %s\n", name);
        // if(t->typeEntry)
        // {
        //     printf("Type entry: %s\n", t->typeEntry->name);
        // }
        return t;
    }

    // search Global Symbol Table
    struct Gsymbol *g = Lookup(name);
    if (g) 
    {
        t->type = g->type;
        t->Gentry = g;
        t->typeEntry = g->typeEntry;
        return t;
    }

    fprintf(stderr, "Error: Variable %s undeclared\n", name);
    exit(1);
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
    t->typeEntry = g->typeEntry;

    if(expr->val >= g->size)
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
    t->varname = strdup(var->varname);
    
    // preserve the base type from the variable and set pointer level
    t->type = var->type;
    t->typeEntry = var->typeEntry;
    t->Gentry = var->Gentry;
    
    return t;
}

struct tnode* makeDerefNode(tnode* id)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_DEREF;
    t->left = id;
    t->right = NULL;

    t->varname = strdup(id->varname);
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

struct tnode* makeNotNode(struct tnode *expr)
{
    tnode *t = malloc(sizeof(struct tnode));
    t->type = TYPE_BOOL;
    t->nodetype = NODE_NOT;
    t->left = expr;
    t->right = NULL;
    return t;
}

struct tnode* makeAssignNode(struct tnode* lval, struct tnode* expr)
{
    if (expr->type != TYPE_NULL)
    {
        if(lval->type == TYPE_USERDEF || expr->type == TYPE_USERDEF || lval->type == TYPE_CLASS || expr->type == TYPE_CLASS)
        {
            ClassTableEntry *lvalClass = lookupClass(lval->typeEntry->name);
            ClassTableEntry *exprClass = lookupClass(expr->typeEntry->name);
            if(!lvalClass || !exprClass)
            {
                if (lval->typeEntry != expr->typeEntry) 
                {
                    if(!exprClass)
                    {
                        fprintf(stderr, "Tree.c: makeAssignNode: Type mismatch in assignment(udeftype) expr is not class\n expr: %s\n", expr->varname);
                        exit(1);
                    }
                    if(!lvalClass)
                    {
                        
                        fprintf(stderr, "Tree.c: makeAssignNode: Type mismatch in assignment(udeftype) lval is not class\n lval type: %s\n", lval->typeEntry->name);
                        exit(1);
                    }
                    fprintf(stderr, "Tree.c: makeAssignNode: Type mismatch in assignment(udeftype)\n");
                    exit(1);
                }
            }
            else if (!isDescendant(exprClass, lvalClass))
            {
                fprintf(stderr, "Tree.c: makeAssignNode: Type mismatch in assignment(class)\n");
                exit(1);
            }
        }
        else if(lval->type != expr->type && expr->type != TYPE_NULL)
        {
            // printf("lval->type: %d, expr->type: %d\n", lval->type, expr->type);
            // printf("lval->varname: %s, expr->varname: %s\n", lval->varname, expr->varname);
            fprintf(stderr, "Tree.c: makeAssignNode: Type mismatch in assignment\n");
            exit(1);
        }
    }

    struct tnode* t = malloc(sizeof(struct tnode));

    t->val = 0;
    t->type = TYPE_NULL;
    t->varname = strdup(lval->varname);
    t->nodetype = NODE_ASSIGN;
    t->left = lval;
    t->right = expr;
    t->Gentry = lval->Gentry;   

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
    t->type = TYPE_NULL;
    t->left = arrayNode;
    t->right = valExpr;
    t->Gentry = g;
    return t;
}

struct tnode* makeReadNode(struct tnode* id) 
{
    struct tnode* t = malloc(sizeof(struct tnode));

    t->val = 0;
    t->type = TYPE_NULL;
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
    t->type = TYPE_NULL;
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
    t->type = TYPE_NULL;
    return t;
}

struct tnode* makeBreakNode()
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_BREAK;
    t->type = TYPE_NULL;
    return t;
}

struct tnode* makeContinueNode()
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_CONTINUE;
    t->type = TYPE_NULL;
    return t;
}

struct tnode* makeIfElseNode(struct tnode* condition, struct tnode* ifBody, struct tnode* elseBody)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    struct tnode* tifelse = malloc(sizeof(struct tnode));

    tifelse->nodetype = NODE_CONNECTOR;
    tifelse->left = ifBody;
    tifelse->right = elseBody;
    tifelse->type = TYPE_NULL;

    t->nodetype = NODE_IFELSE;
    t->left = condition;
    t->right = tifelse;
    t->type = TYPE_NULL;
    
    return t;
}

struct tnode* makeIfNode(struct tnode* condition, struct tnode* ifBody)
{
    struct tnode* t = malloc(sizeof(struct tnode));
    
    t->nodetype = NODE_IF;
    t->left = condition;
    t->right = ifBody;
    t->type = TYPE_NULL;
    return t;
}

int compArgParam(struct Paramstruct **param, struct tnode *arg)
{
    if (arg == NULL)
        return 1;

    if (arg->nodetype == NODE_CONNECTOR)
    {
        if (!compArgParam(param, arg->left))
            return 0;
        return compArgParam(param, arg->right);
    }

    if (*param == NULL)
    {
        fprintf(stderr, "Tree.c: CompArgParam: Error: Function %s: too many arguments\n", arg->varname);
        return 0; 
    }

    if ((*param)->type == TYPE_USERDEF || (*param)->type == TYPE_CLASS)
    {
        ClassTableEntry *paramClass = lookupClass((*param)->typeEntry->name);
        ClassTableEntry *argClass = lookupClass(arg->typeEntry->name);

        if(paramClass && argClass)
        {
            if(!isDescendant(argClass, paramClass))
            {
                fprintf(stderr, "Tree.c: CompArgParam: Error: Function %s: argument %d type mismatch(class)\n", arg->varname, arg->type);
                return 0;
            }
        }
        else if(arg->typeEntry != (*param)->typeEntry)
        {
            fprintf(stderr, "Tree.c: CompArgParam: Error: Function %s: argument %d type mismatch(udeftype)\n", arg->varname, arg->type);
            return 0;
        }
    }
    else if (arg->type != (*param)->type)
    {
        fprintf(stderr, "Tree.c: CompArgParam: Error: Function %s: argument %d type mismatch\n", arg->varname, arg->type);
        return 0;
    }
    else
    {
        int argPtr = 0;
        if (arg->Gentry)
            argPtr = arg->Gentry->ptrLevel;
        
        // for address-of operations (NODE_POINTER), increment pointer level
        if (arg->nodetype == NODE_POINTER)
            argPtr++;

        if (argPtr != (*param)->ptrLevel)
        {
            fprintf(stderr, "Tree.c: CompArgParam: Error: Function %s: argument %d pointer level mismatch\n", arg->varname, arg->type);
            return 0;
        }
    }

    *param = (*param)->next;

    return 1;
}


struct tnode* makeFuncallNode(char *funcname, struct tnode *arglist) {
    struct Gsymbol *g = Lookup(funcname);
    if (!g) 
    {
        fprintf(stderr, "Tree.c: makeFuncallNode: Error: Function %s undeclared\n", funcname);
        exit(1);
    }

    struct Paramstruct *p = g->paramlist;
    struct tnode *arg = arglist;

    if(p && p->type == TYPE_NULL)
    {
        if(arg != NULL)
        {
            fprintf(stderr, "Tree.c: makeFuncallNode: Error: Function %s takes no arguments but arguments were provided\n", funcname);
            exit(1);
        }
    } 
    else
    {
        if(!compArgParam(&p,arg) || p != NULL)
        {
            fprintf(stderr, "Tree.c: makeFuncallNode: Error: Function %s\n", funcname);
            exit(1);
        }
    }

    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_FUNCALL;
    t->varname = strdup(funcname);
    t->left = arglist;
    t->right = NULL;
    t->Gentry = g;
    t->type = g->type;
    t->typeEntry = g->typeEntry;
    return t;
}

struct tnode* makeReturnNode(struct tnode* E, char * funcName) 
{
    struct tnode* t = malloc(sizeof(struct tnode));
    t->nodetype = NODE_RET;
    t->left = E;
    t->right = NULL;


    t->varname = strdup(funcName);
    if(E)
    {
        t->type = E->type; 
        t->typeEntry = E->typeEntry;
    }
    else
    {
        t->type = TYPE_NULL; // no return value
        t->typeEntry = NULL;
    }
    
    return t;
}

struct tnode *makeAllocNode(struct tnode *varNode)
{
    tnode *t = malloc(sizeof(tnode));
    t->nodetype = NODE_ALLOC;
    t->left = varNode;
    t->type = TYPE_USERDEF;
    t->typeEntry = varNode->typeEntry;
    return t;
}

struct tnode *makeFreeNode(struct tnode *varNode)
{
    tnode *t = malloc(sizeof(tnode));
    t->nodetype = NODE_FREE;
    t->left = varNode;
    t->type = TYPE_NULL;
    t->typeEntry = NULL;
    return t;
}

struct tnode *makeInitializeNode()
{
    tnode *t = malloc(sizeof(tnode));
    t->nodetype = NODE_INITIALIZE;
    t->type = TYPE_NULL;
    t->typeEntry = NULL;
    return t;
}

struct tnode *makeFieldNode(tnode *base, char *fieldName)
{
    TypeTableEntry *baseType = base->typeEntry;
    
    if(baseType == NULL) {
        fprintf(stderr, "Tree.c: makeFieldNode: Error: Base is not a user-defined type\n");
        exit(1);
    }

    ClassTableEntry *cls = lookupClass(baseType->name);
    if(cls)
    {
        if(!selfClassEntry)
        {
            fprintf(stderr, "Tree.c: makeFieldNode: Error: Field %s is private and cannot be accessed outside the class\n", fieldName);
            exit(1);
        }

        if (!isDescendant(selfClassEntry, cls) && !isDescendant(cls, selfClassEntry))
        {
            
            fprintf(stderr, "Tree.c: makeFieldNode: Error: Field %s is private and cannot be accessed from a method of class %s\n", fieldName, selfClassEntry->name);
            exit(1);
        }
    }

    Fieldstruct *field = lookupField(baseType, fieldName);
    if(field == NULL) {
        fprintf(stderr, "Tree.c: makeFieldNode: Error: Field %s not found in type %s\n", fieldName, baseType->name);
        exit(1);
    }

    tnode *t = malloc(sizeof(tnode));
    t->nodetype = NODE_FIELD;
    t->type = field->typeEntry->typeId;
    t->left = base;
    t->right = NULL;
    t->varname = strdup(fieldName);
    t->typeEntry = field->typeEntry;
    t->fieldEntry = field;
    return t;
    
}

struct tnode *makeSelfNode()
{
    if(!selfClassEntry)
    {
        fprintf(stderr, "Tree.c: makeSelfNode: Error: 'self' used outside a class method: %s\nlineNumber:%d\n", yytext, lineNumber);
        exit(1);
    }
    
    tnode *t = malloc(sizeof(tnode));
    t->nodetype = NODE_SELF;
    t->type = TYPE_CLASS;
    t->typeEntry = selfClassEntry->type;
    t->varname = strdup("self");
    t->left = NULL;
    t->right = NULL;
    return t;
}

struct tnode *makeNewNode(char *className)
{
    ClassTableEntry *cls = lookupClass(className);
    if(!cls)
    {
        fprintf(stderr, "Tree.c: makeNewNode: Error: Class %s not found\n", className);
        exit(1);
    }
    
    tnode *t = malloc(sizeof(tnode));
    t->nodetype   = NODE_NEW;
    t->type       = TYPE_CLASS;
    t->typeEntry  = cls->type;
    t->varname    = strdup(className);
    t->left = t->right = NULL;
    t->fieldEntry = NULL;
    t->Gentry     = NULL;
    return t;
}

struct tnode *makeMethodCallNode(struct tnode *obj, char *methodName, struct tnode *arglist)
{
    if(!obj->typeEntry)
    {
        fprintf(stderr, "Tree.c: makeMethodCallNode: Error: Receiver has no type information\n");
        exit(1);
    }
    
    ClassTableEntry *cls = lookupClass(obj->typeEntry->name);
    if(!cls)
    {
        fprintf(stderr, "Tree.c: makeMethodCallNode: Error: Receiver type %s is not a class\n", obj->typeEntry->name);
        exit(1);
    }
    
    MethodEntry *method = lookupMethod(cls, methodName);
    if(!method)
    {
        fprintf(stderr, "Tree.c: makeMethodCallNode: Error: Method %s not found in class %s\n", methodName, cls->name);
        exit(1);
    }
    
    // struct Gsymbol *g = Lookup(methodName);
    // if(!g)
    // {
    //     fprintf(stderr, "Tree.c: makeMethodCallNode: Error: Method %s not found in GST\n", methodName);
    //     exit(1);
    // }

    Paramstruct *p = method->params;
    struct tnode *arg = arglist;
    
    if(p && p->type == TYPE_NULL)
    {
        if(arg != NULL)
        {
            fprintf(stderr, "Tree.c: makeMethodCallNode: Error: Method %s takes no arguments but arguments were provided\n", methodName);
            exit(1);
        }
    }
    else
    {
        if(!compArgParam(&p, arg) || p != NULL)
        {
            fprintf(stderr, "Tree.c: makeMethodCallNode: Error: Argument mismatch in call to %s\n", methodName);
            exit(1);
        }
    }
    
    tnode *t = malloc(sizeof(tnode));
    t->nodetype = NODE_METHOD_CALL;
    t->type = method->retType;
    t->typeEntry = method->retTypeEntry;
    t->varname = strdup(methodName);
    t->left = obj;
    t->right = arglist;
    t->Gentry = NULL;
    t->fieldEntry = NULL;
    return t;
}

struct tnode *makeDeleteNode(struct tnode *varNode)
{
    tnode *t = malloc(sizeof(tnode));
    t->nodetype = NODE_DELETE;
    t->left = varNode;
    t->type = TYPE_NULL;
    t->typeEntry = NULL;
    return t;

}

const char* nodeTypeToString(int nodetype)
{
    switch (nodetype)
    {
        case NODE_NUM:          return "NUM";
        case NODE_STRING:       return "STRING";
        case NODE_NULL:         return "NULL";

        case NODE_ID:           return "ID";
        case NODE_ARRAY_ELEMENT: return "ARRAY_ELEMENT";
        case NODE_FIELD:        return "FIELD";

        case NODE_POINTER:      return "POINTER";
        case NODE_DEREF:        return "DEREFERENCE";

        case NODE_FUNCALL:      return "FUNCALL";
        case NODE_METHOD_CALL:  return "METHOD_CALL";
        case NODE_RET:          return "RETURN";

        case NODE_PLUS:         return "PLUS";
        case NODE_MINUS:        return "MINUS";
        case NODE_MUL:          return "MUL";
        case NODE_DIV:          return "DIV";

        case NODE_ASSIGN:       return "ASSIGN";
        case NODE_ARRAY_ASSIGN: return "ARRAY_ASSIGN";

        case NODE_READ:         return "READ";
        case NODE_WRITE:        return "WRITE";

        case NODE_CONNECTOR:    return "CONNECTOR";

        case NODE_WHILE:        return "WHILE";
        case NODE_DOWHILE:      return "DOWHILE";
        case NODE_REPEAT:       return "REPEAT_UNTIL";
        case NODE_IF:           return "IF";
        case NODE_IFELSE:       return "IFELSE";
        case NODE_BREAK:        return "BREAK";
        case NODE_CONTINUE:     return "CONTINUE";

        case NODE_LT:           return "LT";
        case NODE_LE:           return "LE";
        case NODE_GT:           return "GT";
        case NODE_GE:           return "GE";
        case NODE_EQ:           return "EQ";
        case NODE_NE:           return "NE";
        case NODE_AND:          return "AND";
        case NODE_OR:           return "OR";
        case NODE_NOT:          return "NOT";

        case NODE_ALLOC:        return "ALLOC";
        case NODE_FREE:         return "FREE";
        case NODE_INITIALIZE:   return "INITIALIZE";

        case NODE_NEW:          return "NEW";
        case NODE_DELETE:       return "DELETE";
        case NODE_SELF:         return "SELF";

        default:                return "UNKNOWN";
    }
}


void printAST(struct tnode* t, int level)
{
    if (t == NULL) return;

    for (int i = 0; i < level; i++)
        printf("  ");

    printf("|- %s", nodeTypeToString(t->nodetype));

    if(t->nodetype == NODE_SELF) {
        printf(" (%s)",selfClassEntry->name );
    }

    if (t->nodetype == NODE_NUM)
        printf(" (%d)", t->val);
    
    if (t->nodetype == NODE_STRING)
        printf(" (%s)", t->strVal);

    if (t->nodetype == NODE_ID ||
        t->nodetype == NODE_ASSIGN ||
        t->nodetype == NODE_READ ||
        t->nodetype == NODE_FUNCALL ||
        t->nodetype == NODE_FIELD)
    {
        printf(" (%s)", t->varname);
    }
    
    if (t->nodetype == NODE_FIELD && t->fieldEntry)
    {
        printf(" .%s@%d type:%d", t->fieldEntry->name, t->fieldEntry->fieldOffset, t->fieldEntry->typeEntry->typeId);
    }

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
