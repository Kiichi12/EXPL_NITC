%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "tree.h"
    #include "register.h"
    #include "codegeneration.h"

    tnode *root;   /* The root of the expression tree */

    int yylex();
    void yyerror(char *s);
%}

%token NUM 
%token PLUS MINUS MUL DIV
%token LPAREN RPAREN
%token EOL

%left PLUS MINUS
%left MUL DIV


%%

input: 
    expr EOL {root = $1; return 0;}
    | /* empty */ {return 0;}
    ;

expr:
    expr PLUS expr {$$ = makeOperatorNode("+", $1, $3);}
    | expr MINUS expr {$$ = makeOperatorNode("-", $1, $3);}
    | expr MUL expr      { $$ = makeOperatorNode("*", $1, $3); }
    | expr DIV expr      { $$ = makeOperatorNode("/", $1, $3); }
    | LPAREN expr RPAREN { $$ = $2; }
    | NUM             { $$ = $1; }
    ;

%%

int main()
{
    printf("Enter an expression:\n");

    yyparse();  // Parse and build expression tree

    // Print prefix/postfix on console like before
    printf("\nPrefix order  : ");
    preorderTraversal(root);
    printf("\nPostfix order : ");
    postorderTraversal(root);
    printf("\n");

    // Open output file for target code
    FILE *target_file = fopen("target_file.xsm", "w");
    if (!target_file) {
        fprintf(stderr, "Error opening target_file.xsm for writing\n");
        return 1;
    }


    // Initialize register allocation
    initReg();

    // Generate code into target_file.xsm
    fileinit(target_file);
    int resultReg = codeGen(root, target_file);

    // Optional: print final result in memory or print out result
    // For example, store result into memory location 4096
    fprintf(target_file, "MOV [4096], R%d\n", resultReg);
    emitExit(target_file);

    // You could also free the final register if desired
    freeReg();

    fclose(target_file);

    // Free the tree
    deleteTree(root);

    return 0;
}

void yyerror(char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
