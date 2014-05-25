# pragma once
# include "stdio.h"
# include <string>

class CProgram;
class CMainClass;
class CClassDecl;
class CExClassDecl;
class CVarDecl;
class CMethodDecl;
class CCompStm;
class CIfStm;
class CWhStm;
class CSOPStm;
class CAsStm;
class CAsExpStm;
class COpExp;
class CExExp;
class CLenExp;
class CIdClExp;
class CNExp;
class CStrExp;
class CTrExp;
class CFExp;
class CIdExp;
class CThExp;
class CNewIntExp;
class CNewIdExp;
class CNotExp;
class CBrExp;
class CTypeId;
class CExpList;
class CFormalList;
class CClassDeclList;
class CVarDeclList;
class CMethodDeclList;
class CStmList;
class CVarDeclExp;

class IVisitor {
public:
	virtual ~IVisitor() {};
	virtual void Visit( const CProgram& p ) = 0;
	virtual void Visit( const CMainClass& p ) = 0;
	virtual void Visit( const CClassDecl& p ) = 0;
	virtual void Visit( const CExClassDecl& p ) = 0;
	virtual void Visit( const CVarDecl& p ) = 0;
	virtual void Visit( const CMethodDecl& p ) = 0;
	virtual void Visit( const CCompStm& p ) = 0;
	virtual void Visit( const CIfStm& p ) = 0;
	virtual void Visit( const CWhStm& p ) = 0;
	virtual void Visit( const CSOPStm& p ) = 0;
	virtual void Visit( const CAsStm& p ) = 0;
	virtual void Visit( const CAsExpStm& p ) = 0;
	virtual void Visit( const COpExp& p ) = 0;
	virtual void Visit( const CExExp& p ) = 0;
	virtual void Visit( const CLenExp& p ) = 0;
	virtual void Visit( const CIdClExp& p ) = 0;
	virtual void Visit( const CNExp& p ) = 0;
	virtual void Visit( const CStrExp& p ) = 0;
	virtual void Visit( const CTrExp& p ) = 0;
	virtual void Visit( const CFExp& p ) = 0;
	virtual void Visit( const CIdExp& p ) = 0;
	virtual void Visit( const CThExp& p ) = 0;
	virtual void Visit( const CNewIntExp& p ) = 0;
	virtual void Visit( const CNewIdExp& p ) = 0;
	virtual void Visit( const CNotExp& p ) = 0;
	virtual void Visit( const CBrExp& p ) = 0;
	virtual void Visit( const CTypeId& p ) = 0;
	virtual void Visit( const CExpList& p ) = 0;
	virtual void Visit( const CFormalList& p ) = 0;
	virtual void Visit( const CClassDeclList& p ) = 0;
	virtual void Visit( const CVarDeclList& p ) = 0;
	virtual void Visit( const CMethodDeclList& p ) = 0;
	virtual void Visit( const CStmList& p ) = 0;
	virtual void Visit( const CVarDeclExp& p ) = 0;
};

//--------------------------------------------------------------------------------------

class IStm {
public:
	virtual ~IStm() = 0 {};
	virtual void Accept( IVisitor *v ) const = 0 {};
};

//--------------------------------------------------------------------------------------

class IProgram {
public:
	virtual ~IProgram() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};

//--------------------------------------------------------------------------------------

class IMainClass {
public:
	virtual ~IMainClass() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};

//--------------------------------------------------------------------------------------

class IClassDecl {
public:
	virtual ~IClassDecl() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};

//--------------------------------------------------------------------------------------

class IVarDecl {
public:
	virtual ~IVarDecl() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};

//--------------------------------------------------------------------------------------

class IMethodDecl {
public:
	virtual ~IMethodDecl() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};

//--------------------------------------------------------------------------------------

class IExp {
public:
	virtual ~IExp() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};

//--------------------------------------------------------------------------------------

class IType {
public:
	virtual ~IType() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};

//--------------------------------------------------------------------------------------

enum CBinop {
	B_Plus,
	B_Minus,
	B_Mult,
	B_Div,
	B_And,
	B_Less
};

//--------------------------------------------------------------------------------------

class IExpList {
public:
	virtual ~IExpList() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};

//--------------------------------------------------------------------------------------

class IFormalList {
public:
	virtual ~IFormalList() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};

//--------------------------------------------------------------------------------------

class IClassDeclList {
public:
	virtual ~IClassDeclList() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};

//--------------------------------------------------------------------------------------

class IVarDeclList {
public:
	virtual ~IVarDeclList() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};

//--------------------------------------------------------------------------------------

class IMethodDeclList {
public:
	virtual ~IMethodDeclList() = 0 {};
	virtual void Accept( IVisitor *v ) const = 0 {};
};

//--------------------------------------------------------------------------------------

class IStmList {
public:
	virtual ~IStmList() = 0 {};
	virtual void Accept( IVisitor *v )const = 0 {};
};

//--------------------------------------------------------------------------------------

//MainClass ClassDecl*
class CProgram : public IProgram {
public:
	CProgram( const IMainClass *_n, const IClassDeclList *_m ) : n( _n ), m( _m ) {}
	~CProgram() {}
	const IMainClass* GetMainClass() const { return n; }
	const IClassDeclList* GetClassDeclList() const { return m; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }

private:
	const IMainClass *n;
	const IClassDeclList *m;
};

//--------------------------------------------------------------------------------------

//class id { public static void main ( String [] id ) { Statement }}
class CMainClass : public IMainClass {
public:
	CMainClass( const std::string _a, const std::string _b, const IStm *_n ) :
		a( _a ), b( _b ), n( _n ) {}
	~CMainClass() {}
	const std::string GetIdFirst() const { return a; }
	const std::string GetIDSecond() const { return b; }
	const IStm* GetStm() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string a;
	const std::string b;
	const IStm *n;
};

//--------------------------------------------------------------------------------------

//class id { VarDecl* MethodDecl* }
class CClassDecl : public IClassDecl {
public:
	CClassDecl( const std::string _a, const IVarDeclList* _m, const IMethodDeclList* _n ) :
		a( _a ), m( _m ), n( _n ) {}
	~CClassDecl() {}
	const std::string GetId() const { return a; }
	const IVarDeclList* GetVarDeclList() const { return m; }
	const IMethodDeclList* GetMethodDeclList() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string a;
	const IVarDeclList *m;
	const IMethodDeclList *n;
};

//--------------------------------------------------------------------------------------

//class id extends id { VarDecl* MethodDecl* }
class CExClassDecl : public IClassDecl {
public:
	CExClassDecl( const std::string _a, const std::string _b, const IVarDeclList *_m, const IMethodDeclList *_n ) :
		a( _a ), b( _b ), m( _m ), n( _n ) {}
	~CExClassDecl() {}
	const std::string GetId() const { return a; }
	const std::string GetIDExtend() const { return b; }
	const IVarDeclList* GetVarDeclList() const { return m; }
	const IMethodDeclList* GetMethodDeclList() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string a;
	const std::string b;
	const IVarDeclList *m;
	const IMethodDeclList *n;
};

//--------------------------------------------------------------------------------------

//Type id
class CVarDecl : public IVarDecl {
public:
	CVarDecl( const std::string _m, const std::string _a ) : m( _m ), a( _a ) {
		hasExp = false;
	}
	~CVarDecl() {}
	const std::string GetType() const { return m; }
	const std::string GetId() const { return a; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string m;
	const std::string a;
	bool hasExp;
};

//--------------------------------------------------------------------------------------

//public Type id ( FormalList ) { VarDecl* Statement* return Exp ;}
class CMethodDecl : public IMethodDecl {
public:
	CMethodDecl( const std::string _m, const std::string _a, const IFormalList *_n, const IVarDeclList *_l, const IStmList *_k, const IExp *_p ) :
		m( _m ), a( _a ), n( _n ), l( _l ), k( _k ), p( _p ) {}
	~CMethodDecl() {}
	const std::string GetType() const { return m; }
	const std::string GetId() const { return a; }
	const IFormalList* GetFormalList() const { return n; }
	const IVarDeclList* GetVarDeclList() const { return l; }
	const IStmList* GetStmList() const { return k; }
	const IExp* GetExp() const { return p; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string m;
	const std::string a;
	const IFormalList *n;
	const IVarDeclList *l;
	const IStmList* k;
	const IExp *p;
};

//--------------------------------------------------------------------------------------

//{ Statement* }
class CCompStm : public IStm {
public:
	CCompStm( const IStmList *_n ) : n( _n ) {}
	~CCompStm() {}
	const IStmList* GetStmList() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IStmList *n;
};

//--------------------------------------------------------------------------------------

//if ( Exp ) Statement else Statement
class CIfStm : public IStm {
public:
	CIfStm( const IExp *_m, const IStm *_n, const IStm *_l ) : m( _m ), n( _n ), l( _l ) {};
	~CIfStm() {}
	const IExp* GetExp() const { return m; }
	const IStm* GetStmFirst() const { return n; }
	const IStm* GetlStmSecond() const { return l; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExp *m;
	const IStm *n;
	const IStm *l;
};

//--------------------------------------------------------------------------------------

//while ( Exp ) Statement
class CWhStm : public IStm {
public:
	CWhStm( const IExp *_m, const IStm*_n ) : m( _m ), n( _n ) {};
	CWhStm() {}
	const IExp* GetExp() const { return m; }
	const IStm* GetStm() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExp *m;
	const IStm *n;
};

//--------------------------------------------------------------------------------------

//System.out.println ( Exp ) ;
class CSOPStm : public IStm {
public:
	CSOPStm( const IExp *_m ) : m( _m ) {};
	CSOPStm() {}
	const IExp* GetExp() const { return m; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExp *m;
};

//--------------------------------------------------------------------------------------

//id = Exp ;
class CAsStm : public IStm {
public:
	CAsStm( const std::string _a, const IExp *_m ) : a( _a ), m( _m ) {};
	~CAsStm() {}
	const std::string GetId() const { return a; }
	const IExp* GetExp() const { return m; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string a;
	const IExp* m;
};

//--------------------------------------------------------------------------------------

//Type id = Exp ;
class CVarDeclExp : public IStm {
public:
	CVarDeclExp( const std::string _a, const CAsStm *_m ) : a( _a ),  m( _m ) {		
	};
	~CVarDeclExp() {}
	const std::string GetType() const { return a; }
	const std::string GetId() const { return m->GetId(); }
	const IExp* GetExp() const { return m->GetExp(); }
	void Accept( IVisitor* visitor ) const { 
		//visitor->Visit( new CVarDecl( a, b ) );
		visitor->Visit( *this ); 
	}
	const CAsStm* GetAsStm() const { return m; } 
private:
	const std::string a;
	const std::string b;
	const CAsStm* m;
};


//--------------------------------------------------------------------------------------

//id [ Exp ]= Exp
class CAsExpStm : public IStm {
public:
	CAsExpStm( const std::string _a, const IExp *_m, const IExp *_n ) : a( _a ), m( _m ), n( _n ) {};
	~CAsExpStm() {}
	const std::string GetId() const { return a; }
	const IExp* GetExpFirst() const { return m; }
	const IExp* GetExpSecond() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string a;
	const IExp *m;
	const IExp *n;
};

//--------------------------------------------------------------------------------------

//Exp op Exp
class COpExp :public IExp {
public:
	COpExp( const IExp *_a, CBinop _op, const IExp *_c ) : a( _a ), op( _op ), c( _c ) {}
	~COpExp() {}
	const IExp* GetExpFirst() const { return a; }
	CBinop GetOp() const { return op; }
	const IExp* GetExpSecond() const { return c; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExp *a;
	CBinop op;
	const IExp *c;
};

//--------------------------------------------------------------------------------------

//Exp [ Exp ]
class CExExp :public IExp {
public:
	CExExp( const IExp *_m, const IExp *_n ) : m( _m ), n( _n ) {};
	~CExExp() {}
	const IExp* GetExpFirst() const { return m; }
	const IExp* GetExpSecondn() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExp *m;
	const IExp *n;
};

//--------------------------------------------------------------------------------------

//Exp . length
class CLenExp :public IExp {
public:
	CLenExp( const IExp *_n ) : n( _n ) {};
	~CLenExp() {}
	const IExp* GetExp() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExp *n;
};

//--------------------------------------------------------------------------------------

//Exp . id ( ExpList )
class CIdClExp :public IExp {
public:
	CIdClExp( const IExp *_m, const std::string _a, const IExpList *_n ) : m( _m ), a( _a ), n( _n ) {};
	~CIdClExp() {}
	const IExp* GetExp() const { return m; }
	const std::string GetId() const { return a; }
	const IExpList* GetExpList() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExp *m;
	const std::string a;
	const IExpList *n;
};

//--------------------------------------------------------------------------------------

//num
class CNExp :public IExp {
public:
	CNExp( const int _a ) : a( _a ) {}
	~CNExp() {}
	const int GetNum() const { return a; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const int a; //был double, изменено int
};

//--------------------------------------------------------------------------------------

//str
class CStrExp :public IExp {
public:
	CStrExp( const char* _a ) : a( _a ) {}
	~CStrExp() {}
	const char* GetStr() const { return a; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const char* a;
};

//--------------------------------------------------------------------------------------

//true
class CTrExp :public IExp {
public:
	CTrExp() {}
	~CTrExp() {}
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
};

//--------------------------------------------------------------------------------------

//false
class CFExp :public IExp {
public:
	CFExp() {}
	~CFExp() {}
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
};

//--------------------------------------------------------------------------------------

//id
class CIdExp :public IExp {
public:
	CIdExp( const std::string _a ) : a( _a ) {}
	~CIdExp() {}
	const std::string GetId() const { return a; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string a;
};

//--------------------------------------------------------------------------------------

//this
class CThExp :public IExp {
public:
	CThExp() {}
	~CThExp() {}
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
};

//--------------------------------------------------------------------------------------

//new int [ Exp ]
class CNewIntExp :public IExp {
public:
	CNewIntExp( const IExp *_n ) : n( _n ) {}
	~CNewIntExp() {}
	const IExp* GetExp() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExp *n;
};

//--------------------------------------------------------------------------------------

//new id ()
class CNewIdExp :public IExp {
public:
	CNewIdExp( const std::string _a ) : a( _a ) {}
	~CNewIdExp() {}
	const std::string GetId() const { return a; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string a;
};

//--------------------------------------------------------------------------------------

//! Exp
class CNotExp :public IExp {
public:
	CNotExp( const IExp *_n ) : n( _n ) {};
	~CNotExp() {}
	const IExp* GetExp() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExp *n;
};

//--------------------------------------------------------------------------------------

//( Exp )
class CBrExp : public IExp {
public:
	CBrExp( const IExp *_n ) : n( _n ) {};
	~CBrExp() {}
	const IExp* GetExp() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExp *n;
};

//--------------------------------------------------------------------------------------

// id
class CTypeId : public IType {
public:
	CTypeId( const std::string _n ) : n( _n ) {};
	~CTypeId() {}
	const std::string GetId() const { return n; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string n;
};

//--------------------------------------------------------------------------------------

//Exp ExpList
class CExpList : public IExpList {
public:
	CExpList( const IExp *_a, const IExpList *_b ) : a( _a ), b( _b ) {};
	~CExpList() {}
	const IExp* GetExp() const { return a; }
	const IExpList* GetExpList() const { return b; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IExp *a;
	const IExpList *b;
};

//--------------------------------------------------------------------------------------

//Type Id FormalRestList
class CFormalList : public IFormalList {
public:
	CFormalList( const std::string _a, const std::string _b, const IFormalList * _c ) :
		a( _a ), b( _b ), c( _c ) {};
	~CFormalList() {}
	const std::string GetType() const { return a; }
	const std::string GetId() const { return b; }
	const IFormalList* GetFormalList() const { return c; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const std::string a;
	const std::string b;
	const IFormalList *c;
};

//--------------------------------------------------------------------------------------

//ClassDeclList
class CClassDeclList : public IClassDeclList {
public:
	CClassDeclList( const IClassDecl *_a, const IClassDeclList *_b ) : a( _a ), b( _b ) {};
	CClassDeclList() {}
	const IClassDecl* GetTop() const { return a; }
	const IClassDeclList* GetTail() const { return b; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IClassDecl* a;
	const IClassDeclList* b;
};

//--------------------------------------------------------------------------------------

//VarDeclList
class CVarDeclList : public IVarDeclList {
public:
	CVarDeclList( const IVarDecl *_a, const IVarDeclList *_b ) : a( _a ), b( _b ) {};
	~CVarDeclList() {}
	const IVarDecl* GetTop() const { return a; }
	const IVarDeclList* GetTail() const { return b; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IVarDecl *a;
	const IVarDeclList *b;
};

//--------------------------------------------------------------------------------------

//MethodDeclList
class CMethodDeclList : public IMethodDeclList {
public:
	CMethodDeclList( const IMethodDecl *_a, const IMethodDeclList *_b ) : a( _a ), b( _b ) {};
	~CMethodDeclList() {}
	const IMethodDecl* GetTop() const { return a; }
	const IMethodDeclList* GetTail() const { return b; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IMethodDecl *a;
	const IMethodDeclList *b;
};

//--------------------------------------------------------------------------------------

//StmList
class CStmList : public IStmList {
public:
	CStmList( const IStm *_a, const IStmList *_b ) : a( _a ), b( _b ) {};
	~CStmList() {}
	const IStm* GetTop() const { return a; }
	const IStmList* GetTail() const { return b; }
	void Accept( IVisitor* visitor ) const { visitor->Visit( *this ); }
private:
	const IStm *a;
	const IStmList *b;
};