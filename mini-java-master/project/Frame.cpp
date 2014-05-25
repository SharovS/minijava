#pragma once
#include <Temp.h>
#include <Frame.h>
#include <assert.h>
#include <Tree.h>


namespace Frame
{

	CInReg::CInReg( Temp::CTemp* _temp ) : temp( _temp ) {}

	const Tree::IExp* CInReg::getVariable()const
	{
		return new Tree::TEMP( temp );
	}

	CInFrame::CInFrame( const Temp::CTemp* _fp, int _offset ) :
		fp( _fp ),
		offset( _offset )
	{
		assert( fp != 0 );
	}

	const Tree::IExp* CInFrame::getVariable() const
	{
		return new Tree::MEM( new Tree::BINOP(
			Tree::BINOP::PLUS, new Tree::TEMP( fp ), new Tree::CONST( offset ) ) );
	}


	CAccessList::CAccessList( const CAccess* _head, CAccessList* _tail ) : head( _head ), tail( _tail ) {}

	void CAccessList::addHead( const CAccess* _head )
	{
		tail = new CAccessList( head, tail );
		head = _head;
	}

	void CAccessList::addTail( CAccessList* _tail ) { tail = _tail; }

	const CAccess* CAccessList::getHead() { return head; }

	CAccessList* CAccessList::getTail() { return tail; }

	CFrame::CFrame( Temp::CLabel* _name, int _formalscount )
	{
		name = _name;

		Pointer = new Temp::CTemp( "fp" );
		th = new Temp::CTemp( "this" );

		CAccessList* temptemplist = 0;
		for( int i = 0; i < _formalscount; i++ ) {
			// +1, т.к. первый неявный параметр - this
			// (код присваивания this соответствующему регистру будет в прологе)
			CAccess* temp = new CInFrame( Pointer, i * wordSize() + 1 );

			CAccessList* templist = new CAccessList( temp, temptemplist );
			temptemplist = templist;
		}
		formals = temptemplist;
		locals = 0;
	}

	Temp::CLabel* CFrame::getName() const { return name; }

	CAccessList* CFrame::getFormals() { return formals; }

	Temp::CTemp* CFrame::getThis() { return th; }

	CAccess* CFrame::allocLocal()
	{
		CAccess* temp = new CInReg( new Temp::CTemp() );
		CAccessList* templist = new CAccessList( temp, locals );
		locals = templist;
		return temp;
	}

	Temp::CTemp* CFrame::FP()
	{
		return Pointer;
	}

	int CFrame::wordSize()
	{
		return sizeof(int);
	}

	Temp::CTemp* CFrame::thisValue()
	{
		return th;
	}
}