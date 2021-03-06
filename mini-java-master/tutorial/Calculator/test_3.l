%{
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
void yyerror(char *);
#include "y.tab.h"
%}

%%

[0-9]+ { yylval.val = atoi(yytext); return INTEGER;}
/* ����� ��������� ���������� ������� */
square  { return SQUARE;}
abs { return ABS;}
min { return MIN;}
max { return MAX;}
declare { return DECLARE;}
power { return POW;}
print { return PRINT; }
[a-z] { yylval.val = *yytext - 'a'; return VAR;} /* ����� ���������� ������ �������������, 
������� ����� ��������� ������� ������� ��� */
, { return *yytext;}
[+-/*()_=;] { return *yytext;} /* ������ � ����� �������� ���� �������� ��������� */
[ \t\n] ; /* ���������� ������� */
. {printf ("%s ", yytext); yyerror("Unknown symbol\n");}

%%

int yywrap(void)
{
  return 1;
}
