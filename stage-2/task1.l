
%{
    #include <stdio.h>
    #include "tree.h"
    #include <stdlib.h>

    #include "y.tab.h" 
%}

%%

begin   { return kBEGIN; }
end     { return kEND; }
read    { return READ; }
write   { return WRITE; }

[0-9]+  {
            yylval = makeNumNode(atoi(yytext));
            return NUM;
        }

[a-z]   {
            yylval = makeVarNode(strdup(yytext));
            return ID;
        }


[ \t\n]+   ;   



"+"         return PLUS;
"-"         return MINUS;
"*"         return MUL;
"/"         return DIV;

"("         return LPAREN;
")"         return RPAREN;

";"         return SEMICOLON;
"="         return ASSIGN;

.   {
        printf("unknown character %s p\n", yytext); 
        exit(1);
    }

%%

int yywrap()
{
    return 1;
}