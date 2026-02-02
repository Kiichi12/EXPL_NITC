%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "tree.h"
    #include "memory.h"

    void yyerror(char *s);
    int yylex();
    extern FILE *yyin;
    extern int lineNumber;
    extern char *yytext;
    tnode *root;
%}

%union {
    struct tnode *node;
    struct Paramstruct *param;
    struct TypeInfo typeData;
}

%token <node> NUM ID STRING
%token INT STR MAIN DECL ENDDECL kBEGIN kEND WRITE READ RETURN IF THEN ELSE ENDIF WHILE DO ENDWHILE SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE LSQBR RSQBR ASSIGN ADDRESS_OF
%type <node> E Stmt Slist InputStmt OutputStmt AssgStmt IfStmt WhileStmt Body MainBlock ArgList
%type <param> Param ParamList
%type <typeData> Type


%left PLUS MINUS
%left MUL DIV

%nonassoc LT LE GT GE EQ NE

%nonassoc UNARY /* for dereference and address-of */

%%

Program:
    GDeclarations FdefBlock MainBlock { 
            root = $3; 
        }
    | GDeclarations MainBlock        { 
            root = $2; 
        }
    ;

GDeclarations: 
    DECL GdeclList ENDDECL 
    | DECL ENDDECL 
    | /* empty */ 
    ;

GdeclList: 
    GdeclList GDecl 
    | GDecl
    ;

GDecl: 
    Type GidList SEMICOLON;

GidList: 
    GidList COMMA Gid 
    | Gid
    ;

Gid:
    ID {
        if ($<typeData>0.ptrLevel > 0) 
            InstallPointer($1->varname, $<typeData>0.type, $<typeData>0.ptrLevel);
        else 
            Install($1->varname, $<typeData>0.type, 1);
    }
    | ID LSQBR NUM RSQBR {
        Install1DArray($1->varname, $<typeData>0.type, $3->val);
    }
    | ID LSQBR NUM RSQBR LSQBR NUM RSQBR {
        Install2DArray($1->varname, $<typeData>0.type, $3->val, $6->val);
    }
    | ID LPAREN ParamList RPAREN {
        InstallFunction($1->varname, $<typeData>0.type, $3);
    }
    | ID LPAREN RPAREN {
        InstallFunction($1->varname, $<typeData>0.type, NULL);
    }
    ;

Type:
    INT { $$.type = TYPE_INT; $$.ptrLevel = 0; }
    | STR { $$.type = TYPE_STRING; $$.ptrLevel = 0; }
    | MUL Type { $$ = $2; $$.ptrLevel++; }
    ;

ParamList:
    ParamList COMMA Param { $$ = AppendParam($1, $3); }
    | Param { $$ = $1; }
    ;

Param:
    Type ID { $$ = CreateParam($2->varname, $1.type, $1.ptrLevel); }
    ;

FdefBlock: FdefBlock Fdef | Fdef;

Fdef: Type ID LPAREN ParamList RPAREN LBRACE LdeclBlock Body RBRACE { /* Task 2 Logic */ }
    | Type ID LPAREN RPAREN LBRACE LdeclBlock Body RBRACE { /* Task 2 Logic */ }
    ;

LdeclBlock: DECL LdeclList ENDDECL | DECL ENDDECL | /* empty */ ;
LdeclList: LdeclList LDecl | LDecl;
LDecl: Type IdList SEMICOLON;
IdList: IdList COMMA ID | ID;

MainBlock:
    INT MAIN LPAREN RPAREN LBRACE LdeclBlock Body RBRACE { $$ = $7; }
    ;

Body:
    kBEGIN Slist kEND { $$ = $2; }
    | kBEGIN kEND     { $$ = NULL; }
    ;

Slist:
    Slist Stmt SEMICOLON { $$ = makeConnectorNode($1, $2); }
    | Stmt SEMICOLON     { $$ = $1; }
    ;

Stmt:
    InputStmt | OutputStmt | AssgStmt | IfStmt | WhileStmt 
    | RETURN E { $$ = makeConnectorNode(NULL, $2); }
    ;

InputStmt:
    READ LPAREN ID RPAREN                             { $$ = makeReadNode(makeVarNode($3->varname)); }
    | READ LPAREN ID LSQBR E RSQBR RPAREN               { $$ = makeReadNode(makeArrayNode($3, $5)); }
    ;

OutputStmt:
    WRITE LPAREN E RPAREN { $$ = makeWriteNode($3); }
    ;

AssgStmt:
    ID ASSIGN E { $$ = makeAssignNode(makeVarNode($1->varname), $3); }
    | ID LSQBR E RSQBR ASSIGN E { $$ = makeArrayAssignNode(makeArrayNode($1, $3), $6); }
    | MUL ID ASSIGN E %prec UNARY { 
        tnode* deref = makeDerefNode(makeVarNode($2->varname));
        $$ = makeAssignNode(deref, $4); 
    }
    ;

IfStmt:
    IF LPAREN E RPAREN THEN Slist ELSE Slist ENDIF { $$ = makeIfElseNode($3, $6, $8); }
    | IF LPAREN E RPAREN THEN Slist ENDIF          { $$ = makeIfNode($3, $6); }
    ;

WhileStmt:
    WHILE LPAREN E RPAREN DO Slist ENDWHILE { $$ = makeWhileNode($3, $6); }
    ;

E:
    E PLUS E    { $$ = makeArithNode(NODE_PLUS, $1, $3); }
    | E MINUS E { $$ = makeArithNode(NODE_MINUS, $1, $3); }
    | E MUL E   { $$ = makeArithNode(NODE_MUL, $1, $3); }
    | E DIV E   { $$ = makeArithNode(NODE_DIV, $1, $3); }
    | E LT E    { $$ = makeBoolNode(NODE_LT, $1, $3); }
    | E GT E    { $$ = makeBoolNode(NODE_GT, $1, $3); }
    | E EQ E    { $$ = makeBoolNode(NODE_EQ, $1, $3); }
    | NUM       { $$ = $1; }
    | STRING    { $$ = $1; }
    | ID        { $$ = makeVarNode($1->varname); }
    | ID LPAREN ArgList RPAREN { $$ = makeFuncallNode($1->varname, $3); }
    | ID LPAREN RPAREN         { $$ = makeFuncallNode($1->varname, NULL); }
    | MUL E %prec UNARY        { $$ = makeDerefNode($2); }
    | ADDRESS_OF ID %prec UNARY { $$ = makePointerNode(makeVarNode($2->varname)); }
    | LPAREN E RPAREN          { $$ = $2; }
    ;

ArgList:
    ArgList COMMA E { $$ = makeConnectorNode($1, $3); }
    | E             { $$ = $1; }
    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "Error at line %d: %s\n", lineNumber, s);
}

int main(int argc, char **argv) {
    if(argc > 1) {
        FILE *fp = fopen(argv[1], "r");
        if(fp) yyin = fp;
    }
    yyparse();
    printSymbolTable();
    return 0;
}