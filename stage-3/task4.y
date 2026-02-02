%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "tree.h"
    #include "register.h"
    #include "labels.h"
    #include "codegeneration.h"

    void printAST(struct tnode* t, int level);

    int evaluate(struct tnode *root); // to return the value of all variables after code completion
    int symtable[26];  // for evaluate function

    tnode *root;   /* The root of the AST */

    FILE *target_file;
    extern FILE *yyin;

    int yylex();
    void yyerror(char *s);
%}

%token NUM ID
%token PLUS MINUS MUL DIV
%token LT LE GT GE EQ NE
%token LPAREN RPAREN ASSIGN SEMICOLON
%token kBEGIN kEND
%token WRITE READ
%token IF THEN ELSE WHILE ENDIF ENDWHILE DO REPEAT UNTIL
%token BREAK CONTINUE


%left PLUS MINUS
%left MUL DIV

%%

Program:
      kBEGIN Slist kEND   {
                            $$ = $2;
                            root = $$;
                        }
    | kBEGIN kEND         { $$ = NULL; }
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
    | BreakStmt           { $$ = $1; }
    | ContinueStmt        { $$ = $1; }
    | DoWhileStmt         { $$ = $1; }
    | RepeatUntilStmt     { $$ = $1; }
    ;


InputStmt:
    READ LPAREN ID RPAREN { $$ = makeReadNode($3); }
    ;

OutputStmt:
    WRITE LPAREN E RPAREN { $$ = makeWriteNode($3); }
    ;

AssgStmt:
    ID ASSIGN E           { $$ = makeAssignNode($1, $3); }
    ;

IfStmt:
    IF LPAREN E RPAREN THEN Slist ELSE Slist ENDIF
        { $$ = makeIfElseNode($3, $6, $8); }
    | IF LPAREN E RPAREN THEN Slist ENDIF
        { $$ = makeIfNode($3, $6); }
    ;

WhileStmt:
    WHILE LPAREN E RPAREN DO Slist ENDWHILE
        { $$ = makeWhileNode($3, $6); }
    ;

BreakStmt:
    BREAK { $$ = makeBreakNode(); }
    ;

ContinueStmt:
    CONTINUE { $$ = makeContinueNode(); }
    ;

DoWhileStmt:
    DO Slist WHILE LPAREN E RPAREN
        { $$ = makeDoWhileNode($2, $5); }
    ;

RepeatUntilStmt:
    REPEAT Slist UNTIL LPAREN E RPAREN
        { $$ = makeRepeatUntilNode($2, $5); }
    ;


E:
    E PLUS E {
        if (($1->type != INT) || ($3->type != INT)) {
            perror("type mismatch");
            exit(1);
        } else {
            $$ = makeArithNode(NODE_PLUS, $1, $3);
        }
    }
    | E MINUS E {
        if (($1->type != INT) || ($3->type != INT)) {
            perror("type mismatch");
            exit(1);
        } else {
            $$ = makeArithNode(NODE_MINUS, $1, $3);
        }
    }
    | E MUL E {
        if (($1->type != INT) || ($3->type != INT)) {
            perror("type mismatch");
            exit(1);
        } else {
            $$ = makeArithNode(NODE_MUL, $1, $3);
        }
    }
    | E DIV E {
        if (($1->type != INT) || ($3->type != INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeArithNode(NODE_DIV, $1, $3);
        }
    }
    | LPAREN E RPAREN { $$ = $2; }

    | E LT E {
        if (($1->type != INT) || ($3->type != INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_LT, $1, $3);
        }
    }
    | E LE E {
        if (($1->type != INT) || ($3->type != INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_LE, $1, $3);
        }
    }
    | E GT E {
        if (($1->type != INT) || ($3->type != INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_GT, $1, $3);
        }
    }
    | E GE E {
        if (($1->type != INT) || ($3->type != INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_GE, $1, $3);
        }
    }
    | E EQ E {
        if (($1->type != INT) || ($3->type != INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_EQ, $1, $3);
        }
    }
    | E NE E {
        if (($1->type != INT) || ($3->type != INT)) {
            perror("ERROR: type mismatch");
            exit(1);
        } else {
            $$ = makeBoolNode(NODE_NE, $1, $3);
        }
    }
    | NUM { $$ = $1; }
    | ID  { $$ = $1; }
    ;

%%

int main(int argc, char **argv)
{
    FILE *source_file;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source file>\n", argv[0]);
        return 1;
    }

    source_file = fopen(argv[1], "r");
    if (!source_file) {
        perror("fopen");
        return 1;
    }

    yyin = source_file;
    yyparse(); // Parse and build AST
    fclose(source_file);  

    printAST(root, 0);

    //int result = evaluate(root);
    //for (int i = 0; i < 26; i++) {
    //    printf("%c:%d\n", 'a' + i, symtable[i]);
    //}

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

int evaluate(struct tnode *root)
{
    if (root == NULL) return 0;

    switch (root->nodetype) {

        case NODE_NUM:
            return root->val;

        case NODE_ID:
            return symtable[root->varname[0] - 'a'];

        case NODE_PLUS:
            return evaluate(root->left) + evaluate(root->right);

        case NODE_MINUS:
            return evaluate(root->left) - evaluate(root->right);

        case NODE_MUL:
            return evaluate(root->left) * evaluate(root->right);

        case NODE_DIV: {
            int r = evaluate(root->right);
            if (r == 0) {
                printf("Error: division by zero\n");
                exit(1);
            }
            return evaluate(root->left) / r;
        }

        case NODE_LT:
            return evaluate(root->left) < evaluate(root->right);

        case NODE_GT:
            return evaluate(root->left) > evaluate(root->right);

        case NODE_LE:
            return evaluate(root->left) <= evaluate(root->right);

        case NODE_GE:
            return evaluate(root->left) >= evaluate(root->right);

        case NODE_EQ:
            return evaluate(root->left) == evaluate(root->right);

        case NODE_NE:
            return evaluate(root->left) != evaluate(root->right);

        case NODE_ASSIGN: {
            int val = evaluate(root->right);
            symtable[root->varname[0] - 'a'] = val;
            return val;
        }

        case NODE_READ: {
            int v;
            printf("Enter value for %s: ", root->left->varname);
            scanf("%d", &v);
            symtable[root->left->varname[0] - 'a'] = v;
            return v;
        }

        case NODE_WRITE: {
            int v = evaluate(root->left);
            printf("%d\n", v);
            return v;
        }

        case NODE_CONNECTOR:
            evaluate(root->left);
            evaluate(root->right);
            return 0;

        case NODE_IF:
            if (evaluate(root->left))
                evaluate(root->right);
            return 0;

        case NODE_IFELSE:
            if (evaluate(root->left))
                evaluate(root->right->left);
            else
                evaluate(root->right->right);
            return 0;

        case NODE_WHILE:
            while (evaluate(root->left))
                evaluate(root->right);
            return 0;
    }

    return 0;
}

const char* nodeTypeToString(int nodetype)
{
    switch (nodetype) {
        case NODE_NUM:        return "NUM";
        case NODE_ID:         return "ID";

        case NODE_PLUS:       return "PLUS";
        case NODE_MINUS:      return "MINUS";
        case NODE_MUL:        return "MUL";
        case NODE_DIV:        return "DIV";

        case NODE_ASSIGN:     return "ASSIGN";
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

void yyerror(char *s)
{
    fprintf(stderr, "Parse error: %s\n", s);
}
