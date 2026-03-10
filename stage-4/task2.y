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
    int ptrLevel = 0; 

    // #define DEBUG // for debugging(comment when not needed)

    tnode *root;   /* The root of the AST */

    FILE *target_file;
    extern FILE *yyin;

    int yylex();
    void yyerror(char *s);
    extern char * yytext;
    extern int lineNumber;

%}



%token NUM ID STRING INT STR ADDRESS_OF
%token PLUS MINUS MUL DIV
%token LT LE GT GE EQ NE
%token LPAREN RPAREN ASSIGN SEMICOLON COMMA RSQBR LSQBR
%token kBEGIN kEND
%token WRITE READ
%token IF THEN ELSE WHILE ENDIF ENDWHILE DO
%token DECL ENDDECL


%left PLUS MINUS
%left MUL DIV

%nonassoc GE GT LE LT NE EQ

%%

Program:
      DECL DeclList ENDDECL kBEGIN Slist kEND
        {
            root = $5; 
        }
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
    INT   
    { 
        currentType = TYPE_INT; 
        ptrLevel = PTR_LEVEL_0;
    }
    | STR   
    { 
        currentType = TYPE_STRING; 
        ptrLevel = PTR_LEVEL_0;
    }

VarList:
    VarList COMMA ID                                    
    { 
        if (ptrLevel > 0) {
            InstallPointer($3->varname, currentType, ptrLevel);
        } else {
            Install($3->varname, currentType, 1); 
        }
    }
    | VarList COMMA ID LSQBR NUM RSQBR                  
    { 
        if (ptrLevel > 0) {
            fprintf(stderr, "Parse error: line number:%d\nArrays cannot be pointers\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        }
        Install1DArray($3->varname, currentType, $5->val); 
    }
    | VarList COMMA ID LSQBR NUM RSQBR LSQBR NUM RSQBR  
    { 
        if (ptrLevel > 0) {
            fprintf(stderr, "Parse error: line number:%d\nArrays cannot be pointers\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        }
        Install2DArray($3->varname, currentType, $5->val, $8->val); 
    }
    | ID LSQBR NUM RSQBR                                
    { 
        if (ptrLevel > 0) {
            fprintf(stderr, "Parse error: line number:%d\nArrays cannot be pointers\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        }
        Install1DArray($1->varname, currentType, $3->val); 
    }
    | ID LSQBR NUM RSQBR LSQBR NUM RSQBR                
    { 
        if (ptrLevel > 0) {
            fprintf(stderr, "Parse error: line number:%d\nArrays cannot be pointers\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        }
        Install2DArray($1->varname, currentType, $3->val, $6->val); 
    }
    | MUL ID
    {  
        ptrLevel = PTR_LEVEL_1;
        InstallPointer($2->varname, TYPE_POINTER, ptrLevel);
        ptrLevel = PTR_LEVEL_0;
    }
    | MUL MUL ID      
    { 
        ptrLevel = PTR_LEVEL_2;
        InstallPointer($3->varname, TYPE_POINTER, ptrLevel);
        ptrLevel = PTR_LEVEL_0;
    }
    | VarList COMMA MUL ID
    {  
        ptrLevel = PTR_LEVEL_1;
        InstallPointer($4->varname, TYPE_POINTER, ptrLevel);
        ptrLevel = PTR_LEVEL_0;
    }
    | VarList COMMA MUL MUL ID      
    { 
        ptrLevel = PTR_LEVEL_2;
        InstallPointer($5->varname, TYPE_POINTER, ptrLevel);
        ptrLevel = PTR_LEVEL_0;
    }
    | ID                                                
    { 
        if (ptrLevel > 0) {
            InstallPointer($1->varname, currentType, ptrLevel);
        } else {
            Install($1->varname, currentType, 1);
        }
    }
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
    READ LPAREN ID RPAREN                             { $$ = makeReadNode(makeVarNode($3->varname)); }
    | READ LPAREN ID LSQBR E RSQBR RPAREN               { $$ = makeReadNode(makeArrayNode($3, $5)); }
    | READ LPAREN ID LSQBR E RSQBR LSQBR E RSQBR RPAREN { $$ = makeReadNode(make2dArrayNode($3, $5, $8)); }
    | READ LPAREN MUL ID RPAREN               
    { 
        tnode* ptr_node = makeVarNode($4->varname);
        $$ = makeReadNode(makeDerefNode(ptr_node)); 
    }
    ;

OutputStmt:
    WRITE LPAREN E RPAREN { $$ = makeWriteNode($3); }
    ;

AssgStmt:
    ID ASSIGN E 
    {
        struct Gsymbol *g = Lookup($1->varname);
        if (!g) {
            fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, $1->varname, yytext);
            exit(1);
        }
        if (g->type != $3->type) {
            fprintf(stderr, "Parse error: line number:%d\nType mismatch in assignment to %s\nyytext:%s\n", lineNumber, $1->varname, yytext);
            exit(1);
        }
        $$ = makeAssignNode(makeVarNode($1->varname), $3);
    }

    | ID LSQBR E RSQBR ASSIGN E
    {
        struct Gsymbol *g = Lookup($1->varname);
        if (!g) {
            fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, $1->varname, yytext);
            exit(1);
        }
        if (g->type != $6->type) {
            fprintf(stderr, "Parse error: line number:%d\nType mismatch in assignment to %s\nyytext:%s\n", lineNumber, $1->varname, yytext);
            exit(1);
        }
        if ($3->type != TYPE_INT) {
            fprintf(stderr, "Parse error: line number:%d\nArray index should be TYPE_INT (array:%s)\nyytext:%s\n", lineNumber, $1->varname, yytext);
            exit(1);
        }
        $$ = makeArrayAssignNode(makeArrayNode($1, $3), $6);
    }

    | ID LSQBR E RSQBR LSQBR E RSQBR ASSIGN E
    {
        struct Gsymbol *g = Lookup($1->varname);
        if (!g) {
            fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, $1->varname, yytext);
            exit(1);
        }
        if (g->type != $9->type) {
            fprintf(stderr, "Parse error: line number:%d\nType mismatch in assignment to %s\nyytext:%s\n", lineNumber, $1->varname, yytext);
            exit(1);
        }
        if ($3->type != TYPE_INT || $6->type != TYPE_INT) {
            fprintf(stderr, "Parse error: line number:%d\nArray index should be TYPE_INT (array:%s)\nyytext:%s\n", lineNumber, $1->varname, yytext);
            exit(1);
        }
        $$ = makeArray2DAssignNode(make2dArrayNode($1, $3, $6), $9);
    }
    | MUL ID ASSIGN E
    {
        struct Gsymbol *g = Lookup($2->varname);
        if (!g) {
            fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, $2->varname, yytext);
            exit(1);
        }
        if (g->ptrLevel == 0) {
            fprintf(stderr, "Parse error: line number:%d\nCannot dereference non-pointer: %s\nyytext:%s\n", lineNumber, $2->varname, yytext);
            exit(1);
        }
        tnode* ptr_node = makeVarNode($2->varname);
        tnode* deref_node = makeDerefNode(ptr_node);
        $$ = makeAssignNode(deref_node, $4);
        
    }
    ;


IfStmt:
    IF LPAREN E RPAREN THEN Slist ELSE Slist ENDIF
        { 
            if($3->type != TYPE_BOOL)
            {
                fprintf(stderr, "Parse error: line number:%d\nIF statement expects BOOL expression\nyytext:%s\n", lineNumber, yytext);
                exit(1);
            }
            $$ = makeIfElseNode($3, $6, $8); 
        }
    | IF LPAREN E RPAREN THEN Slist ENDIF
        { 
            if($3->type != TYPE_BOOL)
            {
                fprintf(stderr, "Parse error: line number:%d\nIF statement expects BOOL expression\nyytext:%s\n", lineNumber, yytext);
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
                fprintf(stderr, "Parse error: line number:%d\nWHILE statement expects BOOL expression\nyytext:%s\n", lineNumber, yytext);
                exit(1);
            }
            $$ = makeWhileNode($3, $6); 
        }
    ;

E:
    E PLUS E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\ntype mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            $$ = makeArithNode(NODE_PLUS, $1, $3);
        }
    }
    | E MINUS E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\ntype mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            $$ = makeArithNode(NODE_MINUS, $1, $3);
        }
    }
    | E MUL E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\ntype mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            $$ = makeArithNode(NODE_MUL, $1, $3);
        }
    }
    | E DIV E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            $$ = makeArithNode(NODE_DIV, $1, $3);
        }
    }
    | LPAREN E RPAREN { $$ = $2; }

    | E LT E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_LT, $1, $3);
        }
    }
    | E LE E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_LE, $1, $3);
        }
    }
    | E GT E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_GT, $1, $3);
        }
    }
    | E GE E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_GE, $1, $3);
        }
    }
    | E EQ E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_EQ, $1, $3);
        }
    }
    | E NE E {
        if (($1->type != TYPE_INT) || ($3->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_NE, $1, $3);
        }
    }
    | NUM       { $$ = $1; }
    | STRING    { $$ = $1; }
    | ID LSQBR E RSQBR { 
                            struct Gsymbol *g = Lookup($1->varname);
                            if (!g) {
                                fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, $1->varname, yytext);
                                exit(1);
                            }
                            if ($3->type != TYPE_INT) {
                                fprintf(stderr, "Parse error: line number:%d\nArray index should be TYPE_INT (array:%s)\nyytext:%s\n", lineNumber, $1->varname, yytext);
                                exit(1);
                            }
                            $$ = makeArrayNode($1, $3);
                        }
    | ID LSQBR E RSQBR LSQBR E RSQBR {
                                        struct Gsymbol *g = Lookup($1->varname);
                                        if (!g) {
                                            fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, $1->varname, yytext);
                                            exit(1);
                                        }
                                        if ($3->type != TYPE_INT || $6->type != TYPE_INT) {
                                            fprintf(stderr, "Parse error: line number:%d\nArray index should be TYPE_INT (array:%s)\nyytext:%s\n", lineNumber, $1->varname, yytext);
                                            exit(1);
                                        }
                                        $$ = make2dArrayNode($1, $3, $6);
                                     }
    | ADDRESS_OF ID 
        {
            struct Gsymbol *g = Lookup($2->varname);
            if (!g) {
                fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, $2->varname, yytext);
                exit(1);
            }
            if (g->ptrLevel > 0) {
                fprintf(stderr, "Parse error: line number:%d\nCannot take address of pointer: %s\nyytext:%s\n", lineNumber, $2->varname, yytext);
                exit(1);
            }
            tnode* t = makeVarNode($2->varname);
            $$ = makePointerNode(t);
            $$->type = TYPE_POINTER;
        }
    
    | MUL ID
        {
            struct Gsymbol *g = Lookup($2->varname);
            if (!g) {
                fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, $2->varname, yytext);
                exit(1);
            }
            if (g->ptrLevel == 0) {
                fprintf(stderr, "Parse error: line number:%d\nCannot dereference non-pointer: %s\nyytext:%s\n", lineNumber, $2->varname, yytext);
                exit(1);
            }
            tnode* t = makeVarNode($2->varname);
            $$ = makeDerefNode(t);
            $$->type = g->type;
        }
    
    | MUL LPAREN E RPAREN
        {
            if ($3->type != TYPE_POINTER) {
                fprintf(stderr, "Parse error: line number:%d\nCannot dereference non-pointer expression\nyytext:%s\n", lineNumber, yytext);
                exit(1);
            }
            $$ = makeDerefNode($3);
            /* Type depends on what's being pointed to */
        }

    | ID    
        {
            struct Gsymbol *g = Lookup($1->varname);
            if (!g) {
                fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, $1->varname, yytext);
                exit(1);
            }
            $$ = makeVarNode($1->varname);
        }


    ;

%%

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.expl> <output.xsm>\n", argv[0]);
        return 1;
    }

    FILE *source_file = fopen(argv[1], "r");
    if (!source_file) {
        fprintf(stderr, "Parse error: line number:%d\nfopen input\nyytext:%s\n", lineNumber, yytext);
        return 1;
    }

    yyin = source_file;

    if (yyparse() != 0) {
        fprintf(stderr, "Parsing failed\n");
        fclose(source_file);
        return 1;
    }

    fclose(source_file);

    if (!root) {
        fprintf(stderr, "Empty or invalid program\n");
        return 1;
    }

#ifdef DEBUG
    printSymbolTable();
    printAST(root, 0);
#endif

    FILE *temp = tmpfile();
    if (!temp) {
        fprintf(stderr, "Parse error: line number:%d\ntmpfile\nyytext:%s\n", lineNumber, yytext);
        return 1;
    }

    initReg();
    fileinit(temp);
    moveStackPointer(temp);
    codeGen(root, temp);
    emitExit(temp);

    rewind(temp);

    buildLabelTable(temp);

    FILE *out = fopen(argv[2], "w");
    if (!out) {
        fprintf(stderr, "Parse error: line number:%d\nfopen output\nyytext:%s\n", lineNumber, yytext);
        fclose(temp);
        return 1;
    }

    translateLabels(temp, out);

    fclose(out);
    fclose(temp);   

    return 0;
}

void yyerror(char *s)
{
    fprintf(stderr, "Parse error: currentType:%d\nline number:%d\n%s\nyytext:%s\n",currentType, lineNumber, s, yytext);
}