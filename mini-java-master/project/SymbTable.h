#pragma once;
#include <interface.h>
#include <assert.h>

class CMethod
{
	CMetod(char* _c, char*  _name, CVar* _par, CVar* _loc, CMethod* _next)
		: c(_c), name(_name), par(_par), loc(_loc), next(_next) {};
	char* getType(){return c;};
	char* getName(){return name;};
	CVar* getPar(){return par;};
	CVar* getLoc(){return loc;};
	CMethod* getNext(){return next;};
	void addType(char* _c){c = _c;};
	void addName(char* _name){name = _name;};
	void addPar(CVar* _par){par = _par;};
	void addLoc(CVar* _loc){loc = _loc;};
	void addNext(CMethod* _next){next = _next;};
	char * findTVar()
	{
		CVar * temp=CurrMethod->addPar();
		while (temp!=0)
		{
			if (temp->getName()==id)
			{
				return temp->getType()
			}
			else 
			{
				temp=temp->getNext();
			}
		}
		temp=CurrMethod->addLoc();
		while (temp!=0)
		{
			if (temp->getName()==id)
			{
				return temp->getType()
			}
			else 
			{
				temp=temp->getNext();
			}
		}
		return 0;
	}
private:
	char* c;
	char* name;
	CVar* par;
	CVar* loc;
	CMethod* next;
}
class CVar
{
	CVar(char*  _c, char* _name, CVar* _next) c(_c), name(_name), next(_next);
	void addType(char* _c){c = _c;};
	void addName(char* _name){name = _name;};
	void addNext(CVar* _next){next = _next;};
	char* getType(){return c;};
	char* getName(){return name;};
	CVar* getNext(){return next;};
private:
	char* c;
	char* name;
	CVar* next;
}
class CClass
{
	CClass(char* _c, CVar* _var, CMethod* _meth, CClass* _next) c(_c), var(_var), meth(_meth), next(_next);
	void addName(char * _c){c = _c;};
	void addName(char* _name){name = _name;};
	void addVar(CVar * _var){var=_var;};
	void addMeth(CMethod * _meth){meth=_meth;};
	void addNext(CClass * _next){next=_next;};
	char* getName(){return c;};
	CVar* getVar(){return var;};
	CMethod* getMeth(){return meth;};
	CClass* getNext(){return next;};
	char * findTVar(char* id)
	{
		CVar * temp=CurrClass->getVar();
		while (temp!=0)
		{
			if (temp->getName()==id)
			{
				return temp->getType()
			}
			else 
			{
				temp=temp->getNext();
			}
		}
	return 0;
	}
private:
	char* c;
	IVar* var;
	IMethod* meth;
	CClass* next;
}
class CSTable
{
public:
	char* Lookup( char* id)
	{
		if (CurrClass==0)
		{
			assert(false);
		}
		else if (CurrMethod==0)
		{
			CurrClass->findTVar(id);
		}
		else
		{
			if	(CurrMethod->findTVar(id))
			{
				return CurrMethod->findTVar();
			};
			return CurrClass->findTVar(id);
		}		
	}
	void EnterClass(CClass * a){CurrClass=a;};
	void EnterMethod( CMethod * a){CurrMethod=a;};
	void LeaveClass(){CurrClass=0;};
	void LeaveMethod(){CurrMethod=0;};
	CClass * getCurrClass()
	{
		return CurrClass;
	};
	CMethod * getCurrMethod()
	{
		return CurrMethod;
	};
private:
	CClass* CurrClass;
	CMethod* CurrMethod;
	CClass* FirstClass;
}
class STVisitor : public IVisitor
{
public:

	virtual void Visit(const CProgram& p )
	{
		this->Visit(p.GetClassDeclList());
		this->Visit(p.GetMainClass());
	};
	virtual void Visit(const CMainClass& p ) = 0
	{

	};
	virtual void Visit(const CClassDecl& p ) = 0
	{
	};
	virtual void Visit(const CExClassDecl& p ) = 0
	{
	};
	void Visit(VarDecl * n)
	{
		if (CurrMethod == null)
		{
			if (!CurrClass.addVar(id, t)
		}
		else if (!CurrMethod.addVar(id, t))
	}
	virtual void Visit(const CMethodDecl& p ) = 0
	{
	};
	virtual void Visit(const CCompStm& p ) = 0
	{
		assert(false);
	};
	virtual void Visit(const CIfStm& p ) = 0	
	{
		assert(false);
	};
	virtual void Visit(const CWhStm& p ) = 0	
	{
		assert(false);
	};
	virtual void Visit(const CSOPStm& p ) = 0	
	{
		assert(false);
	}; 
	virtual void Visit(const CAsStm& p ) = 0	
	{
		assert(false);
	}; 
	virtual void Visit(const CAsExpStm& p ) = 0	
	{
		assert(false);
	}; 
	virtual void Visit(const COpExp& p ) = 0	
	{
		assert(false);
	}; 
	virtual void Visit(const CExExp& p ) = 0	
	{
		assert(false);
	}; 
	virtual void Visit(const CLenExp& p ) = 0	
	{
		assert(false);
	}; 
	virtual void Visit(const CIdClExp& p ) = 0	
	{
		assert(false);
	}; 
	virtual void Visit(const CNExp& p ) = 0	
	{
		assert(false);
	}; 
	virtual void Visit(const CTrExp& p ) = 0	
	{
		assert(false);
	};  
	virtual void Visit(const CFExp& p ) = 0	
	{
		assert(false);
	};  
	virtual void Visit(const CIdExp& p ) = 0	
	{
		assert(false);
	};  
	virtual void Visit(const CThExp& p ) = 0	
	{
		assert(false);
	};  
	virtual void Visit(const CNewIntExp& p ) = 0	
	{
		assert(false);
	};  
	virtual void Visit(const CNewIdExp& p ) = 0	
	{
		assert(false);
	}; 
	virtual void Visit(const CNotExp& p ) = 0	
	{
		assert(false);
	}; 
	virtual void Visit(const CBrExp& p ) = 0	
	{
		assert(false);
	}; 
	virtual void Visit(const CTypeD& p ) = 0	
	{
		assert(false);
	};  
/*	virtual void Visit(const CTypeMass& p ) = 0;*/ 
	virtual void Visit(const CTypeId& p ) = 0	
	{
		assert(false);
	};  
	virtual void Visit(const CExpList& p ) = 0	
	{
		assert(false);
	}; 
	virtual void Visit(const CFormalList& p ) = 0;
	virtual void Visit(const CClassDeclList& p ) = 0;
	virtual void Visit(const CVarDeclList& p ) = 0;
	virtual void Visit(const CMethodDeclList& p ) = 0;
	virtual void Visit(const CStmList& p ) = 0	
	{
		assert(false);
	}; 
private:
	CClass* CurrClass;
	CMethod* CurrMethod;
	CSTable* ST; 
}