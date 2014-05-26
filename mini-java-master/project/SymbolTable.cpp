#pragma once;
#include <interface.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <SymbolTable.h>
#include <list>

using namespace std;

CVar::CVar( std::string  _c, std::string _name, CVar* _next ) : c( _c ), name( _name ), next( _next ) {}

void CVar::addType( std::string _c )
{
	c = _c;
}

void CVar::addName( std::string _name )
{
	name = _name;
}

void CVar::addNext( CVar* _next )
{
	next = _next;
}

std::string CVar::getType()
{
	return c;
}

std::string CVar::getName()
{
	return name;
}

CVar* CVar::getNext()
{
	return next;
}

void CVar::Print()
{
	printf( "%s ", c.c_str() );
	printf( "%s\n", name.c_str() );
	if( next != 0 ) {
		next->Print();
	}
}

int CVar::Length() const
{
	return 1 + (next == 0 ? 0 : next->Length());
}

CMethod::CMethod( std::string _c, std::string  _name, CVar* _par, CVar* _loc, CMethod* _next ) : c( _c ),
name( _name ), par( _par ), loc( _loc ), next( _next )
{}

std::string CMethod::getType()
{
	return c;
}

std::string CMethod::getName()
{
	return name;
}

CVar* CMethod::getPar()
{
	return par;
}

CVar* CMethod::getLoc()
{
	return loc;
}

CMethod* CMethod::getNext()
{
	return next;
}

void CMethod::addType( std::string _c )
{
	c = _c;
}

void CMethod::addName( std::string _name )
{
	name = _name;
}

void CMethod::addNext( CMethod* _next )
{
	next = _next;
}

void CMethod::addPar( CVar* _par )
{
	if( this->findTVar( _par->getName() ) == "" ) {
		if( par == 0 ) {
			par = _par;
		} else {
			CVar* temp = par;
			while( temp->getNext() != 0 ) {
				temp = temp->getNext();
			}
			temp->addNext( _par );
		}
	} else {
		printf( "double named parametr %s\n", (_par->getName()).c_str() );
	}
}

void CMethod::addLoc( CVar* _loc )
{

	if( this->findTVar( _loc->getName() ) == "" ) {
		if( loc == 0 ) {
			loc = _loc;
		} else {
			CVar * temp = loc;
			while( temp->getNext() != 0 ) {
				temp = temp->getNext();
			}
			temp->addNext( _loc );
		}
	} else {
		printf( "double named local var\n", (_loc->getName()).c_str() );
	}
}

std::string CMethod::findTVar( std::string id )
{
	CVar* temp = this->getPar();
	while( temp != 0 ) {
		if( temp->getName() == id ) {
			return temp->getType();
		} else {
			temp = temp->getNext();
		}
	}
	temp = this->getLoc();
	while( temp != 0 ) {
		if( temp->getName() == id ) {
			return temp->getType();
		} else {
			temp = temp->getNext();
		}
	}
	// Если ничего не нашли
	return "";
}

void CMethod::Print()
{
	printf( "%s ", c.c_str() );
	printf( "%s\n", name.c_str() );
	printf( "(\n" );
	if( par != 0 ) {
		par->Print();
	}
	printf( ")\n" );
	if( loc != 0 ) {
		loc->Print();
	}
	printf( "\n" );
	if( next != 0 ) {
		next->Print();
	}
}

int CMethod::FormalsCount()
{
	int i = 0;
	CVar* temp = par;
	while( temp != 0 ) {
		i++;
		temp = temp->getNext();
	}
	return i;
}

CClass::CClass( std::string _c, CVar* _var, CMethod* _meth, CClass* _next, std::string _ext ) : c( _c ), var( _var ),
meth( _meth ), next( _next ), ext( _ext )
{}

void CClass::addName( std::string _c )
{
	c = _c;
}

void CClass::addVar( CVar* _var )
{
	if( this->findTVar( _var->getName(), 0 ) == "" ) {
		if( var == 0 ) {
			var = _var;
		} else {
			CVar * temp = var;
			while( temp->getNext() != 0 ) {
				temp = temp->getNext();
			}
			temp->addNext( _var );
		}
	} else {
		printf( "double named class var %s\n", (_var->getName()).c_str() );
	}
}

void CClass::addMeth( CMethod* _meth )
{
	if( !this->FindMethod( _meth->getName(), 0 ) ) {
		if( meth == 0 ) {
			meth = _meth;
		} else {
			CMethod* temp = meth;
			while( temp->getNext() != 0 ) {
				temp = temp->getNext();
			}
			temp->addNext( _meth );
		}
	} else {
		printf( "double named class method %s\n", (_meth->getName()).c_str() );
	}
}

void CClass::addNext( CClass* _next )
{
	next = _next;
}

inline void CClass::addExt( std::string _ext )
{
	ext = _ext;
}

std::string CClass::getName()
{
	return c;
}

CVar* CClass::getVar()
{
	return var;
}

CMethod* CClass::getMeth()
{
	return meth;
}

CClass* CClass::getNext()
{
	return next;
}

inline std::string CClass::getExt()
{
	return ext;
}

std::string CClass::findTVar( std::string id, CSTable* table )
{
	CVar* temp = this->getVar();
	while( temp != 0 ) {
		if( temp->getName() == id ) {
			return temp->getType();
		} else {
			temp = temp->getNext();
		}
	}
	if( table != 0 ) {
		if( this->ext != "" ) {
			return table->FindClass( ext )->findTVar( id, table );
		}
	}
	return "";
}

CMethod * CClass::FindMethod( std::string id, CSTable* table )
{
	CMethod * temp = this->getMeth();
	while( temp != 0 ) {
		if( temp->getName() == id ) {
			return temp;
		}
		temp = temp->getNext();
	}
	if( table != 0 ) {
		if( ext != "" ) {
			return table->FindClass( ext )->FindMethod( id, table );
		}
	}
	std::cout << "Unfounded method: " << id << endl;
	return 0;
}

void CClass::Print()
{
	printf( "%s", c.c_str() );
	printf( "\n" );
	printf( "\n" );
	if( var != 0 ) {
		var->Print();
	}
	printf( "\n" );
	printf( "\n" );
	if( meth != 0 ) {
		meth->Print();
	}
	printf( "\n" );
	printf( "_________\n" );
	if( next != 0 ) {
		next->Print();
	}
	printf( "\n" );
}

bool CClass::lookUpVarOffset( std::string id, CSTable* table, int& offset )
{
	int tempoffset = 0;
	std::string temp = this->getName();
	while( (tempoffset == 0) || (temp != "") ) {
		tempoffset = (table->FindClass( temp ))->findOffsetVar( id, table );
		temp = table->FindClass( temp )->getExt();
	}
	if( tempoffset == 0 ) {
		return 0;
	}
	int count = 0;
	if( ext != "" ) {
		count = (table->FindClass( ext ))->getCountVar( table );
	}
	offset = tempoffset + count;
	return 1;
	//а)найти порядковй номер в классе, если нет в классе, спросить у предка.
	//б)если есть в классе, спросить сколько переменных хронится в предке и offset = породковый номер + кол-во переменных в предке
	// а - скопировать их getTVar и вернуть не тип, а число!
	// чтобы легче сделать (б) - сделать метод getVarCount для класса в таблице или просто для класса!!!!!!! 
}

int CClass::getCountVar( CSTable* table )
{
	int count = 0;
	CVar* temp = this->getVar();
	while( temp != 0 ) {
		count++;
		temp = temp->getNext();
	}
	if( ext != "" ) {
		count = count + (table->FindClass( ext ))->getCountVar( table );
	}
	return count;
}

int CClass::findOffsetVar( std::string id, CSTable* table )
{
	int offset = 0;
	CVar* temp = this->getVar();
	while( temp != 0 ) {
		offset++;
		if( temp->getName() == id ) {
			return offset;
		} else {
			temp = temp->getNext();
		}
	}
	return 0;
}

CSTable::CSTable() : CurrClass( 0 ), CurrMethod( 0 ), FirstClass( 0 ) {}

std::string CSTable::Lookup( std::string id )
{
	if( CurrClass == 0 ) {
		assert( false );
		return 0;
	} else if( CurrMethod == 0 ) {
		return CurrClass->findTVar( id, this );
	} else {
		if( CurrMethod->findTVar( id ) != "" ) {
			return CurrMethod->findTVar( id );
		}
		return CurrClass->findTVar( id, this );
	}
}

void CSTable::EnterClass( CClass* a )
{
	CurrClass = a;
}

void CSTable::EnterMethod( CMethod* a )
{
	CurrMethod = a;
}

void CSTable::LeaveClass()
{
	CurrClass = 0;
}

void CSTable::LeaveMethod()
{
	CurrMethod = 0;
}

void CSTable::SetFirst( CClass* first )
{
	FirstClass = first;
}

CClass* CSTable::getCurrClass()
{
	return CurrClass;
}

CMethod* CSTable::getCurrMethod()
{
	return CurrMethod;
}

void CSTable::SetClass( CClass* cl )
{
	if( FirstClass == 0 ) {
		FirstClass = cl;
	} else {
		CClass * temp = FirstClass;
		while( temp->getNext() != 0 ) {
			temp = temp->getNext();
		}
		temp->addNext( cl );
	}
}

CClass* CSTable::FindClass( std::string name )
{
	CClass* temp = FirstClass;
	while( temp->getName() != name ) {
		temp = temp->getNext();
		if( temp == 0 ) {
			std::cout << "Unfounded class:" << name << endl;
			break;
		}
	}
	return temp;
}

void CSTable::Print()
{
	FirstClass->Print();
}

//bool CSTable::CircleChecker()
//{
//	list <CClass*> prev;
//	CClass* temp, tempext;
//	temp=FirstClass;
//	while(temp!=0){
//		if( temp->getExt()!=""){
//			prev.push_back(temp);
//			while( tempext!=0)
//			{
//				prev.push_back(tempext);
//				tempext=this->FindClass(tempext->addExt());
//				for()
//				{
//					if()
//					else
//					{
//					}
//				}
//			}
//		}
//		temp=temp->getNext()
//	}
//}

//--------------------------------------------------------------------------------------

void CSTVisitor::EnterClass( CClass* a )
{
	CurrClass = a;
}

void CSTVisitor::EnterMethod( CMethod* a )
{
	CurrMethod = a;
}

void CSTVisitor::LeaveClass()
{
	CurrClass = 0;
}

void CSTVisitor::LeaveMethod()
{
	CurrMethod = 0;
}

void CSTVisitor::Visit( const CProgram& p )
{
	p.GetMainClass()->Accept( this );
	if( p.GetClassDeclList() != 0 ) {
		p.GetClassDeclList()->Accept( this );
	}
}

void CSTVisitor::Visit( const CMainClass& p )
{
	CClass* cl = new CClass( p.GetIdFirst(), 0, new CMethod( "void", "main",
		new CVar( "string", p.GetIDSecond(), 0 ), 0, 0 ), 0, "" );
	ST->SetClass( cl );
}

void CSTVisitor::Visit( const CClassDecl& p )
{
	if( CurrMethod != 0 ) {
		assert( false );
	} else if( CurrClass != 0 ) {
		assert( false );
	} else {
		CClass* cl = new CClass( p.GetId(), 0, 0, 0, "" );
		CurrClass = cl;
		if( p.GetMethodDeclList() != 0 ) {
			p.GetMethodDeclList()->Accept( this );
		}
		if( p.GetVarDeclList() != 0 ) {
			p.GetVarDeclList()->Accept( this );
		}
		ST->SetClass( cl );
		CurrClass = 0;
	}
}

void CSTVisitor::Visit( const CExClassDecl& p )
{
	if( CurrMethod != 0 ) {
		assert( false );
	} else if( CurrClass != 0 ) {
		assert( false );
	} else {
		CClass * cl = new CClass( p.GetId(), 0, 0, 0, p.GetIDExtend() );
		CurrClass = cl;
		if( p.GetMethodDeclList() != 0 ) {
			p.GetMethodDeclList()->Accept( this );
		}
		if( p.GetVarDeclList() != 0 ) {
			p.GetVarDeclList()->Accept( this );
		}
		ST->SetClass( cl );
		CurrClass = 0;
	}
}

void CSTVisitor::Visit( const CVarDecl& p )
{
	CVar* var = new CVar( p.GetType(), p.GetId(), 0 );
	if( CurrClass == 0 ) {
		assert( false );
	} else if( CurrMethod == 0 ) {
		CurrClass->addVar( var );
	} else {
		CurrMethod->addLoc( var );
	}
}

void CSTVisitor::Visit( const CMethodDecl& p )
{
	CMethod* meth = new CMethod( p.GetType(), p.GetId(), 0, 0, 0 );
	CurrMethod = meth;
	if( p.GetFormalList() != 0 ) {
		p.GetFormalList()->Accept( this );
	}
	if( p.GetVarDeclList() != 0 ) {
		p.GetVarDeclList()->Accept( this );
	}
	CurrClass->addMeth( meth );
	CurrMethod = 0;
}

void CSTVisitor::Visit( const CCompStm& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CIfStm& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CWhStm& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CForStm& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CSOPStm& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CAsStm& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CAsExpStm& p )
{
	assert( false );
}

void CSTVisitor::Visit( const COpExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CPreUnOpExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CPostUnOpExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CExExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CLenExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CIdClExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CNExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CStrExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CTrExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CFExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CIdExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CThExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CNewIntExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CNewIdExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CNotExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CBrExp& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CTypeId& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CExpList& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CFormalList& p )
{
	if( &p ) {
		if( CurrMethod != 0 ) {
			CVar* var = new CVar( p.GetType(), p.GetId(), 0 );
			CurrMethod->addPar( var );
			if( p.GetFormalList() != 0 ) {
				p.GetFormalList()->Accept( this );
			}
		}
	}
}

void CSTVisitor::Visit( const CClassDeclList& p )
{
	p.GetTop()->Accept( this );
	if( p.GetTail() != 0 ) {
		p.GetTail()->Accept( this );
	}
}

void CSTVisitor::Visit( const CVarDeclList& p )
{
	p.GetTop()->Accept( this );
	if( p.GetTail() != 0 ) {
		p.GetTail()->Accept( this );
	}
}

void CSTVisitor::Visit( const CMethodDeclList& p )
{
	p.GetTop()->Accept( this );
	if( p.GetTail() != 0 ) {
		p.GetTail()->Accept( this );
	}
}

void CSTVisitor::Visit( const CStmList& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CEmptyStm& p )
{
	assert( false );
}

void CSTVisitor::Visit( const CExpStm& p )
{
	assert( false );
}