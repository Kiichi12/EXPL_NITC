%{
    #include <stdio.h>
    #include "tree.h"
    #include <stdlib.h>

    #include "y.tab.h" 
%}

%%

\r\n      |
\n        |
\r        return EOL; 

[0-9]+  {
            yylval = makeLeafNode(atoi(yytext));
            return NUM;
        }

[ \t]+   ;   



"+"         return PLUS;
"-"         return MINUS;
"*"         return MUL;
"/"         return DIV;

.   {
        printf("unknown character %s p\n", yytext); 
        exit(1);
    }

%%

int yywrap()
{
    return 1;
}