#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "constants.h"

extern char *yytext;

/* ------------------------------------------------------------------ */
/* Literal / leaf nodes                                                 */
/* ------------------------------------------------------------------ */

struct tnode *makeNumNode(int val)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->val       = val;
    t->type      = TYPE_INT;
    t->typeEntry = NULL;
    t->varname   = NULL;
    t->nodetype  = NODE_NUM;
    t->Gentry    = NULL;
    t->fieldEntry = NULL;
    t->left = t->right = NULL;
    return t;
}

struct tnode *makeStringConstNode(char *lexeme)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->strVal    = strdup(lexeme);
    t->type      = TYPE_STRING;
    t->typeEntry = NULL;
    t->varname   = NULL;
    t->nodetype  = NODE_STRING;
    t->Gentry    = NULL;
    t->fieldEntry = NULL;
    t->left = t->right = NULL;
    return t;
}

struct tnode *makeNullNode()
{
    tnode *t = malloc(sizeof(tnode));
    t->val       = 0;
    t->type      = TYPE_NULL;
    t->typeEntry = NULL;
    t->varname   = NULL;
    t->nodetype  = NODE_NULL;
    t->Gentry    = NULL;
    t->fieldEntry = NULL;
    t->left = t->right = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* Variable nodes                                                       */
/* ------------------------------------------------------------------ */

struct tnode *makeNewVarNode(char *name)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->val       = 0;
    t->varname   = strdup(name);
    t->nodetype  = NODE_ID;
    t->typeEntry = NULL;
    t->Gentry    = NULL;
    t->fieldEntry = NULL;
    t->left = t->right = NULL;
    return t;
}

struct tnode *makeVarNode(char *name)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->varname    = strdup(name);
    t->nodetype   = NODE_ID;
    t->fieldEntry = NULL;
    t->left = t->right = NULL;

    /* Search Local Symbol Table first */
    struct Lsymbol *l = LLookup(name);
    if (l)
    {
        t->type      = l->type;
        t->Gentry    = NULL;
        t->typeEntry = l->typeEntry;
        return t;
    }

    /* Fall back to Global Symbol Table */
    struct Gsymbol *g = Lookup(name);
    if (g)
    {
        t->type      = g->type;
        t->Gentry    = g;
        t->typeEntry = g->typeEntry;
        return t;
    }

    fprintf(stderr, "Error: Variable '%s' undeclared\n", name);
    exit(1);
}

struct tnode *makeArrayNode(tnode *id, tnode *expr)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->val      = expr->val;
    t->varname  = strdup(id->varname);
    t->nodetype = NODE_ARRAY_ELEMENT;
    t->left     = id;
    t->right    = expr;

    struct Gsymbol *g = Lookup(id->varname);
    if (!g)
    {
        fprintf(stderr, "Undeclared array '%s'\n", id->varname);
        exit(1);
    }
    t->Gentry    = g;
    t->type      = g->type;
    t->typeEntry = g->typeEntry;
    t->fieldEntry = NULL;

    if (expr->val >= g->size)
    {
        fprintf(stderr, "Array out of bounds: '%s'\n", id->varname);
        exit(1);
    }
    return t;
}

/* ------------------------------------------------------------------ */
/* Pointer nodes                                                        */
/* ------------------------------------------------------------------ */

struct tnode *makePointerNode(tnode *var)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype   = NODE_POINTER;
    t->left       = var;
    t->right      = NULL;
    t->varname    = strdup(var->varname);
    t->type       = var->type;
    t->typeEntry  = var->typeEntry;
    t->Gentry     = var->Gentry;
    t->fieldEntry = NULL;
    return t;
}

struct tnode *makeDerefNode(tnode *id)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype   = NODE_DEREF;
    t->left       = id;
    t->right      = NULL;
    t->varname    = strdup(id->varname);
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* Arithmetic / Boolean nodes                                           */
/* ------------------------------------------------------------------ */

struct tnode *makeArithNode(int nodetype, struct tnode *l, struct tnode *r)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->type       = TYPE_INT;
    t->nodetype   = nodetype;
    t->left       = l;
    t->right      = r;
    t->typeEntry  = NULL;
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    return t;
}

struct tnode *makeBoolNode(int nodetype, struct tnode *l, struct tnode *r)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->type       = TYPE_BOOL;
    t->nodetype   = nodetype;
    t->left       = l;
    t->right      = r;
    t->typeEntry  = NULL;
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    return t;
}

struct tnode *makeNotNode(struct tnode *expr)
{
    tnode *t = malloc(sizeof(struct tnode));
    t->type       = TYPE_BOOL;
    t->nodetype   = NODE_NOT;
    t->left       = expr;
    t->right      = NULL;
    t->typeEntry  = NULL;
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* Assignment                                                           */
/* Stage 8: lval (class A) = expr (class B) is valid when B is a      */
/* descendant of A.                                                     */
/* ------------------------------------------------------------------ */

struct tnode *makeAssignNode(struct tnode *lval, struct tnode *expr)
{
    /* Allow null on the right-hand side */
    if (expr->type != TYPE_NULL)
    {
        int lIsClass = (lval->type == TYPE_USERDEF || lval->type == TYPE_CLASS);
        int rIsClass = (expr->type == TYPE_USERDEF || expr->type == TYPE_CLASS);

        if (lIsClass || rIsClass)
        {
            if (!lIsClass || !rIsClass)
            {
                fprintf(stderr,
                    "tree.c: makeAssignNode: Type mismatch – "
                    "class vs non-class assignment\n");
                exit(1);
            }

            /*
             * Stage 8 rule:
             *   lval : A,  expr : B
             *   Valid iff B == A  OR  B is a descendant of A.
             */
            ClassTableEntry *lCls = lookupClass(lval->typeEntry->name);
            ClassTableEntry *rCls = lookupClass(expr->typeEntry->name);

            if (!lCls || !rCls)
            {
                /* At least one side is a plain user-defined type (struct),
                   not a class – fall back to exact-match check. */
                if (lval->typeEntry != expr->typeEntry)
                {
                    fprintf(stderr,
                        "tree.c: makeAssignNode: Type mismatch in assignment "
                        "(user-defined type)\n");
                    exit(1);
                }
            }
            else if (!isDescendant(rCls, lCls))
            {
                fprintf(stderr,
                    "tree.c: makeAssignNode: Type mismatch – class '%s' is not "
                    "a subclass of '%s'\n",
                    rCls->name, lCls->name);
                exit(1);
            }
            /* else: valid subtype assignment – proceed */
        }
        else if (lval->type != expr->type)
        {
            fprintf(stderr, "tree.c: makeAssignNode: Type mismatch in assignment\n");
            exit(1);
        }
    }

    struct tnode *t = malloc(sizeof(struct tnode));
    t->val       = 0;
    t->type      = TYPE_NULL;
    t->typeEntry = NULL;
    t->varname   = strdup(lval->varname);
    t->nodetype  = NODE_ASSIGN;
    t->left      = lval;
    t->right     = expr;
    t->Gentry    = lval->Gentry;
    t->fieldEntry = NULL;
    return t;
}

struct tnode *makeArrayAssignNode(tnode *arrayNode, tnode *valExpr)
{
    struct tnode *t  = malloc(sizeof(struct tnode));
    struct Gsymbol *g = Lookup(arrayNode->varname);
    if (!g)
    {
        fprintf(stderr, "Undeclared array: %s\n", arrayNode->varname);
        exit(1);
    }
    if (g->type != valExpr->type)
    {
        fprintf(stderr, "Type mismatch in array assignment to %s\n", arrayNode->varname);
        exit(1);
    }
    t->varname    = strdup(arrayNode->varname);
    t->nodetype   = NODE_ARRAY_ASSIGN;
    t->type       = TYPE_NULL;
    t->left       = arrayNode;
    t->right      = valExpr;
    t->Gentry     = g;
    t->typeEntry  = NULL;
    t->fieldEntry = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* I/O nodes                                                            */
/* ------------------------------------------------------------------ */

struct tnode *makeReadNode(struct tnode *id)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->val       = 0;
    t->type      = TYPE_NULL;
    t->typeEntry = NULL;
    t->varname   = strdup(id->varname);
    t->nodetype  = NODE_READ;
    t->left      = id;
    t->right     = NULL;
    t->Gentry    = id->Gentry;
    t->fieldEntry = NULL;
    return t;
}

struct tnode *makeWriteNode(struct tnode *expr)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->val       = 0;
    t->type      = TYPE_NULL;
    t->typeEntry = NULL;
    t->varname   = NULL;
    t->nodetype  = NODE_WRITE;
    t->left      = expr;
    t->right     = NULL;
    t->Gentry    = NULL;
    t->fieldEntry = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* Control-flow nodes                                                   */
/* ------------------------------------------------------------------ */

struct tnode *makeConnectorNode(struct tnode *l, struct tnode *r)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->varname    = NULL;
    t->nodetype   = NODE_CONNECTOR;
    t->left       = l;
    t->right      = r;
    t->typeEntry  = NULL;
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    return t;
}

struct tnode *makeWhileNode(struct tnode *condition, struct tnode *body)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype   = NODE_WHILE;
    t->left       = condition;
    t->right      = body;
    t->type       = TYPE_NULL;
    t->typeEntry  = NULL;
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    return t;
}

struct tnode *makeBreakNode()
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype   = NODE_BREAK;
    t->type       = TYPE_NULL;
    t->typeEntry  = NULL;
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    t->left = t->right = NULL;
    return t;
}

struct tnode *makeContinueNode()
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype   = NODE_CONTINUE;
    t->type       = TYPE_NULL;
    t->typeEntry  = NULL;
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    t->left = t->right = NULL;
    return t;
}

struct tnode *makeDoWhileNode(struct tnode *body, struct tnode *condition)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype   = NODE_DOWHILE;
    t->left       = condition;
    t->right      = body;
    t->type       = TYPE_NULL;
    t->typeEntry  = NULL;
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    return t;
}

struct tnode *makeRepeatUntilNode(struct tnode *body, struct tnode *condition)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype   = NODE_REPEAT;
    t->left       = condition;
    t->right      = body;
    t->type       = TYPE_NULL;
    t->typeEntry  = NULL;
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    return t;
}

struct tnode *makeIfElseNode(struct tnode *condition,
                              struct tnode *ifBody,
                              struct tnode *elseBody)
{
    struct tnode *tifelse = malloc(sizeof(struct tnode));
    tifelse->nodetype   = NODE_CONNECTOR;
    tifelse->left       = ifBody;
    tifelse->right      = elseBody;
    tifelse->type       = TYPE_NULL;
    tifelse->typeEntry  = NULL;
    tifelse->Gentry     = NULL;
    tifelse->fieldEntry = NULL;
    tifelse->varname    = NULL;

    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype   = NODE_IFELSE;
    t->left       = condition;
    t->right      = tifelse;
    t->type       = TYPE_NULL;
    t->typeEntry  = NULL;
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    return t;
}

struct tnode *makeIfNode(struct tnode *condition, struct tnode *ifBody)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype   = NODE_IF;
    t->left       = condition;
    t->right      = ifBody;
    t->type       = TYPE_NULL;
    t->typeEntry  = NULL;
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* Argument / parameter comparison                                      */
/* Stage 8: class-typed arguments accept subtype values.               */
/* ------------------------------------------------------------------ */

int compArgParam(struct Paramstruct **param, struct tnode *arg)
{
    if (arg == NULL) return 1;

    if (arg->nodetype == NODE_CONNECTOR)
    {
        if (!compArgParam(param, arg->left))  return 0;
        return compArgParam(param, arg->right);
    }

    if (*param == NULL)
    {
        fprintf(stderr,
            "tree.c: compArgParam: Too many arguments (extra arg: '%s')\n",
            arg->varname ? arg->varname : "?");
        return 0;
    }

    int paramIsClass = ((*param)->type == TYPE_CLASS ||
                        (*param)->type == TYPE_USERDEF);
    int argIsClass   = (arg->type == TYPE_CLASS ||
                        arg->type == TYPE_USERDEF);

    if (paramIsClass || argIsClass)
    {
        if (!paramIsClass || !argIsClass)
        {
            fprintf(stderr,
                "tree.c: compArgParam: Class vs non-class type mismatch\n");
            return 0;
        }

        /*
         * Stage 8 rule: the actual argument's class must be the same as or a
         * descendant of the formal parameter's class.
         */
        ClassTableEntry *paramCls = lookupClass((*param)->typeEntry->name);
        ClassTableEntry *argCls   = lookupClass(arg->typeEntry->name);

        if (paramCls && argCls)
        {
            if (!isDescendant(argCls, paramCls))
            {
                fprintf(stderr,
                    "tree.c: compArgParam: Class '%s' is not a subclass of "
                    "parameter type '%s'\n",
                    argCls->name, paramCls->name);
                return 0;
            }
        }
        else
        {
            /* plain user-defined type – exact match required */
            if ((*param)->typeEntry != arg->typeEntry)
            {
                fprintf(stderr,
                    "tree.c: compArgParam: User-defined type mismatch\n");
                return 0;
            }
        }
    }
    else if (arg->type != (*param)->type)
    {
        fprintf(stderr,
            "tree.c: compArgParam: Type mismatch (formal=%d, actual=%d)\n",
            (*param)->type, arg->type);
        return 0;
    }
    else
    {
        /* Pointer-level check for non-class types */
        int argPtr = 0;
        if (arg->Gentry)       argPtr = arg->Gentry->ptrLevel;
        if (arg->nodetype == NODE_POINTER) argPtr++;

        if (argPtr != (*param)->ptrLevel)
        {
            fprintf(stderr,
                "tree.c: compArgParam: Pointer-level mismatch\n");
            return 0;
        }
    }

    *param = (*param)->next;
    return 1;
}

/* ------------------------------------------------------------------ */
/* Function call                                                        */
/* ------------------------------------------------------------------ */

struct tnode *makeFuncallNode(char *funcname, struct tnode *arglist)
{
    struct Gsymbol *g = Lookup(funcname);
    if (!g)
    {
        fprintf(stderr, "tree.c: makeFuncallNode: Function '%s' undeclared\n", funcname);
        exit(1);
    }

    struct Paramstruct *p = g->paramlist;
    struct tnode       *arg = arglist;

    if (p && p->type == TYPE_NULL)
    {
        if (arg != NULL)
        {
            fprintf(stderr,
                "tree.c: makeFuncallNode: Function '%s' takes no arguments\n",
                funcname);
            exit(1);
        }
    }
    else
    {
        if (!compArgParam(&p, arg) || p != NULL)
        {
            fprintf(stderr,
                "tree.c: makeFuncallNode: Argument mismatch for '%s'\n",
                funcname);
            exit(1);
        }
    }

    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype   = NODE_FUNCALL;
    t->varname    = strdup(funcname);
    t->left       = arglist;
    t->right      = NULL;
    t->Gentry     = g;
    t->type       = g->type;
    t->typeEntry  = g->typeEntry;
    t->fieldEntry = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* Return node                                                          */
/* ------------------------------------------------------------------ */

struct tnode *makeReturnNode(struct tnode *E, char *funcName)
{
    struct tnode *t = malloc(sizeof(struct tnode));
    t->nodetype   = NODE_RET;
    t->left       = E;
    t->right      = NULL;
    t->varname    = strdup(funcName);
    t->fieldEntry = NULL;
    t->Gentry     = NULL;

    if (E)
    {
        t->type      = E->type;
        t->typeEntry = E->typeEntry;
    }
    else
    {
        t->type      = TYPE_NULL;
        t->typeEntry = NULL;
    }
    return t;
}

/* ------------------------------------------------------------------ */
/* Heap management nodes                                                */
/* ------------------------------------------------------------------ */

struct tnode *makeAllocNode(struct tnode *varNode)
{
    tnode *t = malloc(sizeof(tnode));
    t->nodetype   = NODE_ALLOC;
    t->left       = varNode;
    t->right      = NULL;
    t->type       = TYPE_USERDEF;
    t->typeEntry  = varNode->typeEntry;
    t->fieldEntry = NULL;
    t->Gentry     = NULL;
    return t;
}

struct tnode *makeFreeNode(struct tnode *varNode)
{
    tnode *t = malloc(sizeof(tnode));
    t->nodetype   = NODE_FREE;
    t->left       = varNode;
    t->right      = NULL;
    t->type       = TYPE_NULL;
    t->typeEntry  = NULL;
    t->fieldEntry = NULL;
    t->Gentry     = NULL;
    return t;
}

struct tnode *makeInitializeNode()
{
    tnode *t = malloc(sizeof(tnode));
    t->nodetype   = NODE_INITIALIZE;
    t->type       = TYPE_NULL;
    t->typeEntry  = NULL;
    t->fieldEntry = NULL;
    t->Gentry     = NULL;
    t->left = t->right = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* Field access                                                         */
/* ------------------------------------------------------------------ */

struct tnode *makeFieldNode(tnode *base, char *fieldName)
{
    TypeTableEntry *baseType = base->typeEntry;

    if (!baseType)
    {
        fprintf(stderr,
            "tree.c: makeFieldNode: Base has no type information\n");
        exit(1);
    }

    ClassTableEntry *cls = lookupClass(baseType->name);
    if (cls)
    {
        if (!selfClassEntry)
        {
            fprintf(stderr,
                "tree.c: makeFieldNode: Field '%s' is private and cannot be "
                "accessed outside a class method\n", fieldName);
            exit(1);
        }
        /*
         * Stage 8: allow access if selfClassEntry is cls itself or a
         * descendant of cls (a subclass method may access inherited fields).
         */
        if (!isDescendant(selfClassEntry, cls) &&
            !isDescendant(cls, selfClassEntry))
        {
            fprintf(stderr,
                "tree.c: makeFieldNode: Field '%s' belongs to class '%s' "
                "but current method is from class '%s'\n",
                fieldName, cls->name, selfClassEntry->name);
            exit(1);
        }
    }

    Fieldstruct *field = lookupField(baseType, fieldName);
    if (!field)
    {
        fprintf(stderr,
            "tree.c: makeFieldNode: Field '%s' not found in type '%s'\n",
            fieldName, baseType->name);
        exit(1);
    }

    tnode *t = malloc(sizeof(tnode));
    t->nodetype   = NODE_FIELD;
    t->type       = field->typeEntry->typeId;
    t->left       = base;
    t->right      = NULL;
    t->varname    = strdup(fieldName);
    t->typeEntry  = field->typeEntry;
    t->fieldEntry = field;
    t->Gentry     = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* 'self' node                                                          */
/* ------------------------------------------------------------------ */

struct tnode *makeSelfNode()
{
    if (!selfClassEntry)
    {
        fprintf(stderr,
            "tree.c: makeSelfNode: 'self' used outside a class method\n");
        exit(1);
    }
    tnode *t = malloc(sizeof(tnode));
    t->nodetype   = NODE_SELF;
    t->type       = TYPE_CLASS;
    t->typeEntry  = selfClassEntry->type;
    t->varname    = strdup("self");
    t->left = t->right = NULL;
    t->Gentry     = NULL;
    t->fieldEntry = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* new(ClassName)                                                        */
/* Stage 8: a = new(B) is valid when B is a descendant of the class    */
/* of a.  The node carries B's class/type information so the code       */
/* generator can set the correct virtual function table pointer.        */
/* ------------------------------------------------------------------ */

struct tnode *makeNewNode(char *className)
{
    ClassTableEntry *cls = lookupClass(className);
    if (!cls)
    {
        fprintf(stderr,
            "tree.c: makeNewNode: Class '%s' not found\n", className);
        exit(1);
    }

    tnode *t = malloc(sizeof(tnode));
    t->nodetype   = NODE_NEW;
    t->type       = TYPE_CLASS;
    t->typeEntry  = cls->type;   /* type of the instantiated class */
    t->varname    = strdup(className);
    t->left = t->right = NULL;
    t->fieldEntry = NULL;
    t->Gentry     = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* delete node (Stage 8 alias for NODE_DELETE)                          */
/* ------------------------------------------------------------------ */

struct tnode *makeDeleteNode(struct tnode *varNode)
{
    tnode *t = malloc(sizeof(tnode));
    t->nodetype   = NODE_DELETE;
    t->left       = varNode;
    t->right      = NULL;
    t->type       = TYPE_NULL;
    t->typeEntry  = NULL;
    t->fieldEntry = NULL;
    t->Gentry     = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* Method call                                                          */
/* Stage 8 semantic rule:                                               */
/*   x.fun() is valid ONLY IF fun is declared in the *static* (compile-*/
/*   time) class of x – i.e., the class that x was declared as.        */
/*   If x is declared as class A, only methods visible in A's class    */
/*   table entry are callable, even if x currently holds a child-class  */
/*   object.                                                            */
/* ------------------------------------------------------------------ */

struct tnode *makeMethodCallNode(struct tnode *obj,
                                  char *methodName,
                                  struct tnode *arglist)
{
    if (!obj->typeEntry)
    {
        fprintf(stderr,
            "tree.c: makeMethodCallNode: Receiver has no type information\n");
        exit(1);
    }

    /* Use the *declared* (static) type of the object variable */
    ClassTableEntry *declaredCls = lookupClass(obj->typeEntry->name);
    if (!declaredCls)
    {
        fprintf(stderr,
            "tree.c: makeMethodCallNode: '%s' is not a class type\n",
            obj->typeEntry->name);
        exit(1);
    }

    /*
     * Stage 8 rule: the method must be visible in the declared class.
     * (Even if obj at runtime holds a descendant, only the parent's
     *  interface is accessible through a parent-typed variable.)
     */
    MethodEntry *method = lookupMethod(declaredCls, methodName);
    if (!method)
    {
        fprintf(stderr,
            "tree.c: makeMethodCallNode: Method '%s' not found in class '%s'\n",
            methodName, declaredCls->name);
        exit(1);
    }

    /*
     * Find the GST entry.  For inherited/overriding methods we may have
     * installed the original under 'methodName' (root class) or under
     * 'ClassName_methodName' (overriding class).  We look up 'methodName'
     * as the representative entry – the actual label is resolved at runtime
     * via the virtual function table.
     */
    struct Gsymbol *g = Lookup(methodName);
    if (!g)
    {
        /* Try mangled name for the declared class */
        char mangledName[512];
        snprintf(mangledName, sizeof(mangledName), "%s_%s",
                 declaredCls->name, methodName);
        g = Lookup(mangledName);
    }
    if (!g)
    {
        fprintf(stderr,
            "tree.c: makeMethodCallNode: No GST entry for method '%s'\n",
            methodName);
        exit(1);
    }

    /* Validate actual arguments against formal parameters */
    Paramstruct  *p   = method->params;
    struct tnode *arg = arglist;

    if (p && p->type == TYPE_NULL)
    {
        if (arg != NULL)
        {
            fprintf(stderr,
                "tree.c: makeMethodCallNode: Method '%s' takes no arguments\n",
                methodName);
            exit(1);
        }
    }
    else
    {
        if (!compArgParam(&p, arg) || p != NULL)
        {
            fprintf(stderr,
                "tree.c: makeMethodCallNode: Argument mismatch for '%s'\n",
                methodName);
            exit(1);
        }
    }

    tnode *t = malloc(sizeof(tnode));
    t->nodetype   = NODE_METHOD_CALL;
    t->type       = method->retType;
    t->typeEntry  = method->retTypeEntry;
    t->varname    = strdup(methodName);
    t->left       = obj;
    t->right      = arglist;
    t->Gentry     = g;
    t->fieldEntry = NULL;
    return t;
}

/* ------------------------------------------------------------------ */
/* Debug / print helpers                                                */
/* ------------------------------------------------------------------ */

const char *nodeTypeToString(int nodetype)
{
    switch (nodetype)
    {
        case NODE_NUM:           return "NUM";
        case NODE_STRING:        return "STRING";
        case NODE_NULL:          return "NULL";
        case NODE_ID:            return "ID";
        case NODE_ARRAY_ELEMENT: return "ARRAY_ELEMENT";
        case NODE_FIELD:         return "FIELD";
        case NODE_POINTER:       return "POINTER";
        case NODE_DEREF:         return "DEREFERENCE";
        case NODE_FUNCALL:       return "FUNCALL";
        case NODE_METHOD_CALL:   return "METHOD_CALL";
        case NODE_RET:           return "RETURN";
        case NODE_PLUS:          return "PLUS";
        case NODE_MINUS:         return "MINUS";
        case NODE_MUL:           return "MUL";
        case NODE_DIV:           return "DIV";
        case NODE_ASSIGN:        return "ASSIGN";
        case NODE_ARRAY_ASSIGN:  return "ARRAY_ASSIGN";
        case NODE_READ:          return "READ";
        case NODE_WRITE:         return "WRITE";
        case NODE_CONNECTOR:     return "CONNECTOR";
        case NODE_WHILE:         return "WHILE";
        case NODE_DOWHILE:       return "DOWHILE";
        case NODE_REPEAT:        return "REPEAT_UNTIL";
        case NODE_IF:            return "IF";
        case NODE_IFELSE:        return "IFELSE";
        case NODE_BREAK:         return "BREAK";
        case NODE_CONTINUE:      return "CONTINUE";
        case NODE_LT:            return "LT";
        case NODE_LE:            return "LE";
        case NODE_GT:            return "GT";
        case NODE_GE:            return "GE";
        case NODE_EQ:            return "EQ";
        case NODE_NE:            return "NE";
        case NODE_AND:           return "AND";
        case NODE_OR:            return "OR";
        case NODE_NOT:           return "NOT";
        case NODE_ALLOC:         return "ALLOC";
        case NODE_FREE:          return "FREE";
        case NODE_INITIALIZE:    return "INITIALIZE";
        case NODE_NEW:           return "NEW";
        case NODE_DELETE:        return "DELETE";
        case NODE_SELF:          return "SELF";
        default:                 return "UNKNOWN";
    }
}

void printAST(struct tnode *t, int level)
{
    if (!t) return;

    for (int i = 0; i < level; i++) printf("  ");
    printf("|- %s", nodeTypeToString(t->nodetype));

    if (t->nodetype == NODE_NUM)    printf(" (%d)", t->val);
    if (t->nodetype == NODE_STRING) printf(" (%s)", t->strVal);

    if (t->nodetype == NODE_ID     ||
        t->nodetype == NODE_ASSIGN ||
        t->nodetype == NODE_READ   ||
        t->nodetype == NODE_FUNCALL||
        t->nodetype == NODE_METHOD_CALL ||
        t->nodetype == NODE_FIELD)
        printf(" (%s)", t->varname);

    if (t->nodetype == NODE_FIELD && t->fieldEntry)
        printf(" .%s@%d", t->fieldEntry->name, t->fieldEntry->fieldOffset);

    if (t->typeEntry)
        printf(" [type=%s]", t->typeEntry->name);

    printf("\n");

    printAST(t->left,  level + 1);
    printAST(t->right, level + 1);
}

void deleteTree(tnode *root)
{
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}
