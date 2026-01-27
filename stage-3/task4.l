
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

"if"             { return IF; }
"then"           { return THEN; }
"else"           { return ELSE; }
"endif"          { return ENDIF; }

"while"          { return WHILE; }
"do"             { return DO; }
"endwhile"       { return ENDWHILE; }
"break"          { return BREAK; }
"continue"       { return CONTINUE; }
"repeat"         { return REPEAT; }
"until"          { return UNTIL; }


"<="             { return LE; }
">="             { return GE; }
"=="             { return EQ; }
"!="             { return NE; }
"<"              { return LT; }
">"              { return GT; }

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