%{
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "types.h"
int yylex(void);
void yyerror(const char *);
/* функции, по коду переменной выдающие соответствующее сообщение об ошибке */ 
const char * unassignedVariable (int);
const char * undeclaredVariable (int);
const char * redeclaredVariable (int);

int myPower(int, int); 
void init_arrays(void);
int yydebug = 1; /* переменна€, отвечающа€ за выдачу отладочной информации */
int variablesValues[26]; /* массив значений переменных */
int declaredVariables[26]; /* объ€влены ли переменные */
int assignedVariables[26]; /* присвоено ли переменной значение */
char error_message[1000];
%}
 /* значение либо целое число (результат вычислений), либо массив чисел. Ёто нужно дл€ функции с переменным числом аргументов */
%union {
  int val;
  pair array;
}

%token <val> INTEGER SQUARE MIN MAX ABS POW VAR PRINT DECLARE
%left '+' '-'
%left '*' '/'
%left UMINUS
%type <val> expr
%type <val> func_expr
%type <val> SQUARE_expr
%type <val> ABS_expr
%type <val> EXTR_expr
%type <val> POW_expr
%type <array> expr_sequence /* последовательность  выражений произвольной длины */

%%

program : /* empty */
  | program line
  
line : assignment ';'
  | declaration ';'
  | print ';'
  
assignment : VAR '=' expr {
                            //printf("d\n", $1);
                            if (declaredVariables[$1])
                            {
                              assignedVariables[$1] = 1; 
                              variablesValues[$1] = $3;
                            }
                            else
                            {
                              yyerror(undeclaredVariable($1));
                            }
                           }

declaration : DECLARE VAR {
                            if(declaredVariables[$2] == 0) { declaredVariables[$2] = 1; }
                            else { yyerror(redeclaredVariable($2)); }
                          }
  | DECLARE VAR '=' expr {
                            if(declaredVariables[$2] == 0) { declaredVariables[$2] = 1; }
                            else { yyerror(redeclaredVariable($2)); };
                            assignedVariables[$2] = 1; 
                            variablesValues[$2] = $4;
                          }
print : PRINT expr {printf("%d\n", $2);}

expr : INTEGER {$$ = $1;}
  | VAR {
        if(assignedVariables[$1]) { $$ = variablesValues[$1];}
        else {yyerror(unassignedVariable($1));}
        }        
  | expr '+' expr {$$ = $1 + $3; printf("%d %d ", $1, $3);}
  | expr '-' expr {$$ = $1 - $3;}
  | expr '*' expr {$$ = $1 * $3;}
  | expr '/' expr {
                  if ($3 != 0) {$$ = $1 / $3;}
                  else {yyerror("Zero division\n");}
                  }
  | '(' expr ')' {$$ = $2;}
  | '-' expr %prec UMINUS {$$ = -$2;}
  | func_expr {$$ = $1;}
  
func_expr : SQUARE_expr {$$ = $1;}
  | ABS_expr {$$ = $1;}
  | EXTR_expr {$$ = $1;}
  | POW_expr {$$ = $1;} 
  
SQUARE_expr : SQUARE '(' expr ')' {$$ = $3 * $3;}
ABS_expr : ABS '(' expr ')' {$$ = abs($3);}
EXTR_expr : MIN '(' expr_sequence ')' {$$ = findMin($3.sequence, $3.sequence_length);}
  | MAX '(' expr_sequence ')' {$$ = findMax($3.sequence, $3.sequence_length);}
POW_expr : POW '(' expr ',' expr ')' {$$ = myPower($3, $5);}  

expr_sequence : expr {$$.sequence_length = 1; ($$.sequence)[0] = $1;}
  | expr_sequence ',' expr {
                            $$.sequence_length = $1.sequence_length + 1;
                            for (int i = 0; i < $1.sequence_length; ++i)
                            {
                              ($$.sequence)[i] = ($1.sequence)[i];
                            }
                            ($$.sequence)[$1.sequence_length] = $3;
                           }
%%

int myPower (int base, int degree) /* быстрое возведение в степень */
{
  int result = 1;
  if (degree > 0)
  {
    result = myPower (base, degree / 2);
    result = result * result;
  }
  if (degree % 2 == 1)
  {
    result *= base;
  }
  return result;
}
      
const char* undeclaredVariable(int var_code)
{
  strcpy (error_message, "Variable ");
  char temp_string[1];
  temp_string[0] = (char) 'a' + var_code;
  strcat (error_message, temp_string);
  strcat (error_message, "being used without being declared");
  return error_message;
}

const char* unassignedVariable(int var_code)
{
  strcpy (error_message, "Variable ");
  char temp_string[1];
  temp_string[0] = (char) 'a' + var_code;
  strcat (error_message, temp_string);
  strcat (error_message, "being used without being assigned");
  return error_message;
}

const char* redeclaredVariable(int var_code)
{
  strcpy (error_message, "Variable ");
  char temp_string[1];
  temp_string[0] = (char) 'a' + var_code;
  strcat (error_message, temp_string);
  strcat (error_message, "being already declared");
  return error_message;
}

int findMax (const int* numbers, int length)
{
  int result = numbers[0];
  for (int i = 1; i < length; ++i)
  {
    result = numbers[i] > result ? numbers[i] : result;
  }
  return result;
}

int findMin (const int* numbers, int length)
{
  int result = numbers[0];
  for (int i = 1; i < length; ++i)
  {
    result = numbers[i] < result ? numbers[i] : result;
  }
  return result;
}

void yyerror(const char *s) 
{
  fprintf(stderr, "%s\n", s);
}

void init_arrays(void) /* вначале все переменные не объ€влены */
{
  for (int i = 0; i < 26; ++i)
  {
    declaredVariables[i] = 0;
    assignedVariables[i] = 0;
  }
}

int main(void)
{
  init_arrays();
  yyparse();
  return 0;
}