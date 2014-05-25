#pragma once
#include <string>
#include <sstream>
#include <Temp.h>
using namespace std;

namespace Assembler
{
	class CTargets {
	public:
		CTargets( const Temp::CLabelList* _labels ) : labels( _labels ) {}
		const Temp::CLabelList* getLabels() { return labels; };
	private:
		const Temp::CLabelList* labels;
	};

	//--------------------------------------------------------------------------------------

	class IInstr {
	public:
		virtual const Temp::CTempList* use() const = 0;
		virtual const Temp::CTempList* def() const = 0;
		virtual const CTargets* jumps() const = 0;
		virtual string format( const Temp::CTempMap m ) const = 0;
	};

	//--------------------------------------------------------------------------------------

	class IInstrList {
	public:
		IInstrList( const IInstr* _head, const IInstrList* _tail ) : head( _head ), tail( _tail ) {}
		const IInstr* getTop() const { return head; }
		const IInstrList* getTail() const { return tail; }
		void setTail( IInstrList* newTail ) { tail = newTail; }
	private:
		const IInstr* head;
		const IInstrList* tail;
	};

	//--------------------------------------------------------------------------------------

	class OPER : public IInstr {
	public:
		OPER( string _assem, const Temp::CTempList* _dst, const Temp::CTempList* _src ) :
			assem( _assem ), dst( _dst ), src( _src ), jump( 0 ) {}
		OPER( string _assem, const Temp::CTempList* _dst, const Temp::CTempList* _src,
			const Temp::CLabelList* _jump ) :
			assem( _assem ), dst( _dst ), src( _src ), jump( _jump )
		{}
		std::string getAssem() const { return assem; }
		const Temp::CTempList* getDst() { return dst; }
		const Temp::CTempList* getSrc() { return src; }
		const Temp::CLabelList* getJump() const { return jump; }
		virtual const Temp::CTempList* use() const { return src; }
		virtual const Temp::CTempList* def() const { return dst; }
		virtual const CTargets* jumps() const { return new CTargets( jump ); }
		virtual string format( const Temp::CTempMap m ) const;
	private:
		string assem;
		const Temp::CTempList* dst;
		const Temp::CTempList* src;
		const Temp::CLabelList* jump;
	};

	//--------------------------------------------------------------------------------------

	class MOVE : public IInstr {
	public:
		MOVE( string _assem, const Temp::CTemp* _dst, const Temp::CTemp* _src ) :
			assem( _assem ), dst_src( new Temp::CTempList( _dst, new Temp::CTempList( _src, 0 ) ) )
		{}
		string getAssem() const { return assem; };
		const Temp::CTempList* getDstSrc() { return dst_src; };
		virtual const Temp::CTempList* use() const { return dst_src->getTail(); }
		virtual const Temp::CTempList* def() const { return new Temp::CTempList( dst_src->getTop(), 0 ); }
		virtual const CTargets* jumps() const { return 0; }
		virtual string format( const Temp::CTempMap m ) const;
	private:
		string assem;
		const Temp::CTempList* dst_src;
	};

	//--------------------------------------------------------------------------------------

	class LABEL : public IInstr {
	public:
		LABEL( const string _assem, const Temp::CLabel* _lable ) : assem( _assem ), lable( _lable ) {}
		string getAssem() const { return assem; }
		const Temp::CLabel* getLable() { return lable; }
		virtual const Temp::CTempList* use() const { return 0; }
		virtual const Temp::CTempList* def() const { return 0; }
		virtual const CTargets* jumps() const { return 0; }
		virtual string format( const Temp::CTempMap m ) const;
	private:
		const string assem;
		const Temp::CLabel* lable;
	};
}