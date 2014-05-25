%{
#include <stdio.h>
#include <stdlib.h>
#include "types_1.h"
void yyerror(char *);
#include "y.tab.h"
VarTableRecord * var_pointer; /* указатель на запись в таблице перемнных */
%}

%%

[0-9]+ { yylval.val = atoi(yytext); return INTEGER;}
square  { return SQUARE;}
abs { return ABS;}
min { return MIN;}
max { return MAX;}
declare { return DECLARE;}
power { return POW;}
print { return PRINT; }
if { return IF; }
else  {return ELSE; }
then  {return THEN; }
for { return FOR; }
while { return WHILE; }
from  { return FROM; }
to { return TO; }
step { return STEP; }
do  { return DO; }
begin { return START; }
end { return END; }
and { return AND; }
or  {return OR; }
xor {return XOR; }
">="  { return GE; }
"=="  { return EQ; }
"<="  { return LE; }
"<" {return LT; }
">" {return GT; }
!=  {return NE; }
! {return NOT; }
true {yylval.val = 1; return BOOLEAN; }
false {yylval.val = 0; return BOOLEAN; }
[a-zA-Z_][a-zA-Z_0-9]* { /* сразу вносим запись в таблицу переменных */
                       var_pointer = findRecord(yytext); 
                       if (var_pointer) yylval.var_pointer = var_pointer;
                       else yylval.var_pointer = addRecord(yytext);                      
                       return VAR;
                       }
, { return *yytext;}
[+-/*()_=;] { return *yytext;}

[ \t\n] ;
. {printf ("%s ", yytext); yyerror("Unknown symbol\n");}

%%

int yywrap(void)
{
  return 1;
}
