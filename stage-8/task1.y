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
    #include "typetable.h"
    #include "classtable.h"

    void yyerror(char *s);
    int yylex();
    extern FILE *yyin;
    extern int lineNumber;
    tnode *root;
    FILE *interim_file;
    char *current_function_name;
    extern char * yytext;

    // to store the type of the current declaration line
    struct TypeInfo currentTypeData;

    // to store the udeftype being defined
    static TypeTableEntry *currentUdefType = NULL;

    // to store the current class being defined
    static ClassTableEntry *currentClassEntry = NULL;

    // for usage of self in method definitions
    ClassTableEntry *selfClassEntry = NULL;
%}

%union 
{
    struct tnode *node;
    struct Paramstruct *param;
    struct TypeInfo typeData;
}

%token <node> NUM ID STRING SELF_KW
%token INT STR MAIN DECL ENDDECL kBEGIN kEND WRITE READ RETURN 
       IF THEN ELSE ENDIF 
       WHILE DO ENDWHILE BREAK CONTINUE 
       SEMICOLON COMMA LPAREN RPAREN LBRACE RBRACE LSQBR RSQBR 
       ASSIGN 
       ADDRESS_OF MUL 
       TYPE_KW ENDTYPE DOT
       ALLOC FREE_KW INITIALIZE NULLVAL
       CLASS ENDCLASS NEW_KW DELETE_KW EXTENDS

%type <node> E Stmt Slist InputStmt OutputStmt AssgStmt IfStmt WhileStmt ContinueStmt BreakStmt Body MainBlock ArgList LValue FreeStmt InitStmt FieldAccess DeleteStmt
%type <param> Param ParamList
%type <typeData> Type

%left OR
%left AND
%right NOT
%left PLUS MINUS
%left MUL DIV
%nonassoc LT LE GT GE EQ NE
%nonassoc UNARY
%nonassoc THEN
%nonassoc ELSE

%%

Program:
  TypeDefBlock ClassDefBlock 
  {
    int numClasses = 0;
    ClassTableEntry *cc = classTableHead;
    while (cc) 
    { 
      numClasses++; 
      cc = cc->next; 
    }
    if (numClasses > 0)
      advanceNextBinding(numClasses * 8);
  }
  GDeclarations FdefBlock MainBlock { root = $6; }
  ;

ClassDefBlock:
  CLASS ClassDeflist ENDCLASS { printClassTable(); }
  | CLASS ENDCLASS
  |
  ;
ClassDeflist:
  ClassDeflist ClassDef
  | ClassDef
  ;

ClassDef:
  ID 
  {
    currentClassEntry = installClass($1->varname, NULL);
    currentUdefType = currentClassEntry->type;
  }
  LBRACE DECL ClassMemberDecList ENDDECL MethodDefList RBRACE
  {
    if (currentClassEntry)
    {
      printf("\n--- Class '%s' definition complete ---\n", currentClassEntry->name);
      printClassTable();
    }
    currentClassEntry = NULL;
    currentUdefType = NULL;
  }
  | ID EXTENDS ID
  {
    currentClassEntry = installClass($1->varname, $3->varname);
    currentUdefType = currentClassEntry->type;
  }
  LBRACE DECL ClassMemberDecList ENDDECL MethodDefList RBRACE
  {
    if (currentClassEntry)
    {
      printf("\n--- Class '%s' definition complete ---\n", currentClassEntry->name);
      // printClassTable();
    }
    currentClassEntry = NULL;
    currentUdefType = NULL;
  }
  ;

ClassMemberDecList:
  ClassMemberDecList ClassMemberDec
  | ClassMemberDec
  ;

ClassMemberDec:
  Type ID SEMICOLON
  {
    if(!currentClassEntry)
    {
      fprintf(stderr, "Error: handleClassFieldDec called outside a class definition\n");
      exit(1);  
    }

    TypeTableEntry *t;
    if($1.type == TYPE_USERDEF || $1.type == TYPE_CLASS)
    {
      t = $1.typeEntry;
    }
    else
    {
      if($1.type == TYPE_INT)
      {
        t = lookupType("int");
      }
      if($1.type == TYPE_STRING)
      {
        t = lookupType("string");
      }
      if($1.type == TYPE_BOOL)
      {
        t = lookupType("bool");
      }
    }
    
    addField(currentClassEntry->type, $2->varname, t);
  }
  | Type ID LPAREN ParamList RPAREN SEMICOLON
  {
    if(!currentClassEntry)
    {
      fprintf(stderr, "Error: handleMethodDec called outside a class definition\n");
      exit(1);
    }
    addMethod(currentClassEntry, $2->varname, $1.type, $1.typeEntry, $4);
  }
  | Type ID LPAREN RPAREN SEMICOLON
  {
    if(!currentClassEntry)
    {
      fprintf(stderr, "Error: handleMethodDec called outside a class definition\n");
      exit(1);
    }
    addMethod(currentClassEntry, $2->varname, $1.type, $1.typeEntry, NULL);
  }
  ;

// ClassFieldDecList:
//   ClassFieldDecList ClassFieldDec
//   | ClassFieldDec
//   |
//   ;

// ClassFieldDec:
//   Type ID SEMICOLON
//   {
//     if(!currentClassEntry)
//     {
//       fprintf(stderr, "Error: handleClassFieldDec called outside a class definition\n");
//       exit(1);  
//     }

//     TypeTableEntry *t;
//     if($1.type == TYPE_USERDEF)
//     {
//       t = $1.typeEntry;
//     }
//     else
//     {
//       if($1.type == TYPE_INT)
//       {
//         t = lookupType("int");
//       }
//       if($1.type == TYPE_STRING)
//       {
//         t = lookupType("string");
//       }
//       if($1.type == TYPE_BOOL)
//       {
//         t = lookupType("bool");
//       }
//     }
    
//     addField(currentClassEntry->type, $2->varname, t);
//   }
//   ;

// MethodDecList:
//   MethodDecList MethodDec
//   | MethodDec
//   |
//   ;

// MethodDec:
//   Type ID LPAREN ParamList RPAREN SEMICOLON
//   {
//     if(!currentClassEntry)
//     {
//       fprintf(stderr, "Error: handleMethodDec called outside a class definition\n");
//       exit(1);
//     }
//     addMethod(currentClassEntry, $2->varname, $1.type, $1.typeEntry, $4);
//   }
//   | Type ID LPAREN RPAREN SEMICOLON
//   {
//     if(!currentClassEntry)
//     {
//       fprintf(stderr, "Error: handleMethodDec called outside a class definition\n");
//       exit(1);
//     }
//     addMethod(currentClassEntry, $2->varname, $1.type, $1.typeEntry, NULL);
//   }
//   ;

MethodDefList:
  MethodDefList MethodDef
  | MethodDef
  |
  ;

MethodDef: 
  Type ID LPAREN ParamList RPAREN 
  {
    // set current function name
    current_function_name = $2->varname;

    if(currentClassEntry)
    {
      InstallParamsToLSTMethod($4, currentClassEntry->type);
    }
  }
  LBRACE LdeclBlock Body RBRACE 
  { 
    struct TypeInfo retType = $1;
    
    verifyMethodSignature(currentClassEntry, $2->varname, &retType, $4);

    handleFdefPrint($2->varname, $9);
    
    Gsymbol *method = malloc(sizeof(Gsymbol));
    method->name = strdup($2->varname);
    MethodEntry *MethodEntry = lookupMethod(currentClassEntry, method->name);
    method->flabel = MethodEntry->flabel;
    
    /*
    fprintf(interim_file, "F%d:\n", g->flabel);
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");

    locAlloc(interim_file);
    */

    codeGen($9, interim_file, method);

    // clear current function name
    current_function_name = NULL;

    selfClassEntry = NULL;

    // now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
  | Type ID LPAREN RPAREN 
  {
    // set current function name
    current_function_name = $2->varname;
    
    if(currentClassEntry)
    {
      InstallParamsToLSTMethod(NULL, currentClassEntry->type); // to install self in LST
    }
  }
  LBRACE LdeclBlock Body RBRACE
  {
    struct TypeInfo retType = $1;
    Paramstruct *p = malloc(sizeof(Paramstruct));
    p->next = NULL;
    p->type = TYPE_NULL;
    verifyMethodSignature(currentClassEntry, $2->varname, &retType, p);

    handleFdefPrint($2->varname, $8);

    Gsymbol *method = malloc(sizeof(Gsymbol));
    method->name = strdup($2->varname);
    MethodEntry *MethodEntry = lookupMethod(currentClassEntry, method->name);
    method->flabel = MethodEntry->flabel;
    /*
    fprintf(interim_file, "F%d:\n", g->flabel);
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");

    locAlloc(interim_file);
    */

    codeGen($8, interim_file, method);

    // clear current function name
    current_function_name = NULL;

    selfClassEntry = NULL;

    // now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
  ;


TypeDefBlock:
  TYPE_KW TypeDefList ENDTYPE
  {
    printTypeTable();
  }
  | 
  ;

TypeDefList:
  TypeDefList TypeDef
  | TypeDef
  ;

TypeDef:
  ID 
  {
    currentUdefType = installType($1->varname);
  } 
  LBRACE FieldDecList RBRACE 
  {
    currentUdefType = NULL; // end of type definition
  }
  ;

FieldDecList:
  FieldDecList FieldDec
  | FieldDec
  ;

FieldDec:
  Type ID SEMICOLON
  {
    TypeTableEntry *t;
    if($1.type == TYPE_USERDEF)
    {
      t = $1.typeEntry;
    }
    else
    {
      if($1.type == TYPE_INT)
      {
        t = lookupType("int");
      }
      if($1.type == TYPE_STRING)
      {
        t = lookupType("string");
      }
      if($1.type == TYPE_BOOL)
      {
        t = lookupType("bool");
      }
    }
    if(!t)
    {
      yyerror("Unknown field type");
      exit(1);
    }
    if(currentUdefType->fieldCount >= MAX_FIELDS_IN_USER_TYPE)
    {
      yyerror("Maximum fields in user type exceeded");
      exit(1);
    }

    addField(currentUdefType, $2->varname, t);
  }
  ;

/* 
FIdList:
  FIdList COMMA ID
  | ID
  ;
*/

GDeclarations: 
  DECL GDecList ENDDECL 
  { 
    handleGdecComplete(); 
  }
  | DECL ENDDECL 
  | 
  ;

GDecList: 
  GDecList GDecl 
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
    // printf("current type: %d\ncurrent var:%s\n", currentTypeData.type, $1->varname);
    handleGidScalar($1, &currentTypeData); 
  }
  | ID LSQBR NUM RSQBR 
  { 
    handleGidArray1D($1, &currentTypeData, $3->val); 
  }
  | ID LPAREN ParamList RPAREN 
  { 
    struct TypeInfo funcType = $<typeData>0;
    handleGidFunction($1, &funcType, $3); 
  }
  | ID LPAREN RPAREN 
  { 
    handleGidFunction($1, &currentTypeData, NULL); 
  }
  ;
    
Type:
  INT { 
      $$.type = TYPE_INT; $$.ptrLevel = 0; 
      currentTypeData = $$; 
  }
  | STR { 
      $$.type = TYPE_STRING; $$.ptrLevel = 0; 
      currentTypeData = $$; 
  }
  | MUL Type { 
      $$ = $2; $$.ptrLevel++; 
      currentTypeData = $$; 
  }
  | ID {
      TypeTableEntry *t = lookupType($1->varname);
      if(!t || t->typeId < TYPE_USERDEF || lookupClass($1->varname))
      {
        ClassTableEntry *c = lookupClass($1->varname);
        if(!c)
        {
          yyerror("Undefined type name");
          exit(1);
        }
        t = c->type;
        $$.type = TYPE_CLASS;
        $$.typeEntry = t;
        $$.ptrLevel = 0;
        currentTypeData = $$;
      }
      else
      {
        $$.type = TYPE_USERDEF;
        $$.typeEntry = t;
        $$.ptrLevel = 0;
        currentTypeData = $$;
      }
  }
  ;

ParamList:
  ParamList COMMA Param { $$ = AppendParam($1, $3); }
  | Param { $$ = $1; }
  ;

Param:
  Type ID { $$ = CreateParam($2->varname, $1.type, $1.typeEntry, $1.ptrLevel); }
  ;

FdefBlock: 
  FdefBlock Fdef 
  |
  ;

Fdef: 
  Type ID LPAREN ParamList RPAREN 
  {
    // set current function name
    current_function_name = $2->varname;

    if(lookupMethod(currentClassEntry, current_function_name))
    {
      selfClassEntry = currentClassEntry;
    }
    else
    {
      selfClassEntry = findClassForMethod($2->varname);
    }
    if(selfClassEntry)
    {
      InstallParamsToLSTMethod($4, selfClassEntry->type);
    }
    else
    {
      InstallParamsToLST($4);
    }
  }
  LBRACE LdeclBlock Body RBRACE 
  { 
    struct TypeInfo retType = $1;
    verifyFunctionSignature(Lookup($2->varname), &retType, $4);
    handleFdefPrint($2->varname, $9);

    struct Gsymbol* g = Lookup($2->varname);
    /*
    fprintf(interim_file, "F%d:\n", g->flabel);
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");

    locAlloc(interim_file);
    */

    codeGen($9, interim_file, g);

    // clear current function name
    current_function_name = NULL;

    selfClassEntry = NULL;

    // now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
  | Type ID LPAREN RPAREN 
  {
    // set current function name
    current_function_name = $2->varname;
    if(lookupMethod(currentClassEntry, current_function_name))
    {
      selfClassEntry = currentClassEntry;
    }
    else
    {
      selfClassEntry = findClassForMethod($2->varname);
    }
    if(selfClassEntry)
    {
      InstallParamsToLSTMethod(NULL, selfClassEntry->type); // to install self in LST
    }
    else
    {
      printf("Function %s is not a method\n", $2->varname);
      exit(1);
    }
    printf("code reached here\n");
  }
  LBRACE LdeclBlock Body RBRACE
  {
    struct TypeInfo retType = $1;
    Paramstruct *p = malloc(sizeof(Paramstruct));
    p->next = NULL;
    p->type = TYPE_NULL;
    verifyFunctionSignature(Lookup($2->varname), &retType, p);
    handleFdefNoArgsPrint($2->varname, $8); 

    struct Gsymbol* g = Lookup($2->varname);
    /*
    fprintf(interim_file, "F%d:\n", g->flabel);
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");

    locAlloc(interim_file);
    */

    codeGen($8, interim_file, g);

    // clear current function name
    current_function_name = NULL;

    selfClassEntry = NULL;

    // now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
  ;

LdeclBlock: 
  DECL LDecList ENDDECL 
  | DECL ENDDECL 
  | 
  ;

LDecList: 
  LDecList LDecl 
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
    handleMainPrint($8); 
    $$ = $8; 

    /*
    fprintf(interim_file, "MAIN:\n");
    moveStackPointer(interim_file);
    fprintf(interim_file, "BRKP\n");
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");
    
    locAlloc(interim_file);
    */

    struct Gsymbol* main_func = malloc(sizeof(struct Gsymbol));
    main_func->name = "MAIN";
    
    codeGen($$, interim_file, main_func);

    // clear current function name
    current_function_name = NULL;

    // now it is expected that all functions have a return statement(empty or not)
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
  | FreeStmt { $$ = $1; }
  | InitStmt { $$ = $1; }
  | DeleteStmt { $$ = $1; }
  ;

InputStmt:
  READ LPAREN ID RPAREN { $$ = makeReadNode(makeVarNode($3->varname)); }
  | READ LPAREN ID LSQBR E RSQBR RPAREN { $$ = makeReadNode(makeArrayNode($3, $5)); }
  | READ LPAREN MUL ID RPAREN               
  { 
    tnode* ptr_node = makeVarNode($4->varname);
    $$ = makeReadNode(makeDerefNode(ptr_node)); 
  }
  | READ LPAREN FieldAccess RPAREN
  {
    $$ = makeReadNode($3);
  }
  ;

OutputStmt: 
  WRITE LPAREN E RPAREN { $$ = makeWriteNode($3); }
  ;

FreeStmt:
  FREE_KW LPAREN LValue RPAREN
  {
    $$ = makeFreeNode($3);
  }
  ;

DeleteStmt:
  DELETE_KW LPAREN LValue RPAREN
  {
    $$ = makeDeleteNode($3);
  }
  ;

InitStmt:
  INITIALIZE LPAREN RPAREN
  {
    $$ = makeInitializeNode();
  }
  ;
AssgStmt:
  LValue ASSIGN E { $$ = makeAssignNode($1, $3); }
  | MUL ID ASSIGN E %prec UNARY 
  { 
    tnode* deref = makeDerefNode(makeVarNode($2->varname));
    $$ = makeAssignNode(deref, $4); 
  }
  | LValue ASSIGN ALLOC LPAREN RPAREN
  {
    $$ = makeAssignNode($1, makeAllocNode($1));
  }
  | LValue ASSIGN NEW_KW LPAREN ID RPAREN
  {
    $$ = makeAssignNode($1, makeNewNode($5->varname));
  }
  ;
  
LValue:
  ID
  {
    $$ = makeVarNode($1->varname);
  }
  | ID LSQBR E RSQBR
  {
    $$ = makeArrayNode($1, $3);
  }
  | FieldAccess
  ;

FieldAccess:
  ID DOT ID
  {
    tnode *base = makeVarNode($1->varname);
    $$ = makeFieldNode(base, $3->varname);
  }
  | FieldAccess DOT ID
  {
    $$ = makeFieldNode($1, $3->varname);
  }
  | SELF_KW DOT ID
  {
    if(lookupMethod(currentClassEntry, current_function_name))
    {
      selfClassEntry = currentClassEntry;
    }
    else
    {
      selfClassEntry = findClassForMethod(current_function_name);
    }
    if(!selfClassEntry) {
      printf("expr:lineNumber:%d\n", lineNumber); 
    }
    $$ = makeFieldNode(makeSelfNode(), $3->varname);
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
  | E AND E { $$ = makeBoolNode(NODE_AND, $1, $3); }
  | E OR E  { $$ = makeBoolNode(NODE_OR, $1, $3); }
  | NOT E   { $$ = makeNotNode($2); }
  | NUM { $$ = $1; }
  | STRING { $$ = $1; }
  | NULLVAL    { $$ = makeNullNode(); }
  | ID { $$ = makeVarNode($1->varname); }
  | ID LPAREN ArgList RPAREN { $$ = makeFuncallNode($1->varname, $3); }
  | ID LPAREN RPAREN { $$ = makeFuncallNode($1->varname, NULL); }
  | MUL E %prec UNARY { $$ = makeDerefNode($2); }
  | ADDRESS_OF ID %prec UNARY { $$ = makePointerNode(makeVarNode($2->varname)); }
  | LPAREN E RPAREN { $$ = $2; }
  | ID LSQBR E RSQBR { $$ = makeArrayNode($1, $3); }
  | FieldAccess
  | SELF_KW 
  {
    if(lookupMethod(currentClassEntry, current_function_name))
    {
      selfClassEntry = currentClassEntry;
    }
    else
    {
      selfClassEntry = findClassForMethod(current_function_name);
    }
    if(!selfClassEntry) {
      printf("expr:lineNumber:%d\n", lineNumber); 
    }
    $$ = makeSelfNode(); 
  }
  | SELF_KW DOT ID LPAREN ArgList RPAREN 
  {
    if(lookupMethod(currentClassEntry, current_function_name))
    {
      selfClassEntry = currentClassEntry;
    }
    else
    {
      selfClassEntry = findClassForMethod(current_function_name);
    }
    if(!selfClassEntry) {
      printf("expr:lineNumber:%d\n", lineNumber); 
    } 
    $$ = makeMethodCallNode(makeSelfNode(), $3->varname, $5); 
  }
  | SELF_KW DOT ID LPAREN RPAREN 
  { 
    if(lookupMethod(currentClassEntry, current_function_name))
    {
      selfClassEntry = currentClassEntry;
    }
    else
    {
      selfClassEntry = findClassForMethod(current_function_name);
    }
    if(!selfClassEntry) {
      printf("expr:lineNumber:%d\n", lineNumber); 
    }
    $$ = makeMethodCallNode(makeSelfNode(), $3->varname, NULL); 
  }
  | ID DOT ID LPAREN ArgList RPAREN { $$ = makeMethodCallNode(makeVarNode($1->varname), $3->varname, $5); }
  | ID DOT ID LPAREN RPAREN { $$ = makeMethodCallNode(makeVarNode($1->varname), $3->varname, NULL); } 
  | FieldAccess DOT ID LPAREN ArgList RPAREN 
  { 
    tnode *t = makeFieldNode($1->left, $1->varname);
    $$ = makeMethodCallNode(t, $3->varname, $5); 
  }
  | FieldAccess DOT ID LPAREN RPAREN 
  { 
    tnode *t = makeFieldNode($1->left, $1->varname);
    $$ = makeMethodCallNode(t, $3->varname, NULL); 
  } 
  
  ;

ArgList: 
  ArgList COMMA E { $$ = makeConnectorNode($1, $3); } 
  | E { $$ = $1; } 
  ;

%%

void yyerror(char *s) 
{
  fprintf(stderr, "Error at line %d: %s: %s\n", lineNumber, s, yytext);
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

  initTypeTable();
  initClassTable();
  initReg();
  fileinit(interim_file);
  
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
