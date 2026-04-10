%{
    #include <stdio.h>
    #include <string.h>

    #include "tree.h"
    #include "typetable.h"

    #include "y.tab.h"

    int lineNumber = 1;

%}

%%

"begin"     { return kBEGIN; }
"end"       { return kEND; }
"read"      { return READ; }
"write"     { return WRITE; }
"return"    { 
                return RETURN; 
            }
"main"      { return MAIN; }

"decl"      { return DECL; }
"enddecl"   { return ENDDECL; }

"type"      { return TYPE_KW; }
"endtype"   { return ENDTYPE; }

"class"     { return CLASS; }
"endclass"  { return ENDCLASS; }
"new"       { return NEW_KW; }
"delete"    { return DELETE_KW; }
"self"      { return SELF_KW; }

"alloc"     { return ALLOC; }
"free"      { return FREE_KW; }
"initialize" { return INITIALIZE; }

"NULL"      { return NULLVAL; }

"int"       { return INT; }
"str"       { return STR; }

"if"        { return IF; }
"then"      { return THEN; }
"else"      { return ELSE; }
"endif"     { return ENDIF; }
"while"     { return WHILE; }
"do"        { return DO; }
"endwhile"  { return ENDWHILE; }
"break"     { return BREAK; }
"continue"  { return CONTINUE; }

[0-9]+  {
            yylval.node = makeNumNode(atoi(yytext));
            return NUM;
        }

\"[^\"]*\"  {
    yylval.node = makeStringConstNode(yytext);  
    return STRING;
}

[a-zA-Z][a-zA-Z0-9_]* {
    yylval.node = makeNewVarNode(strdup(yytext));
    return ID;
}

"<="    { return LE; }
">="    { return GE; }
"=="    { return EQ; }
"!="    { return NE; }
"<"     { return LT; }
">"     { return GT; }
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MUL; }
"/"     { return DIV; }

"&"     { return ADDRESS_OF; }
"."     { return DOT; }

"="     { return ASSIGN; }

";"     { return SEMICOLON; }
","     { return COMMA; }
"["     { return LSQBR; }
"]"     { return RSQBR; }
"("     { return LPAREN; }
")"     { return RPAREN; }
"{"     { return LBRACE; }
"}"     { return RBRACE; }

[ \t]+   ;  
\n  { lineNumber++; } 

.   { printf("Unknown: %s\n", yytext); exit(1); }

%%

int yywrap() 
{ 
    return 1; 
}