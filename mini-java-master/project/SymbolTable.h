#pragma once;
#include <interface.h>
#include <assert.h>
#include <string>

//--------------------------------------------------------------------------------------

class CSTable;

class CVar {
public:
	CVar( std::string  _c, std::string _name, CVar* _next );
	void addType( std::string _c );
	void addName( std::string _name );
	void addNext( CVar* _next );
	std::string getType();
	std::string getName();
	CVar* getNext();
	void Print();
	// Длина оставшейся части списка
	int Length() const;

private:
	std::string c;
	std::string name;
	CVar* next;
};

//--------------------------------------------------------------------------------------

class CMethod {
public:
	CMethod( std::string _c, std::string  _name, CVar* _par, CVar* _loc, CMethod* _next );
	std::string getType();
	std::string getName();
	CVar* getPar();
	CVar* getLoc();
	CMethod* getNext();
	void addType( std::string _c );
	void addName( std::string _name );
	void addPar( CVar* _par );
	void addLoc( CVar* _loc );
	void addNext( CMethod* _next );
	std::string findTVar( std::string id );
	void Print();
	int FormalsCount();

private:
	std::string c;
	std::string name;
	CVar* par;
	CVar* loc;
	CMethod* next;
};

//--------------------------------------------------------------------------------------

class CClass {
public:
	CClass( std::string _c, CVar* _var, CMethod* _meth, CClass* _next, std::string _ext );
	void addName( std::string _c );
	void addVar( CVar * _var );
	void addMeth( CMethod * _meth );
	void addNext( CClass * _next );
	void addExt( std::string _ext );
	std::string getName();
	CVar* getVar();
	CMethod* getMeth();
	CClass* getNext();
	std::string getExt();
	std::string findTVar( std::string id, CSTable* table );
	//ищет номер переменной в классе
	CMethod* FindMethod( std::string id, CSTable* table );
	void Print();
	bool lookUpVarOffset( std::string id, CSTable* table, int& offset );
	int getCountVar( CSTable* table ); //количество переменных в классе и его предках
	int findOffsetVar( std::string id, CSTable* table ); //смещение в выбранном классе без предков, чтобы не запутаться, если не нашли - 0
private:
	std::string c;
	CVar* var;
	CMethod* meth;
	CClass* next;
	std::string ext;
};

//--------------------------------------------------------------------------------------

class CSTable {
public:
	CSTable();
	std::string Lookup( std::string id );
	void EnterClass( CClass * a );
	void EnterMethod( CMethod * a );
	void LeaveClass();
	void LeaveMethod();
	void SetFirst( CClass* first );
	CClass* getCurrClass();
	CMethod* getCurrMethod();
	void SetClass( CClass * cl );
	CClass* FindClass( std::string name );
	void Print();
	bool CircleChecker();

private:
	CClass* CurrClass;
	CMethod* CurrMethod;
	CClass* FirstClass;
};

//----------------------------------------------------------------------------------------

class CSTVisitor : public IVisitor {
public:
	CSTVisitor() : CurrClass( 0 ), CurrMethod( 0 ), ST( new CSTable() ) {}
	void EnterClass( CClass* a );
	void EnterMethod( CMethod* a );
	void LeaveClass();
	void LeaveMethod();
	CSTable * GetTable() { return ST; }
	void Visit( const CProgram& p );
	void Visit( const CMainClass& p );
	void Visit( const CClassDecl& p );
	void Visit( const CExClassDecl& p );
	void Visit( const CVarDecl& p );
	void Visit( const CMethodDecl& p );
	void Visit( const CCompStm& p );
	void Visit( const CIfStm& p );
	void Visit( const CWhStm& p );
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
	void Visit( const CVarDeclExp& p );
private:
	CClass* CurrClass;
	CMethod* CurrMethod;
	CSTable* ST;
};