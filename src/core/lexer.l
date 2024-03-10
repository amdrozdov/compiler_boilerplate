/* Include bison generated header */
%{
#include "parser.tab.h"
/*
*/
#define YYSTYPE char*
%}

/* TOKENS */
%%
"+" { return ADD; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"&&" { return AND; }
"||" { return OR; }
"abs" { return ABS; }
"print" { return PRINT; }
[0-9]+ { yylval = yytext; return NUMBER; }
"$"[0-9]+ { yylval = yytext; return PVAR; }
\n { return EOL; }
"//".* { /* Comment with 2 backslash*/ }
"(" { return OB; }
")" { return CB; }
"{" { return PO; }
"}" { return PC; }
"==" { return EQ; }
">" { return GT; }
"<" { return LT; }
">=" { return GTE; }
"<=" { return LTE; }
"," { return SEP; }
[ \t] {}

. { printf("Unknown character %c\n", *yytext); }
%%