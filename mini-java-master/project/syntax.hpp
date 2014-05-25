/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SYNTAX_HPP_INCLUDED
# define YY_YY_SYNTAX_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     _ID = 258,
     _NUM = 259,
     _STR = 260,
     _IF = 261,
     _ELSE = 262,
     _WHILE = 263,
     _SYSTEMOP = 264,
     _CLASS = 265,
     _MAIN = 266,
     _PUBLIC = 267,
     _STATIC = 268,
     _RETURN = 269,
     _EXTENDS = 270,
     _INT = 271,
     _BOOLEAN = 272,
     _VOID = 273,
     _STRING = 274,
     _TRUE = 275,
     _FALSE = 276,
     _THIS = 277,
     _NEW = 278,
     _LENGTH = 279,
     _POINT = 280,
     _SEMICOLUMN = 281,
     _STAR = 282,
     _ASSIGNMENT = 283,
     _WOW = 284,
     __COMMA = 285,
     _RL_BRACKET = 286,
     _RR_BRACKET = 287,
     _SL_BRACKET = 288,
     _SR_BRACKET = 289,
     _FL_BRACKET = 290,
     _FR_BRACKET = 291,
     _OPPLUS = 292,
     _OPMINUS = 293,
     _OPMULT = 294,
     _OPDIV = 295,
     _OPAND = 296,
     _OPLESS = 297,
     NEG = 298
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 83 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"

 int IntV;
 char* StringV;
 CBinop Binop;
 //CT IdType;
 char* SymbolTable;
 IProgram* Program;
 IMainClass* MainClass;
 IClassDecl* ClassDecl;
 IClassDeclList* ClassDeclList;
 IVarDecl* VarDecl;
 IVarDeclList* VarDeclList;
 IMethodDecl* MethodDecl;
 IMethodDeclList* MethodDeclList;
 IFormalList* FormalList;
 IType* Type;    
 IStm* Stm;
 IStmList* StmList;
 IExp* Exp ;
 IExpList* ExpList ;


/* Line 2058 of yacc.c  */
#line 123 "syntax.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;
extern YYLTYPE yylloc;
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_SYNTAX_HPP_INCLUDED  */
