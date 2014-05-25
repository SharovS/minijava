
#pragma once
#include <iostream>
# include <stdio.h>
#include <IntermediateTreePrinter.h>
#include <Tree.h>
#include <assert.h>

using namespace std;

std::string ident( "" );

void IntermediateTreeVisitor::Visit( const Tree::CONST& p )
{
	cout << "CONST(" << p.getInt() << ")";
}

void IntermediateTreeVisitor::Visit( const Tree::NAME& p )
{
	cout << "NAME(" << p.getLabel()->getLabelName() << ")";
}

void IntermediateTreeVisitor::Visit( const Tree::TEMP& p )
{
	cout << "TEMP(" << p.getTemp()->getId() << ")";
}

void IntermediateTreeVisitor::Visit( const Tree::BINOP& p )
{
	cout << "BINOP(";

	if( p.getBinOp() == Tree::BINOP::PLUS ) {
		cout << " + ";
	} else if( p.getBinOp() == Tree::BINOP::MINUS ) {
		cout << " - ";
	} else if( p.getBinOp() == Tree::BINOP::MUL ) {
		cout << " * ";
	} else if( p.getBinOp() == Tree::BINOP::DIV ) {
		cout << " / ";
	} else if( p.getBinOp() == Tree::BINOP::AND ) {
		cout << " AND ";
	} else if( p.getBinOp() == Tree::BINOP::OR ) {
		cout << " OR ";
	} else if( p.getBinOp() == Tree::BINOP::LSHIFT ) {
		cout << " LSHIFT ";
	} else if( p.getBinOp() == Tree::BINOP::RSHIFT ) {
		cout << " RSHIFT ";
	} else if( p.getBinOp() == Tree::BINOP::ARSHIFT ) {
		cout << " ARSHIFT ";
	} else if( p.getBinOp() == Tree::BINOP::XOR ) {
		cout << " XOR ";
	} else {
		assert( false );
	}

	cout << ", ";
	p.getLeftExp()->Accept( this );
	ident += "    ";
	cout << ", " << endl << ident;
	p.getRightExp()->Accept( this );
	cout << ")";
	ident = ident.substr( 0, ident.length() - 4 );
}

void IntermediateTreeVisitor::Visit( const Tree::MEM& p )
{
	cout << "MEM(";
	p.getExp()->Accept( this );
	cout << ")";
}

void IntermediateTreeVisitor::Visit( const Tree::CALL& p )
{
	cout << "CALL(";
	p.getFuncExp()->Accept( this );
	ident += "    ";
	cout << ", " << endl << ident;

	p.getArgsExpList()->Accept( this );
	cout << ")";
	ident = ident.substr( 0, ident.length() - 4 );
}

void IntermediateTreeVisitor::Visit( const Tree::ESEQ& p )
{
	cout << "ESEQ(";
	p.getStm()->Accept( this );
	ident += "    ";
	cout << ", " << endl << ident;
	p.getExp()->Accept( this );
	cout << ")";
	ident = ident.substr( 0, ident.length() - 4 );
}

void IntermediateTreeVisitor::Visit( const Tree::MOVE& p )
{
	cout << "MOVE(";
	p.getDst()->Accept( this );
	ident += "    ";
	cout << ", " << endl << ident;
	p.getSrc()->Accept( this );
	cout << ")";
	ident = ident.substr( 0, ident.length() - 4 );
}

void IntermediateTreeVisitor::Visit( const Tree::EXP& p )
{
	cout << "EXP(";
	p.getExp()->Accept( this );
	cout << ")";
}

void IntermediateTreeVisitor::Visit( const Tree::JUMP& p )
{
	cout << "JUMP(";
	const Temp::CLabelList* pwh( p.getTgList() );
	ident += "    ";
	while( pwh ) {
		cout << pwh->getTop()->getLabelName() << ", " << endl << ident;
		pwh = pwh->getTail();
	}
	//cout << p.getTarget()->getLabelName() << ")";
	cout << ")";
	ident = ident.substr( 0, ident.length() - 4 );
}

void IntermediateTreeVisitor::Visit( const Tree::CJUMP& p )
{
	cout << "CJUMP(";
	switch( p.getRelOp() ) {
		case Tree::CJUMP::EQ:
			cout << " == ";
			break;
		case Tree::CJUMP::NE:
			cout << " != ";
			break;
		case Tree::CJUMP::LT:
			cout << " < ";
			break;
		case Tree::CJUMP::GT:
			cout << " > ";
			break;
		case Tree::CJUMP::LE:
			cout << " <= ";
			break;
		case Tree::CJUMP::GE:
			cout << " >= ";
			break;
		case Tree::CJUMP::ULT:
			cout << " ULT ";
			break;
		case Tree::CJUMP::ULE:
			cout << " ULE ";
			break;
		case Tree::CJUMP::UGT:
			cout << " UGT ";
			break;
		case Tree::CJUMP::UGE:
			cout << " UGE ";
			break;
	}
	cout << ", ";
	p.getLeftExp()->Accept( this );
	ident += "    ";
	cout << ", " << endl << ident;
	p.getRightExp()->Accept( this );
	cout << ", " << endl << ident;
	cout << p.getTrueLabel()->getLabelName() << ", " << endl << ident
		<< p.getFalseLabel()->getLabelName() << ")";
	ident = ident.substr( 0, ident.length() - 4 );
}

void IntermediateTreeVisitor::Visit( const Tree::SEQ& p )
{
	cout << "SEQ(";
	p.getLeftStm()->Accept( this );
	ident += "    ";
	cout << ", " << endl << ident;
	p.getRightStm()->Accept( this );
	cout << ")";
	ident = ident.substr( 0, ident.length() - 4 );
}

void IntermediateTreeVisitor::Visit( const Tree::LABEL& p )
{
	cout << " " << p.getLabel()->getLabelName();
}

void IntermediateTreeVisitor::Visit( const Tree::ExpList& p )
{
	p.getTop()->Accept( this );
	if( p.getTail() != 0 ) {
		p.getTail()->Accept( this );
	}
}

void IntermediateTreeVisitor::Visit( const Tree::StmList& p )
{
	p.getTop()->Accept( this );
	if( p.getTail() != 0 ) {
		p.getTail()->Accept( this );
	}
}
