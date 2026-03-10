%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "tree.h"
    #include "memory.h"
    #include "yacc-helper.h"
    #include "codegeneration.h"
    #include "register.h"
    #include "labels.h"

    void yyerror(char *s);
    int yylex();
    extern FILE *yyin;
    extern int lineNumber;
    tnode *root;
    FILE *interim_file;
    char *current_function_name;
    extern char * yytext;

    // Global variable to store the type of the current declaration line
    struct TypeInfo currentTypeData;
%}

%union 
{
    struct tnode *node;
    struct Paramstruct *param;
    struct TypeInfo typeData;
}

%token <node> NUM ID STRING 
%token INT STR MAIN DECL ENDDECL kBEGIN kEND WRITE READ RETURN IF THEN ELSE ENDIF 
       WHILE DO ENDWHILE BREAK CONTINUE SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE 
       LSQBR RSQBR ASSIGN ADDRESS_OF MUL

%type <node> E Stmt Slist InputStmt OutputStmt AssgStmt IfStmt WhileStmt ContinueStmt BreakStmt Body MainBlock ArgList
%type <param> Param ParamList
%type <typeData> Type

%left PLUS MINUS
%left MUL DIV
%nonassoc LT LE GT GE EQ NE
%nonassoc UNARY

%%

Program:
    GDeclarations FdefBlock MainBlock { root = $3; }
  | GDeclarations MainBlock { root = $2; }
  ;

GDeclarations: 
    DECL GdeclList ENDDECL 
    { 
      handleGdeclComplete(); 
    }
  | DECL ENDDECL 
  | 
  ;

GdeclList: 
  GdeclList GDecl 
  | GDecl 
  ;

GDecl: 
  Type GidList SEMICOLON 
  ;

GidList: 
  GidList COMMA Gid 
  | Gid 
  ;

Gid:
  ID 
  { 
    // Uses the global currentTypeData instead of stack reference
    handleGidScalar($1, &currentTypeData); 
  }
  | ID LSQBR NUM RSQBR 
  { 
    handleGidArray1D($1, &currentTypeData, $3->val); 
  }
  | ID LSQBR NUM RSQBR LSQBR NUM RSQBR 
  { 
    handleGidArray2D($1, &currentTypeData, $3->val, $6->val); 
  }
  | ID LPAREN ParamList RPAREN 
  { 
    handleGidFunction($1, &currentTypeData, $3); 
  }
  | ID LPAREN RPAREN 
  { 
    handleGidFunction($1, &currentTypeData, NULL); 
  }
  ;

Type:
  INT { 
      $$.type = TYPE_INT; $$.ptrLevel = 0; 
      currentTypeData = $$; // Save to global tracking
  }
  | STR { 
      $$.type = TYPE_STRING; $$.ptrLevel = 0; 
      currentTypeData = $$; // Save to global tracking
  }
  | MUL Type { 
      $$ = $2; $$.ptrLevel++; 
      currentTypeData = $$; // Update global tracking for pointers
  }
  ;

ParamList:
  ParamList COMMA Param { $$ = AppendParam($1, $3); }
  | Param { $$ = $1; }
  ;

Param:
  Type ID { $$ = CreateParam($2->varname, $1.type, $1.ptrLevel); }
  ;

FdefBlock: 
  FdefBlock Fdef 
  | Fdef 
  ;

Fdef: 
  Type ID LPAREN ParamList RPAREN 
  {
    handleParamInstall($4);
    // Set current function name
    current_function_name = $2->varname;
  }
  LBRACE LdeclBlock Body RBRACE 
  { 
    struct TypeInfo retType = $1;
    verifyFunctionSignature(Lookup($2->varname), &retType, $4);
    handleFdefPrint($2->varname, $9);

    struct Gsymbol* g = Lookup($2->varname);
    fprintf(interim_file, "F%d:\n", g->flabel);
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");

    locAlloc(interim_file);

    codeGen($9, interim_file);

    // Clear current function name
    current_function_name = NULL;

    // Now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
  | Type ID LPAREN RPAREN LBRACE LdeclBlock Body RBRACE
  {
    // Set current function name
    current_function_name = $2->varname;
    
    struct TypeInfo retType = $1;
    verifyFunctionSignature(Lookup($2->varname), &retType, NULL);
    handleFdefNoArgsPrint($2->varname, $7); 

    struct Gsymbol* g = Lookup($2->varname);
    fprintf(interim_file, "F%d:\n", g->flabel);
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");

    locAlloc(interim_file);

    codeGen($7, interim_file);

    // Clear current function name
    current_function_name = NULL;

    // Now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
  ;

LdeclBlock: 
  DECL LdeclList ENDDECL 
  | DECL ENDDECL 
  | 
  ;

LdeclList: 
  LdeclList LDecl 
  | LDecl 
  ;

LDecl: 
  Type IdList SEMICOLON 
  ;

IdList: 
  IdList COMMA ID 
  { 
    // Uses the global currentTypeData
    handleLidInstall($3->varname, &currentTypeData); 
  }
  | ID 
  { 
    handleLidInstall($1->varname, &currentTypeData); 
  }
  ;

MainBlock:
  INT MAIN
  {
    current_function_name = "MAIN";
  } 
  LPAREN RPAREN LBRACE LdeclBlock Body RBRACE 
  { 
    // Set current function name for main
    
    
    handleMainPrint($8); 
    $$ = $8; 

    fprintf(interim_file, "MAIN:\n");
    moveStackPointer(interim_file);
    fprintf(interim_file, "BRKP\n");
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");
    
    locAlloc(interim_file);

    codeGen($$, interim_file);

    // Clear current function name
    current_function_name = NULL;

    // Now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
;

Body: 
  kBEGIN Slist kEND { $$ = $2; } 
  | kBEGIN kEND { $$ = NULL; } 
  ;

Slist: 
  Slist Stmt SEMICOLON { $$ = makeConnectorNode($1, $2); }
  | Stmt SEMICOLON { $$ = $1; }
  ;

Stmt:
  InputStmt { $$ = $1; } 
  | OutputStmt { $$ = $1; } 
  | AssgStmt { $$ = $1; }
  | IfStmt { $$ = $1; }
  | WhileStmt { $$ = $1; }
  | BreakStmt { $$ = $1; }
  | ContinueStmt { $$ = $1; }
  | RETURN E { $$ = makeReturnNode($2, current_function_name); }
  | RETURN { $$ = makeReturnNode(NULL, current_function_name); } 
  ;

InputStmt:
  READ LPAREN ID RPAREN { $$ = makeReadNode(makeVarNode($3->varname)); }
  | READ LPAREN ID LSQBR E RSQBR RPAREN { $$ = makeReadNode(makeArrayNode($3, $5)); }
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
  ID ASSIGN E { $$ = makeAssignNode(makeVarNode($1->varname), $3); }
  | ID LSQBR E RSQBR ASSIGN E { $$ = makeArrayAssignNode(makeArrayNode($1, $3), $6); }
  | ID LSQBR E RSQBR LSQBR E RSQBR ASSIGN E { $$ = makeArray2DAssignNode(make2dArrayNode($1, $3, $6), $9); }
  | MUL ID ASSIGN E %prec UNARY 
  { 
    tnode* deref = makeDerefNode(makeVarNode($2->varname));
    $$ = makeAssignNode(deref, $4); 
  }
  ;

IfStmt:
  IF LPAREN E RPAREN THEN Slist ELSE Slist ENDIF { $$ = makeIfElseNode($3, $6, $8); }
  | IF LPAREN E RPAREN THEN Slist ENDIF { $$ = makeIfNode($3, $6); }
  ;

WhileStmt: 
  WHILE LPAREN E RPAREN DO Slist ENDWHILE { $$ = makeWhileNode($3, $6); }
  ;

BreakStmt: 
  BREAK { $$ = makeBreakNode(); } 
  ;

ContinueStmt: 
  CONTINUE { $$ = makeContinueNode(); } 
  ;

E:
  E PLUS E { $$ = makeArithNode(NODE_PLUS, $1, $3); }
  | E MINUS E { $$ = makeArithNode(NODE_MINUS, $1, $3); }
  | E MUL E { $$ = makeArithNode(NODE_MUL, $1, $3); }
  | E DIV E { $$ = makeArithNode(NODE_DIV, $1, $3); }
  | E LT E { $$ = makeBoolNode(NODE_LT, $1, $3); }
  | E GT E { $$ = makeBoolNode(NODE_GT, $1, $3); }
  | E EQ E { $$ = makeBoolNode(NODE_EQ, $1, $3); }
  | E LE E { $$ = makeBoolNode(NODE_LE, $1, $3); }
  | E GE E { $$ = makeBoolNode(NODE_GE, $1, $3); }
  | E NE E { $$ = makeBoolNode(NODE_NE, $1, $3); }
  | NUM { $$ = $1; }
  | STRING { $$ = $1; }
  | ID { $$ = makeVarNode($1->varname); }
  | ID LPAREN ArgList RPAREN { $$ = makeFuncallNode($1->varname, $3); }
  | ID LPAREN RPAREN { $$ = makeFuncallNode($1->varname, NULL); }
  | MUL E %prec UNARY { $$ = makeDerefNode($2); }
  | ADDRESS_OF ID %prec UNARY { $$ = makePointerNode(makeVarNode($2->varname)); }
  | LPAREN E RPAREN { $$ = $2; }
  | ID LSQBR E RSQBR { $$ = makeArrayNode($1, $3); }
  | ID LSQBR E RSQBR LSQBR E RSQBR { $$ = make2dArrayNode($1, $3, $6); }
  ;

ArgList: 
  ArgList COMMA E { $$ = makeConnectorNode($1, $3); } 
  | E { $$ = $1; } 
  ;

%%

void yyerror(char *s) 
{
  fprintf(stderr, "Error at line %d: %s\n", lineNumber, s);
}

int main(int argc, char **argv) 
{
  if (argc < 3)   
  {
    fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
    return 1;
  }
  
  FILE *fp = fopen(argv[1], "r");
  if (fp) yyin = fp;
  else {
    fprintf(stderr, "Error: Cannot open input file %s\n", argv[1]);
    return 1;
  }

  FILE * target_file = fopen(argv[2], "w");
  if (!target_file) {
    fprintf(stderr, "Error: Cannot open output file %s\n", argv[2]);
    return 1;
  }

  interim_file = fopen("interim_file.xsm", "w");
  if (!interim_file) {
    fprintf(stderr, "Error: Cannot open interim file\n");
    return 1;
  }

  initReg();
  fileinit(interim_file);
  
  // Initialize current function name
  current_function_name = NULL;
  
  yyparse();
  emitExit(interim_file);

  fclose(interim_file);

  interim_file = fopen("interim_file.xsm", "r");
  rewind(interim_file);
  buildLabelTable(interim_file);

  translateLabels(interim_file, target_file);

  fclose(interim_file);
  fclose(target_file);
  return 0;
}