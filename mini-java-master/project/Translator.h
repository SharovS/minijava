# pragma once
#include <Temp.h>
#include <Tree.h>
#include <interface.h>
#include <SymbolTable.h>
#include <Frame.h>
#include <BasicBlocks.h>
#include <AssemblerGenerator.h>
#include <map>

using namespace std;

namespace Translation
{
	class CProgramFragment {
	public:
		CProgramFragment() : funcFrame( 0 ), funcCode( 0 ), nextFragment( 0 ), funcCodeLinearized( 0 ) {}
		const Frame::CFrame* funcFrame;
		const Tree::IExp* funcCode;
		const Tree::StmList* funcCodeLinearized;
		const Assembler::IInstrList* assemblerCode;
		CProgramFragment* nextFragment;
	};

	//--------------------------------------------------------------------------------------

	class Exp {
	public:
		virtual ~Exp() = 0 {}
		virtual Tree::IExp* unEx() = 0;
		virtual Tree::IStm* unNx() = 0;
		virtual Tree::IStm* unCx( Temp::CLabel* t, Temp::CLabel* f ) = 0;
	};

	//--------------------------------------------------------------------------------------

	class Translator : public IVisitor {
	public:
		Translator( CSTable* _table ) : Frag( 0 ), Previous( 0 ), expListPrevious( 0 ), table( _table ), CurrFrame( 0 ) {}
		~Translator() {}

		CProgramFragment * getFragments();
		Tree::IExp* ExternalCall( Tree::NAME* _func, Tree::ExpList* _args );

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
		void Visit( const CPreUnOpExp& p );
		void Visit( const CPostUnOpExp& p );
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
		void Visit( const CExpList& p );//done
		void Visit( const CFormalList& p );//done
		void Visit( const CClassDeclList& p );//done
		void Visit( const CVarDeclList& p );//done
		void Visit( const CMethodDeclList& p );//done
		void Visit( const CStmList& p );//done
		void Visit( const CEmptyStm& p );
		void Visit( const CExpStm& p );
		bool checkClassVariable( Exp* prv, std::string name );
	private:
		CProgramFragment * Frag;
		Exp* Previous;
		Tree::ExpList* expListPrevious;
		CSTable* table;
		Frame::CFrame* CurrFrame;
		map<string, const Frame::CAccess*> variables;
		//поиск переменной в таблице возвр IExp
	};


}