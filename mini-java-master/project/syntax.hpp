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
     _SYSTEMOPWOLN = 265,
     _CLASS = 266,
     _MAIN = 267,
     _PUBLIC = 268,
     _STATIC = 269,
     _RETURN = 270,
     _EXTENDS = 271,
     _INT = 272,
     _BOOLEAN = 273,
     _VOID = 274,
     _STRING = 275,
     _TRUE = 276,
     _FALSE = 277,
     _THIS = 278,
     _NEW = 279,
     _LENGTH = 280,
     _POINT = 281,
     _SEMICOLUMN = 282,
     _STAR = 283,
     _ASSIGNMENT = 284,
     _WOW = 285,
     __COMMA = 286,
     _RL_BRACKET = 287,
     _RR_BRACKET = 288,
     _SL_BRACKET = 289,
     _SR_BRACKET = 290,
     _FL_BRACKET = 291,
     _FR_BRACKET = 292,
     _OPPLUS = 293,
     _OPMINUS = 294,
     _OPMULT = 295,
     _OPDIV = 296,
     _OPAND = 297,
     _OPLESS = 298,
     NEG = 299
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 84 "C:\\Users\\�����\\Desktop\\java\\minijava\\mini-java-master\\project\\syntax.txt"

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
#line 124 "syntax.hpp"
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