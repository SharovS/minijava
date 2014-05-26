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
     _FOR = 264,
     _SYSTEMOP = 265,
     _SYSTEMOPWOLN = 266,
     _CLASS = 267,
     _MAIN = 268,
     _PUBLIC = 269,
     _STATIC = 270,
     _RETURN = 271,
     _EXTENDS = 272,
     _INT = 273,
     _BOOLEAN = 274,
     _VOID = 275,
     _STRING = 276,
     _TRUE = 277,
     _FALSE = 278,
     _THIS = 279,
     _NEW = 280,
     _LENGTH = 281,
     _POINT = 282,
     _SEMICOLUMN = 283,
     _STAR = 284,
     _ASSIGNMENT = 285,
     _WOW = 286,
     __COMMA = 287,
     _RL_BRACKET = 288,
     _RR_BRACKET = 289,
     _SL_BRACKET = 290,
     _SR_BRACKET = 291,
     _FL_BRACKET = 292,
     _FR_BRACKET = 293,
     _OPINC = 294,
     _OPDEC = 295,
     _OPPLUS = 296,
     _OPMINUS = 297,
     _OPMULT = 298,
     _OPDIV = 299,
     _OPAND = 300,
     _OPLESS = 301,
     NEG = 302
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 89 "C:\\Users\\Антон\\Documents\\GitHub\\minijava\\mini-java-master\\project\\syntax.txt"

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
#line 127 "syntax.hpp"
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
