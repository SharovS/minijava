#pragma once
#include <Temp.h>
#include <Tree.h>

namespace Frame
{
	class CAccess
	{
	public:
		CAccess(){}
		virtual ~CAccess() {} 

		virtual const Tree::IExp* getVariable() const =0 {};
	};

	//--------------------------------------------------------------------------------------

	class CInReg : public CAccess 
	{
	public:
		CInReg(Temp::CTemp* _temp);
		virtual const Tree::IExp* getVariable() const;
	private:
		Temp::CTemp* temp;
	};

	//--------------------------------------------------------------------------------------

	class CInFrame : public CAccess {
	public:
		CInFrame( const Temp::CTemp* fp, int offset );

		virtual const Tree::IExp* getVariable() const;

	private:
		const Temp::CTemp* const fp;
		const int offset;
	};

	//--------------------------------------------------------------------------------------

	class CAccessList
	{
	public:
		CAccessList (const CAccess* _head, CAccessList* _tail); 
		~CAccessList(){};
		void addHead(const CAccess* _head);
		void addTail(CAccessList* _tail);
		const CAccess* getHead();
		CAccessList* getTail();
	private:
		const CAccess* head;
		CAccessList* tail;
	};

	//--------------------------------------------------------------------------------------

	class CFrame
	{
	public:
		CFrame (Temp::CLabel* _name, int _formalscount); //список имен вместо числа переменных, или аллокформал
		Temp::CLabel* getName() const;
		CAccessList* getFormals();
		Temp::CTemp* getThis();
		CAccess* allocLocal();
		Tree::IExp* externalCall(std::string func, Tree::ExpList *args);
		Temp::CTemp* FP();
		Temp::CTemp* thisValue();//
		int wordSize();
	private:
		Temp::CTemp* Pointer;
		Temp::CLabel* name;
		CAccessList* formals;
		CAccessList* locals;
		Temp::CTemp* th;//this
	};
}