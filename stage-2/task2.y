%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "tree.h"
    #include "register.h"
    #include "codegeneration.h"

    void printAST(struct tnode* t, int level);

    tnode *root;   /* The root of the AST */

    FILE *target_file;
    extern FILE *yyin;

    int yylex();
    void yyerror(char *s);
%}

%token NUM ID
%token PLUS MINUS MUL DIV
%token LPAREN RPAREN ASSIGN SEMICOLON
%token kBEGIN kEND 
%token WRITE READ

%left PLUS MINUS
%left MUL DIV


%%

Program:
      kBEGIN Slist kEND   { 
                            $$ = $2; 
                            root = $$ ;
                        }
    | kBEGIN kEND           { $$ = NULL; }
    ;

Slist:
    Slist Stmt SEMICOLON   { $$ = makeConnectorNode($1,$2); }
    | Stmt SEMICOLON       { $$ = $1; }
    ;

Stmt:
    InputStmt              { $$ = $1; }
    | OutputStmt          { $$ = $1; }
    | AssgStmt             { $$ = $1; }
    ;
InputStmt:
    READ LPAREN ID RPAREN  { $$ = makeReadNode($3); };

OutputStmt:
    WRITE LPAREN expr RPAREN { $$ = makeWriteNode($3); };

AssgStmt:
    ID ASSIGN expr          { $$ = makeAssignNode($1,$3); };

expr:
    expr PLUS expr {$$ = makeArithNode(NODE_PLUS, $1, $3);}
    | expr MINUS expr {$$ = makeArithNode(NODE_MINUS, $1, $3);}
    | expr MUL expr      { $$ = makeArithNode(NODE_MUL, $1, $3); }
    | expr DIV expr      { $$ = makeArithNode(NODE_DIV, $1, $3); }
    | LPAREN expr RPAREN { $$ = $2; }
    | NUM             { $$ = $1; }
    | ID               { $$ = $1; }
    ;
%%

int main()
{
    FILE *source_file = fopen("source.expl", "r");
    yyin = source_file;

    yyparse();  // Parse and build expression tree
    printAST(root, 0);
    // Open output file for target code
    FILE *target_file = fopen("target_file.xsm", "w");
    if (!target_file) {
        fprintf(stderr, "Error opening target_file.xsm for writing\n");
        return 1;
    }

    initReg();

    // Generate code into target_file.xsm
    fileinit(target_file); // header and breakpt
    codeGen(root, target_file);
    emitExit(target_file);
    

    return 0;
}

const char* nodeTypeToString(int nodetype) {
    switch (nodetype) {
        case NODE_NUM:    return "NUM";
        case NODE_ID:     return "ID";
        case NODE_PLUS:   return "PLUS";
        case NODE_MINUS:  return "MINUS";
        case NODE_MUL:    return "MUL";
        case NODE_DIV:    return "DIV";
        case NODE_ASSIGN: return "ASSIGN";
        case NODE_READ:   return "READ";
        case NODE_WRITE:  return "WRITE";
        case NODE_CONNECTOR:   return "CONNECTOR";
        default:          return "UNKNOWN";
    }
}


void printAST(struct tnode* t, int level) {
    if (t == NULL)
        return;

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


void yyerror(char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
