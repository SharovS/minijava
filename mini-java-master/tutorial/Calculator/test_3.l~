%{
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
void yyerror(char *);
#include "y.tab.h"
%}

%%

[0-9]+ { yylval.val = atoi(yytext); return INTEGER;}
/* ¬ведЄм поддержку нескольких функций */
square  { return SQUARE;}
abs { return ABS;}
min { return MIN;}
max { return MAX;}
declare { return DECLARE;}
power { return POW;}
print { return PRINT; }
[a-z] { yylval.val = *yytext - 'a'; return VAR;} /* »мена переменных только однобуквенные, 
поэтому можно значением лексемы считать им€ */
, { return *yytext;}
[+-/*()_=;] { return *yytext;} /* скобки и знаки операций тоже €вл€ютс€ лексемами */
[ \t\n] ; /* игнорируем пробелы */
. {printf ("%s ", yytext); yyerror("Unknown symbol\n");}

%%

int yywrap(void)
{
  return 1;
}
