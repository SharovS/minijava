%{
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include "types_1.h"

MyTreeNode * operNode (int, int, ...); 
MyTreeNode * conNode (int);
MyTreeNode * varNode (VarTableRecord*);
int execute (MyTreeNode *);
//Result iResult (int);
void deleteSubtree (MyTreeNode *);

int yylex(void);
void yyerror(const char *);
int yydebug = 1;

const char * unassignedVariable (const char *);
const char * undeclaredVariable (const char *);
const char * redeclaredVariable (const char *);
const char * wrongTypeAssignment (char);
const char* getType (char type_code, char* type);
int myPower(int, int);

void init_table(void);
void remove_table(void);

char error_message[1000];
VarTable variables_table; /* таблица переменных (на самом деле список) */
Pair for_sequence; /* для того случая, когда аргумент функции есть последовательность выражений. */
%}

%union {
  int val; /* для констант */
  VarTableRecord * var_pointer; /* для переменных */
  MyTreeNode * node_pointer; /* для всего остального */ 
}

%token <val> INTEGER BOOLEAN
%token <var_pointer> VAR
%token WHILE IF PRINT FOR DO THEN STEP TO FROM DECLARE
%token SQUARE MAX MIN ABS POW
%nonassoc IFTHEN
%nonassoc ELSE
%token START END

%left OR XOR
%left AND
%left GE LE GT LT EQ NE
%left NOT
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <node_pointer> stmt stmt_list assignment declaration print expr logic_expr func_expr
%type <node_pointer> expr_sequence

%%

program : /* empty */
  | program stmt {execute($2); deleteSubtree($2);}
  
stmt : assignment ';' {$$ = $1;}
  | declaration ';' {$$ = $1;}
  | print ';' { $$ = $1;}
  | WHILE logic_expr DO stmt  {$$ = operNode(WHILE, 2, $2, $4);}
  | IF logic_expr THEN stmt %prec IFTHEN /* приоритет такой же, как у IFTHEN */{ $$ = operNode(IF, 2, $2, $4); }
  | IF logic_expr THEN stmt ELSE stmt {$$ = operNode (IF, 3, $2, $4, $6); }
  | FOR VAR {
                                                if (!$2->is_declared)
                                                {
                                                  yyerror(undeclaredVariable($2->name));
                                                }
                                                else
                                                {
                                                  $2->is_assigned = 1;
                                                }
            } 
            FROM expr TO expr STEP expr DO stmt {
                                                  if($2->is_declared)
                                                  {
                                                    MyTreeNode * var_node = varNode($2);
                                                    $$ = operNode(FOR, 5, var_node, $5, $7, $9, $11);
                                                  }
                                                } 
                                                 | START stmt_list END {$$ = $2; } 
  
assignment : VAR '=' expr {
                            if ($1->is_declared)
                            {
                              $1->is_assigned = 1;
                              MyTreeNode * var_node = varNode($1);
                              $$ = operNode('=', 2, var_node, $3);
                            }
                            else
                            {
                              yyerror(undeclaredVariable($1->name));
                            }
                          }                              

declaration : DECLARE VAR {
                            if ($2->is_declared)
                            {
                              yyerror(redeclaredVariable($2->name));
                            }
                            else
                            {
                              MyTreeNode * var_node = varNode($2);
                              $2->is_declared = 1;
                              $2->type = 'i';
                              $$ = operNode(DECLARE, 1, var_node);
                            }
                          }
  | DECLARE VAR '=' expr  {
                            if ($2->is_declared)
                            {
                              yyerror(redeclaredVariable($2->name));
                            }
                            else
                            {
                              $2->is_declared = 1;
                              $2->is_assigned = 1;
                              $2->type = 'i';
                              MyTreeNode * var_node = varNode($2);
                              $$ = operNode('=', 2, var_node, $4);
                            }
                          }
print : PRINT expr {
                   $$ = operNode(PRINT, 1, $2);
                   }

expr : INTEGER {
               $$ = conNode($1);
               }
  | VAR {
        if ($1->is_declared)
        {
          if ($1->is_assigned)
          {
            $$ = varNode($1);
          }
          else
          {
            yyerror(unassignedVariable($1->name));
          }
        }
        else
        {
          yyerror(undeclaredVariable($1->name));
        }
       }       
  | expr '+' expr {$$ = operNode('+', 2, $1, $3);}
  | expr '-' expr {$$ = operNode('-', 2, $1, $3);}
  | expr '*' expr {$$ = operNode('*', 2, $1, $3);}
  | expr '/' expr {$$ = operNode('/', 2, $1, $3);}                  
  | '(' expr ')' {$$ = $2;}
  | '-' expr %prec UMINUS {$$ = operNode(UMINUS, 1, $2);}
  | func_expr {$$ = $1;}
  
func_expr : SQUARE '(' expr ')' {$$ = operNode(SQUARE, 1, $3);}
  | ABS '(' expr ')' {$$ = operNode(ABS, 1, $3);}
  | MIN '(' expr_sequence ')' {$$ = operNode(MIN, 1, $3);}
  | MAX '(' expr_sequence ')' {$$ = operNode(MAX, 1, $3);}
  | POW '(' expr ',' expr ')' {$$ = operNode(POW, 2, $3, $5);}  

expr_sequence : expr { $$ = operNode(',', 1, $1); }
  | expr_sequence ',' expr { $$ = operNode(',', 2, $1, $3); }
  
logic_expr : BOOLEAN {$$ = conNode($1);}
  | expr EQ expr {$$ = operNode(EQ, 2, $1, $3);}
  | expr NE expr {$$ = operNode(NE, 2, $1, $3);}
  | expr GT expr {$$ = operNode(GT, 2, $1, $3);}
  | expr GE expr {$$ = operNode(GE, 2, $1, $3);}
  | expr LT expr {$$ = operNode(LT, 2, $1, $3);}
  | expr LE expr {$$ = operNode(LE, 2, $1, $3);}
  | expr OR expr {$$ = operNode(OR, 2, $1, $3);}
  | expr XOR expr {$$ = operNode(XOR, 2, $1, $3);}
  | expr AND expr {$$ = operNode(AND, 2, $1, $3);}
  | logic_expr EQ logic_expr {$$ = operNode(EQ, 2, $1, $3);}
  | logic_expr NE logic_expr {$$ = operNode(NE, 2, $1, $3);}
  | logic_expr GT logic_expr {$$ = operNode(GT, 2, $1, $3);}
  | logic_expr GE logic_expr {$$ = operNode(GE, 2, $1, $3);}
  | logic_expr LT logic_expr {$$ = operNode(LT, 2, $1, $3);}
  | logic_expr LE logic_expr {$$ = operNode(LE, 2, $1, $3);}
  | logic_expr OR logic_expr {$$ = operNode(OR, 2, $1, $3);}
  | logic_expr XOR logic_expr {$$ = operNode(XOR, 2, $1, $3);}
  | logic_expr AND logic_expr {$$ = operNode(AND, 2, $1, $3);}
  | NOT logic_expr {$$ = operNode(NOT, 1, $2);}
  | '(' logic_expr ')' {$$ = $2; }
  
stmt_list : stmt {$$ = $1;}
  | stmt_list stmt {$$ = operNode(';', 2, $1, $2);}
  
%%

MyTreeNode * conNode (int value) /* создаём узел для константы */
{
  MyTreeNode * node_pointer = malloc(sizeof(MyTreeNode));
  node_pointer->type = con;
  (node_pointer->value).con_value = value;
  return node_pointer;
}

MyTreeNode * varNode (VarTableRecord * var_record_pointer) /* создаём узел для переменной */
{
  MyTreeNode * node_pointer = malloc(sizeof(MyTreeNode));
  node_pointer->type = var;
  (node_pointer->value).var_pointer = var_record_pointer;
  return node_pointer;
}

MyTreeNode * operNode (int operation, int operands_number, ...) /* создаём узел для функционального символа. 
                                                                   Число операндов может быть разным, поэтому число аргументов переменно */
{
  va_list operands;
  MyTreeNode * node_pointer = malloc(sizeof(MyTreeNode));
  node_pointer->type = oper;
  ((node_pointer->value).oper_node).lexem_name = operation;
  ((node_pointer->value).oper_node).operands_number = operands_number;
  
  MyTreeNode** children = malloc(operands_number * sizeof(MyTreeNode*));
  va_start(operands, operands_number);
  for (int i = 0; i < operands_number; ++i)
  {
    children[i] = va_arg(operands, MyTreeNode*);
  }
  ((node_pointer->value).oper_node).operands = children;
  return node_pointer;
}

int execute (MyTreeNode * root) /* выполнить фрагмент программы, соответствующий поддереву с корнем в данном узле */
{
  if (!root) return 0;
  Pair* sequence_pointer;
  VarTableRecord * var_pointer;
  int counter, arg;
  switch(root->type)
  {
    case con:
      return root->value.con_value;
    case var:
      return ((root->value).var_pointer)->value.i_value; 
    case oper:
      switch ((root->value.oper_node).lexem_name)
      {
        case WHILE:
          while (execute((root->value.oper_node).operands[0]))
          {
            execute((root->value.oper_node).operands[1]);
          }
          return 0;
        case FOR:
          counter = execute((root->value.oper_node).operands[1]);
          (((root->value.oper_node).operands[0])->value.var_pointer)->value.i_value = counter;
          while (counter <= execute(((root->value).oper_node).operands[2]))
          {
            execute(((root->value).oper_node).operands[4]);
            counter += execute(((root->value).oper_node).operands[3]);
            (((root->value.oper_node).operands[0])->value.var_pointer)->value.i_value = counter;
          }
          return 0;
        case IF:
          if (execute(((root->value).oper_node).operands[0]))
          {
            execute(((root->value).oper_node).operands[1]);
            return 0;
          }
          else
          {
            if (((root->value).oper_node).operands_number == 3)
            {
              execute(((root->value).oper_node).operands[2]);
            }
            return 0;
          }
        case PRINT:
          printf("%d\n", execute(((root->value).oper_node).operands[0]));
          return 0;
        case DECLARE:
          return 0;
        case '=':
          var_pointer = (((root->value).oper_node).operands[0])->value.var_pointer;
          arg = execute(((root->value).oper_node).operands[1]);
          return (var_pointer->value.i_value = arg);
        case ';':
          execute(((root->value).oper_node).operands[0]);
          return execute(((root->value).oper_node).operands[1]);
        
        case ',':          
          if (((root->value).oper_node).operands_number == 1)
          {
            for_sequence.sequence_length = 1;
            for_sequence.sequence[0] = execute(((root->value).oper_node).operands[0]);
          }
          else
          {
            ++for_sequence.sequence_length;
            for_sequence.sequence[for_sequence.sequence_length - 1] = 
              execute(((root->value).oper_node).operands[1]);
          }
          return 0;
        
       case UMINUS:
          return (-execute(((root->value).oper_node).operands[0]));
       
       case NOT:
          return (1 - execute(((root->value).oper_node).operands[0]));
       
       case '+':
          return (execute(((root->value).oper_node).operands[0]) +
                         execute(((root->value).oper_node).operands[1]));
        
       case '-':
          return (execute(((root->value).oper_node).operands[0]) -
                         execute(((root->value).oper_node).operands[1]));
                         
       case '*':
          return (execute(((root->value).oper_node).operands[0]) *
                         execute(((root->value).oper_node).operands[1]));
                         
       case '/':
          arg = execute(((root->value).oper_node).operands[1]);
          if (arg != 0)
          {
            return (execute(((root->value).oper_node).operands[0]) / arg);
          }
          else
          {
            yyerror("Zero division\n");
            return 0;
          }
          
       case LT:
          return (execute(((root->value).oper_node).operands[0]) <
                         execute(((root->value).oper_node).operands[1]));
          
       case LE:
          return (execute(((root->value).oper_node).operands[0]) <=
                         execute(((root->value).oper_node).operands[1]));
       
       case GT:
          return (execute(((root->value).oper_node).operands[0]) >
                         execute(((root->value).oper_node).operands[1]));
       
       case GE:
          return (execute(((root->value).oper_node).operands[0]) >=
                         execute(((root->value).oper_node).operands[1]));
       
       case EQ:
          return (execute(((root->value).oper_node).operands[0]) ==
                         execute(((root->value).oper_node).operands[1]));
       
       case NE:
          return (execute(((root->value).oper_node).operands[0]) !=
                         execute(((root->value).oper_node).operands[1]));
                          
       case OR:
          return (execute(((root->value).oper_node).operands[0]) ||
                         execute(((root->value).oper_node).operands[1]));
       
       case AND:
          return (execute(((root->value).oper_node).operands[0]) &&
                         execute(((root->value).oper_node).operands[1]));
       
       case SQUARE:
          arg = execute((root->value).oper_node.operands[0]);
          return arg * arg;
          
       case ABS:
          return abs(execute(((root->value).oper_node).operands[0]));
       
       case POW:
          return myPower(execute(((root->value).oper_node).operands[0]),
                         execute(((root->value).oper_node).operands[1]));
       case MAX:
          execute(((root->value).oper_node).operands[0]);
          return findMax(for_sequence.sequence, for_sequence.sequence_length);
      case MIN:
          execute(((root->value).oper_node).operands[0]);
          return findMin(for_sequence.sequence, for_sequence.sequence_length);          
      }
  }
return 0;
}

void deleteSubtree(MyTreeNode * root)
{
  if(!root) return;
  if(root->type == oper)
  {
    for(int i = 0; i < ((root->value).oper_node).operands_number; i++)
    {
      deleteSubtree(((root->value).oper_node).operands[i]);
    }
    free(((root->value).oper_node).operands);
  }
  free(root);
}                                 
                                 
int myPower (int base, int degree)
{
  if (degree < 0)
  {
    yyerror("Wrong power argument\n");
    return 0;
  }
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
      
const char* undeclaredVariable(const char * var_code)
{
  strcpy (error_message, "Variable ");
  strcat (error_message, var_code);
  strcat (error_message, " being used without being declared");
  return error_message;
}

const char* unassignedVariable(const char * var_code)
{
  strcpy (error_message, "Variable ");
  strcat (error_message, var_code);
  strcat (error_message, "being used without being assigned");
  return error_message;
}

const char* redeclaredVariable(const char * var_code)
{
  strcpy (error_message, "Variable ");
  strcat (error_message, var_code);
  strcat (error_message, " being already declared");
  return error_message;
}

const char* wrongTypeAssignment(char type_code)
{
  char type[10];
  getType(type_code, type);
  strcpy (error_message, "Integer cannot be assigned to ");
  strcat (error_message, type);
  strcat (error_message, " variable");
  return error_message;
}

const char* getType (char type_code, char* type)
{
  if (type_code == 'i')
  {
    strcpy(type, "int");    
  }
  else
  {
    strcpy(type, "NO_TYPE");
  }
  return type;
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

void init_table(void)
{
  variables_table.head = NULL;
}

VarTableRecord* addRecord (const char * name) /* добавление записи в таблицу переменных */
{
  VarTableNode* new_head_node = malloc(sizeof(VarTableNode));
  VarTableRecord  record;
  strcpy(record.name, name);
  record.is_assigned = 0;
  record.is_declared = 0;
  record.type = 0;
  new_head_node->record = record;
  new_head_node->next = variables_table.head;
  variables_table.head = new_head_node;
  return &(new_head_node->record); 
}

VarTableRecord * findRecord (const char * var_name) /* поиск записи в таблице переменных */
{
  for (VarTableNode * node = variables_table.head; node != NULL; node = node->next)
  {
    if (!strcmp((node->record).name, var_name))
    {
      return &(node->record);
    }
  }
  return NULL;
}

void remove_table(void)
{
  while (variables_table.head != NULL)
  {
    VarTableNode* current_node = variables_table.head;
    variables_table.head = current_node->next;
    free(current_node);
  }
}

int main(void)
{
  init_table();
  yyparse();
  remove_table();
  return 0;
}

