%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "tree.h"
    #include "register.h"
    #include "labels.h"
    #include "memory.h"
    #include "codegeneration.h"

    void printAST(struct tnode* t, int level);

    int currentType;
    tnode *root;   /* The root of the AST */

    FILE *target_file;
    extern FILE *yyin;

    int yylex();
    void yyerror(char *s);
%}

%token NUM ID STRING INT STR
%token PLUS MINUS MUL DIV
%token LT LE GT GE EQ NE
%token LPAREN RPAREN ASSIGN SEMICOLON COMMA
%token kBEGIN kEND
%token WRITE READ
%token IF THEN ELSE WHILE ENDIF ENDWHILE DO
%token DECL ENDDECL


%left PLUS MINUS
%left MUL DIV

%%

Program:
      DECL DeclList ENDDECL kBEGIN Slist kEND
        { root = $5; }
    |   DECL ENDDECL kBEGIN Slist kEND
        { root = $4; }
    |   kBEGIN Slist kEND      
        { root = $2; }
    | kBEGIN kEND         { $$ = NULL; }
    ;

DeclList:
    DeclList Decl
    | Decl
    ;

Decl:
    Type VarList SEMICOLON
    ;

Type:
    INT   { currentType = TYPE_INT; }
    | STR   { currentType = TYPE_STRING; }
    ;

VarList:
    VarList COMMA ID   { Install($3->varname, currentType, 1); }
    | ID                 { Install($1->varname, currentType, 1); }
    ;


Slist:
    Slist Stmt SEMICOLON { $$ = makeConnectorNode($1, $2); }
    | Stmt SEMICOLON     { $$ = $1; }
    ;

Stmt:
    InputStmt             { $$ = $1; }
    | OutputStmt          { $$ = $1; }
    | AssgStmt            { $$ = $1; }
    | IfStmt              { $$ = $1; }
    | WhileStmt           { $$ = $1; }
    ;

InputStmt:
    READ LPAREN ID RPAREN { $$ = makeReadNode(makeVarNode($3->varname)); }
    ;

OutputStmt:
    WRITE LPAREN E RPAREN { $$ = makeWriteNode($3); }
    ;

AssgStmt:
    ID ASSIGN E 
    {
        struct Gsymbol *g = Lookup($1->varname);
        if (!g) {
            fprintf(stderr, "Undeclared variable: %s\n", $1->varname);
            exit(1);
        }
        if (g->type != $3->type) {
            fprintf(stderr, "Type mismatch in assignment to %s\n", $1->varname);
            exit(1);
        }
        $$ = makeAssignNode(makeVarNode($1->varname), $3);
    }
;


IfStmt:
    IF LPAREN E RPAREN THEN Slist ELSE Slist ENDIF
        { 
            if($3->type != TYPE_BOOL)
            {
                fprintf(stderr, "IF statement expects BOOL expression\n");
                exit(1);
            }
            $$ = makeIfElseNode($3, $6, $8); 
        }
    | IF LPAREN E RPAREN THEN Slist ENDIF
        { 
            if($3->type != TYPE_BOOL)
            {
                fprintf(stderr, "IF statement expects BOOL expression\n");
                exit(1);
            }
            $$ = makeIfNode($3, $6); 
        }
    ;

WhileStmt:
    WHILE LPAREN E RPAREN DO Slist ENDWHILE
        {
            if($3->type != TYPE_BOOL)
            {
                fprintf(stderr, "WHILE statement expects BOOL expression\n");
                exit(1);
            }
           $$ = makeWhileNode($3, $6); 
        }
    ;

E:
    E PLUS E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            perror("type mismatch");
            exit(1);
        } else {
            $$ = makeArithNode(NODE_PLUS, $1, $3);
        }
    }
    | E MINUS E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            perror("type mismatch");
            exit(1);
        } else {
            $$ = makeArithNode(NODE_MINUS, $1, $3);
        }
    }
    | E MUL E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            perror("type mismatch");
            exit(1);
        } else {
            $$ = makeArithNode(NODE_MUL, $1, $3);
        }
    }
    | E DIV E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeArithNode(NODE_DIV, $1, $3);
        }
    }
    | LPAREN E RPAREN { $$ = $2; }

    | E LT E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_LT, $1, $3);
        }
    }
    | E LE E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_LE, $1, $3);
        }
    }
    | E GT E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_GT, $1, $3);
        }
    }
    | E GE E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_GE, $1, $3);
        }
    }
    | E EQ E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_EQ, $1, $3);
        }
    }
    | E NE E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_NE, $1, $3);
        }
    }
    | NUM       { $$ = $1; }
    | STRING    { $$ = $1; }
    | ID    {
                struct Gsymbol *g = Lookup($1->varname);
                if (!g) {
                    fprintf(stderr, "Undeclared variable: %s\n", $1->varname);
                    exit(1);
                }
                $$ = makeVarNode($1->varname);
            }


    ;

%%

int main()
{
    FILE *source_file = fopen("source.expl", "r");
    yyin = source_file;

    yyparse();  // Parse and build Expression tree

    printSymbolTable(); 
    
    printAST(root, 0);

    // int result = evaluate(root);
    // for (int i = 0; i < 26; i++) {
    //     printf("%c:%d\n", 'a' + i, symtable[i]);
    // }

    // Open output file for intermediate code
    FILE *temp = fopen("temp.xsm", "w");
    if (!temp) {
        fprintf(stderr, "Error opening temp.xsm for writing\n");
        return 1;
    }

    initReg();

    // Generate code into temp.xsm
    fileinit(temp); // header and breakpt
    codeGen(root, temp);
    emitExit(temp);

    fclose(temp);  

    // reopen for reading
    temp = fopen("temp.xsm", "r");
    if (!temp) {
        fprintf(stderr, "Error opening temp.xsm for reading\n");
        return 1;
    }

    buildLabelTable(temp);

    // Open output file for target code
    FILE *target_file = fopen("target_file.xsm", "w");
    if (!target_file) {
        fprintf(stderr, "Error opening target_file.xsm for writing\n");
        return 1;
    }

    translateLabels(temp, target_file);

    return 0;
}


void yyerror(char *s)
{
    fprintf(stderr, "Parse error: %s\n", s);
}
