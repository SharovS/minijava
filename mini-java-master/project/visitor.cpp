# pragma once
# include "stdio.h"
#include <interface.h>
#include <visitor.h>

void 
PrettyPrintVisitor::Visit(const CProgram& p)//MainClass ClassDeclList
{
	p.GetMainClass()->Accept(this);
	p.GetClassDeclList()->Accept(this);
	
}

void
PrettyPrintVisitor::Visit(const CMainClass& p)//class id { public static void main ( String [] id ) { Statement }}
{
	printf("class %s { public static Void main ( String [] %s ) { ", p.GetIdFirst(), p.GetIDSecond());
	p.GetStm()->Accept(this);
	printf("}}\n");
}

void
PrettyPrintVisitor::Visit(const CClassDecl& p)//class id { VarDeclList MethodDeclList }
{
	printf("class %s { ", p.GetId());
	p.GetVarDeclList()->Accept(this);
	p.GetMethodDeclList()->Accept(this);
	printf("} ");
}
void
PrettyPrintVisitor::Visit(const CExClassDecl& p)//class id extends id { VarDeclList MethodDeclList }
{
	printf("class %s extends %s { ", p.GetId(), p.GetIDExtend());
	p.GetVarDeclList()->Accept(this);
	p.GetMethodDeclList()->Accept(this);
	printf("}\n");
}
void
PrettyPrintVisitor::Visit(const CVarDecl& p)//Type id
{
	printf("%s %s \n", p.GetType(), p.GetId());
}

void 
PrettyPrintVisitor::Visit(const CMethodDecl& p)//public Type id ( FormalList ) { VarDecl* Statement* return Exp ;}
{
	printf("public %s %s ( ", p.GetType(), p.GetId());
	p.GetFormalList()->Accept(this);
	printf(") { ");
	p.GetVarDeclList()->Accept(this);
	p.GetStmList()->Accept(this);
	printf("return ");
	p.GetExp()->Accept(this);
	printf(";}\n");
}

void
PrettyPrintVisitor::Visit(const CCompStm& p)//{ Statement* }
{
	printf("{");
	p.GetStmList()->Accept(this);
	printf("} ");
}

void
PrettyPrintVisitor::Visit(const CIfStm& p)//if ( Exp ) Statement else Statement
{
	printf("if ( ");
	p.GetExp()->Accept(this);
	p.GetStmFirst()->Accept(this);
	printf("else ");
	p.GetlStmSecond()->Accept(this);
}

void
PrettyPrintVisitor::Visit(const CWhStm& p)//while ( Exp ) Statement
{
	printf("while ( ");
	p.GetExp()->Accept(this);
	printf(") ");
	p.GetStm()->Accept(this);
}

void
PrettyPrintVisitor::Visit(const CSOPStm& p)//System.out.println ( Exp ) ;
{
	printf("System.out.println ( ");
	p.GetExp()->Accept(this);
	printf(") ;\n")
}

void 
PrettyPrintVisitor::Visit(const CAsStm& p)//id = Exp ;
{
	printf("%s = ", p.GetId());
	p.GetExp()->Accept(this);
	printf(";\n");
}

void
PrettyPrintVisitor::Visit(const CAsExpStm& p)//id [ Exp ] = Exp
{
	printf("%s [ ", p.GetId());
	p.GetExpFirst()->Accept(this);
	printf("] = ");
	p.GetExpSecond()->Accept(this);
}

void
PrettyPrintVisitor::Visit(const COpExp& p)//Exp op Exp
{
	p.GetExpFirst()->Accept(this);
	if(p.GetOp == B_Plus) 
	{
		printf("+ ");
	}
	else if(p.GetOp == B_Minus)	
	{
		printf("- ");
	}
	else if(p.GetOp == B_Mult)	
	{
		printf("* ");
	}
	else if(p.GetOp == B_Div)	
	{
		printf("/ ");
	}
	else if(p.GetOp == B_Pow)	
	{
		printf("^");
	}
	p.GetExpSecond()->Accept(this);
}

void 
PrettyPrintVisitor::Visit(const CExExp& p)//Exp [ Exp ]
{
	p.GetExpFirst()->Accept(this);
	printf("[ ");
	p.GetExpSecondn()->Accept(this);
	printf("] ");
}

void
PrettyPrintVisitor::Visit(const CLenExp& p)//Exp . length
{
	p.GetExp()->Accept(this);
	printf(". length");
}

void
PrettyPrintVisitor::Visit(const CIdClExp& p)//Exp . id ( ExpList )
{
	p.GetExp()->Accept(this);
	printf(". %s ( ", p.GetId());
	p.GetExpList()->Accept(this);
	printf(")");
}

void
PrettyPrintVisitor::Visit(const CNExp& p)//num
{
	printf("%f", p.GetNum());
}
void
PrettyPrintVisitor::Visit(const CTrExp& p)//true
{
	printf("true");
}

void
PrettyPrintVisitor::Visit(const CFExp& p)//false
{
	printf("false");
}

void
PrettyPrintVisitor::Visit(const CIdExp& p)//id
{
	printf("%s", p.GetId());
}

void 
PrettyPrintVisitor::Visit(const CThExp& p)//this
{
	printf("this");
}

void
PrettyPrintVisitor::Visit(const CNewIntExp& p)//new int [ Exp ]
{
	printf("new int [ ");
	p.GetExp()->Accept(this);
	printf("]");
}

void
PrettyPrintVisitor::Visit(const CNewIdExp& p)//new id ()
{
	printf("new %s ()", p.GetId());
}

void
PrettyPrintVisitor::Visit(const CNotExp& p)//! Exp
{
	printf("! ");
	p.GetExp()->Accept();
}

void 
PrettyPrintVisitor::Visit(const CBrExp& p)//( Exp )
{
	printf("( ");
	p.GetExp()->Accept();
	printf(")");
}

void
PrettyPrintVisitor::Visit(const CTypeD& p)// defined
{
	if(p.GetType() == T_INT_BR)
	{
		printf("int [] ");
	}
	else if(p.GetType() == T_BOOL)
	{
		printf("boolean ");
	}
	else if(p.GetType() == T_INT)
	{
		printf("int ");
	}
}

//void
//PrettyPrintVisitor::Visit(const CTypeMass& p)
//{
//}

void
PrettyPrintVisitor::Visit(const CTypeId& p)// id
{
	printf("%s", p.GetId());
}

void
PrettyPrintVisitor::Visit(const CExpList& p)//Exp , ExpList
{
	p.GetExp()->Accept(this);
	printf(",");//????????????????????????????????????????
	p.GetExpList()->Accept(this);
}

void
PrettyPrintVisitor::Visit(const CFormalList& p)//Type Id FormalRestList
{
	p.GetType()->Accept(this);
	printf("%s", p.GetType());
	p.GetFormalList()->Accept(this);
}

void
PrettyPrintVisitor::Visit(const CClassDeclList& p)//ClassDeclList
{
	p.GetTop()->Accept(this);
	p.GetTail()->Accept(this);
}

void
PrettyPrintVisitor::Visit(const CVarDeclList& p)
{
	p.GetTop()->Accept(this);
	p.GetTail()->Accept(this);
}

void
PrettyPrintVisitor::Visit(const CMethodDeclList& p)
{
	p.GetTop()->Accept(this);
	p.GetTail()->Accept(this);
}

void
PrettyPrintVisitor::Visit(const CStmList& p)
{
	p.GetTop()->Accept(this);
	p.GetTail()->Accept(this);
}