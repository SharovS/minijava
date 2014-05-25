# pragma once
#include <string>
#include <interface.h>
#include <SymbolTable.h>

class CTypeCheckerVisitor : public IVisitor {
public:
	CTypeCheckerVisitor( CSTable* _table ) : table( _table ), isError( false ), lastType( "" ), varList( 0 ), counter( 0 ) {}
	~CTypeCheckerVisitor() {}
	void Visit( const CProgram& p );
	void Visit( const CMainClass& p );
	void Visit( const CClassDecl& p );
	void Visit( const CExClassDecl& p );
	void Visit( const CVarDecl& p );
	void Visit( const CMethodDecl& p );
	void Visit( const CCompStm& p );
	void Visit( const CIfStm& p );
	void Visit( const CWhStm& p );
	void Visit( const CForStm& p );
	void Visit( const CSOPStm& p );
	void Visit( const CAsStm& p );
	void Visit( const CAsExpStm& p );
	void Visit( const COpExp& p );
	void Visit( const CExExp& p );
	void Visit( const CLenExp& p );
	void Visit( const CIdClExp& p );
	void Visit( const CNExp& p );
	void Visit( const CStrExp& p );
	void Visit( const CTrExp& p );
	void Visit( const CFExp& p );
	void Visit( const CIdExp& p );
	void Visit( const CThExp& p );
	void Visit( const CNewIntExp& p );
	void Visit( const CNewIdExp& p );
	void Visit( const CNotExp& p );
	void Visit( const CBrExp& p );
	void Visit( const CTypeId& p );
	void Visit( const CExpList& p );
	void Visit( const CFormalList& p );
	void Visit( const CClassDeclList& p );
	void Visit( const CVarDeclList& p );
	void Visit( const CMethodDeclList& p );
	void Visit( const CStmList& p );
	void Visit( const CEmptyStm& p );

	bool wasError();
private:
	CSTable* table;
	bool isError;
	std::string lastType;
	CVar* varList;
	int counter;
};