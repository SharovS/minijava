# pragma once
# include "stdio.h"
#include <iostream>
#include <interface.h>
#include <PrettyPrintVisitor.h>

std::string identt( "   " );//отступы

void PrettyPrintVisitor::Visit( const CProgram& p ) //MainClass ClassDeclList
{
	p.GetMainClass()->Accept( this );
	if( p.GetClassDeclList() ) {
		p.GetClassDeclList()->Accept( this );
	}
}

void PrettyPrintVisitor::Visit( const CMainClass& p ) //class id { public static void main ( String [] id ) { Statement }}
{
	printf( "class %s { \n%spublic static Void main ( String [] %s ) { \n", p.GetIdFirst().c_str(), identt.c_str(), p.GetIDSecond().c_str() );
	identt += "    ";
	p.GetStm()->Accept( this );
	identt = identt.substr( 0, identt.length() - 4 );
	printf( "%s}\n}\n", identt.c_str() );
}

void PrettyPrintVisitor::Visit( const CClassDecl& p ) //class id { VarDeclList MethodDeclList }
{
	identt = "";
	printf( "\n%sclass %s { \n", identt.c_str(), p.GetId().c_str() );
	identt += "    ";
	if( p.GetVarDeclList() ) {
		p.GetVarDeclList()->Accept( this );
	}
	if( p.GetMethodDeclList() ) {
		p.GetMethodDeclList()->Accept( this );
	}
	printf( "\n}\n" );
}

void PrettyPrintVisitor::Visit( const CExClassDecl& p ) //class id extends id { VarDeclList MethodDeclList }
{
	identt = "";
	printf( "\n%sclass %s extends %s { \n", identt.c_str(), p.GetId().c_str(), p.GetIDExtend().c_str() );
	identt += "    ";
	if( p.GetVarDeclList() ) {
		p.GetVarDeclList()->Accept( this );
	}
	if( p.GetMethodDeclList() ) {
		p.GetMethodDeclList()->Accept( this );
	}
	printf( "\n}\n" );
}

void PrettyPrintVisitor::Visit( const CVarDecl& p ) //Type id
{
	printf( "%s%s %s ;\n", identt.c_str(), p.GetType().c_str(), p.GetId().c_str() );
}

void PrettyPrintVisitor::Visit( const CMethodDecl& p ) //public Type id ( FormalList ) { VarDecl* Statement* return Exp ;}
{
	printf( "%spublic %s %s ( ", identt.c_str(), p.GetType().c_str(), p.GetId().c_str() );
	if( p.GetFormalList() ) {
		p.GetFormalList()->Accept( this );
	}
	printf( ") { \n" );
	identt += "    ";
	if( p.GetVarDeclList() ) {
		p.GetVarDeclList()->Accept( this );
	}
	if( p.GetStmList() ) {
		p.GetStmList()->Accept( this );
	}
	printf( "\n%sreturn ", identt.c_str() );
	p.GetExp()->Accept( this );
	identt = identt.substr( 0, identt.length() - 4 );
	printf( ";\n%s}\n", identt.c_str() );
	//identt = identt.substr(0,identt.length() - 4);
}

void PrettyPrintVisitor::Visit( const CCompStm& p ) //{ Statement* }
{
	printf( "%s{\n", identt.c_str() );
	identt += "    ";
	if( p.GetStmList() ) {
		p.GetStmList()->Accept( this );
	}
	identt = identt.substr( 0, identt.length() - 4 );
	printf( "%s}\n", identt.c_str() );
	identt = identt.substr( 0, identt.length() - 4 );
}

void PrettyPrintVisitor::Visit( const CIfStm& p ) //if ( Exp ) Statement else Statement
{
	//могла напутоть с фигурными скобками
	std::string idtCopy( identt );
	printf( "%sif ( ", identt.c_str() );
	p.GetExp()->Accept( this );
	printf( " )\n" );
	identt += "    ";
	p.GetStmFirst()->Accept( this );
	identt = idtCopy;
	printf( "%selse\n", identt.c_str() );
	identt += "    ";
	p.GetlStmSecond()->Accept( this );
	identt = identt.substr( 0, identt.length() - 4 );
}

void PrettyPrintVisitor::Visit( const CWhStm& p )//while ( Exp ) Statement
{
	printf( "%swhile ( ", identt.c_str() );
	p.GetExp()->Accept( this );
	printf( " )\n" );
	identt += "    ";
	p.GetStm()->Accept( this );
	identt.substr( 0, identt.length() - 4 );
}

void PrettyPrintVisitor::Visit( const CForStm& p )//for ( Statement; Exp; Statement ) Statement
{
	printf( "%sfor ( ", identt.c_str() );
	p.GetInitStm()->Accept( this );
	printf( "; " );
	p.GetCheckExp()->Accept( this );
	printf( "; " );
	p.GetUpdateStm()->Accept( this );
	printf( " )\n" );
	identt += "    ";
	p.GetBodyStm()->Accept( this );
	identt.substr( 0, identt.length() - 4 );
}

void PrettyPrintVisitor::Visit( const CSOPStm& p )//System.out.println ( Exp ) ;
{
	printf( "%sSystem.out.println ( ", identt.c_str() );
	p.GetExp()->Accept( this );
	printf( " ) ;\n" );
}

void PrettyPrintVisitor::Visit( const CAsStm& p )//id = Exp ;
{
	printf( "%s%s = ", identt.c_str(), p.GetId().c_str() );
	p.GetExp()->Accept( this );
	printf( ";\n" );
}

void PrettyPrintVisitor::Visit( const CAsExpStm& p )//id [ Exp ] = Exp;
{
	printf( "%s%s [ ", identt.c_str(), p.GetId().c_str() );
	p.GetExpFirst()->Accept( this );
	printf( " ] = " );
	p.GetExpSecond()->Accept( this );
	printf( ";\n" );
}

void PrettyPrintVisitor::Visit( const COpExp& p )//Exp op Exp
{
	p.GetExpFirst()->Accept( this );
	if( p.GetOp() == B_Plus ) {
		printf( " + " );
	} else if( p.GetOp() == B_Minus ) {
		printf( " - " );
	} else if( p.GetOp() == B_Mult ) {
		printf( " * " );
	} else if( p.GetOp() == B_Div ) {
		printf( " / " );
	} else if( p.GetOp() == B_And ) {
		printf( " && " );
	} else if( p.GetOp() == B_Less ) {
		printf( " < " );
	}
	p.GetExpSecond()->Accept( this );
}

void PrettyPrintVisitor::Visit( const CExExp& p )//Exp [ Exp ]
{
	p.GetExpFirst()->Accept( this );
	printf( "[ " );
	p.GetExpSecondn()->Accept( this );
	printf( " ] " );
}

void PrettyPrintVisitor::Visit( const CLenExp& p )//Exp . length
{
	p.GetExp()->Accept( this );
	printf( ". length" );
}

void PrettyPrintVisitor::Visit( const CIdClExp& p )//Exp . id ( ExpList )
{
	p.GetExp()->Accept( this );
	printf( ". %s ( ", p.GetId().c_str() );
	if( p.GetExpList() ) {
		p.GetExpList()->Accept( this );
	}
	printf( " )" );
}

void PrettyPrintVisitor::Visit( const CNExp& p )//num
{
	printf( "%d", p.GetNum() );
}

void PrettyPrintVisitor::Visit( const CStrExp& p )//str
{
	printf( "%s", p.GetStr() );
}

void PrettyPrintVisitor::Visit( const CTrExp& p )//true
{
	printf( "true" );
}

void PrettyPrintVisitor::Visit( const CFExp& p )//false
{
	printf( "false" );
}

void PrettyPrintVisitor::Visit( const CIdExp& p )//id
{
	printf( "%s", p.GetId().c_str() );
}

void PrettyPrintVisitor::Visit( const CThExp& p )//this
{
	printf( "this" );
}

void PrettyPrintVisitor::Visit( const CNewIntExp& p )//new int [ Exp ]
{
	printf( "new int [ " );
	p.GetExp()->Accept( this );
	printf( " ]" );
}

void PrettyPrintVisitor::Visit( const CNewIdExp& p )//new id ()
{
	printf( "new %s ()", p.GetId().c_str() );
}

void PrettyPrintVisitor::Visit( const CNotExp& p )//! Exp
{
	printf( "! " );
	p.GetExp()->Accept( this );
}

void PrettyPrintVisitor::Visit( const CBrExp& p )//( Exp )
{
	printf( "( " );
	p.GetExp()->Accept( this );
	printf( " )" );
}


void PrettyPrintVisitor::Visit( const CTypeId& p )// id
{
	printf( "%s", p.GetId().c_str() );
}

void PrettyPrintVisitor::Visit( const CExpList& p )//Exp , ExpList
{
	p.GetExp()->Accept( this );
	printf( " " );
	if( p.GetExpList() ) {
		printf( ", " );//????????????????????????????????????????
		p.GetExpList()->Accept( this );
	}
}

void PrettyPrintVisitor::Visit( const CFormalList& p )//Type Id FormalRestList
{
	//p.GetType()->Accept(this);
	printf( "%s", p.GetType().c_str() );
	printf( " %s ", p.GetId().c_str() );
	if( p.GetFormalList() ) {
		printf( ", " );
		p.GetFormalList()->Accept( this );
	}
}

void PrettyPrintVisitor::Visit( const CClassDeclList& p )//ClassDeclList
{
	p.GetTop()->Accept( this );
	if( p.GetTail() ) {
		p.GetTail()->Accept( this );
	}
}

void PrettyPrintVisitor::Visit( const CVarDeclList& p )
{
	p.GetTop()->Accept( this );
	if( p.GetTail() ) {
		p.GetTail()->Accept( this );
	}
}

void PrettyPrintVisitor::Visit( const CMethodDeclList& p )
{
	p.GetTop()->Accept( this );
	if( p.GetTail() ) {
		p.GetTail()->Accept( this );
	}
}

void PrettyPrintVisitor::Visit( const CStmList& p )
{
	p.GetTop()->Accept( this );
	if( p.GetTail() ) {
		p.GetTail()->Accept( this );
	}
}

void PrettyPrintVisitor::Visit( const CEmptyStm& p )
{
	// do nothing
}