#pragma once
#include <Temp.h>
#include <assert.h>

namespace Tree
{
	class CONST;
	class NAME;
	class TEMP;
	class BINOP;
	class MEM;
	class CALL;
	class ESEQ;
	class MOVE;
	class EXP;
	class JUMP;
	class CJUMP;
	class SEQ;
	class LABEL;
	class ExpList;
	class StmList;

	class ITreeVisitor {
	public:
		virtual ~ITreeVisitor() {}
		virtual void Visit( const CONST& p ) = 0;
		virtual void Visit( const NAME& p ) = 0;
		virtual void Visit( const TEMP& p ) = 0;
		virtual void Visit( const BINOP& p ) = 0;
		virtual void Visit( const MEM& p ) = 0;
		virtual void Visit( const CALL& p ) = 0;
		virtual void Visit( const ESEQ& p ) = 0;
		virtual void Visit( const MOVE& p ) = 0;
		virtual void Visit( const EXP& p ) = 0;
		virtual void Visit( const JUMP& p ) = 0;
		virtual void Visit( const CJUMP& p ) = 0;
		virtual void Visit( const SEQ& p ) = 0;
		virtual void Visit( const LABEL& p ) = 0;
		virtual void Visit( const ExpList& p ) = 0;
		virtual void Visit( const StmList& p ) = 0;
	};

	//--------------------------------------------------------------------------------------

	class IExp {
	public:
		virtual ~IExp() = 0 {};
		virtual void Accept( ITreeVisitor *v ) const
		{
			assert( false );
		}
		virtual const ExpList* Kids() const = 0;
		virtual const IExp* Build( const ExpList* ) const = 0;
	};

	//--------------------------------------------------------------------------------------

	class IStm {
	public:
		virtual ~IStm() = 0 {};
		virtual void Accept( ITreeVisitor *v ) const
		{
			assert( false );
		}
		virtual const ExpList* Kids() const = 0;
		virtual const IStm* Build( const ExpList* ) const = 0;
	};

	//--------------------------------------------------------------------------------------

	class ExpList {
	public:
		ExpList( const IExp* _top, const ExpList* _tail ) : top( _top ), tail( _tail ) {}
		~ExpList() {}
		const IExp* getTop() const
		{
			return top;
		}
		const ExpList* getTail() const
		{
			return tail;
		}
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
	private:
		const IExp* top;
		const ExpList* tail;
	};

	//--------------------------------------------------------------------------------------

	class StmList {
	public:
		StmList( const IStm* _top, const StmList* _tail ) : top( _top ), tail( _tail ) {}
		~StmList() {}
		void setTop( IStm* _top )
		{
			top = _top;
		}
		const IStm* getTop() const
		{
			return top;
		}
		void setTail( StmList* _tail )
		{
			tail = _tail;
		}
		const StmList* getTail() const
		{
			return tail;
		}
		void Accept( ITreeVisitor* visitor ) const
		{
			visitor->Visit( *this );
		}
	private:
		const IStm* top;
		const StmList* tail;
	};

	//--------------------------------------------------------------------------------------
	class BINOP : public IExp {
	public:
		enum T_Binop {
			PLUS,
			MINUS,
			MUL,
			DIV,
			AND,
			OR,
			LSHIFT,
			RSHIFT,
			ARSHIFT,
			XOR
		};
		BINOP( T_Binop _binop, const IExp* _left, const IExp* _right ) : binop( _binop ), left( _left ), right( _right ) {}
		~BINOP() {}
		virtual const ExpList* Kids() const
		{
			return new ExpList( left, new ExpList( right, 0 ) );
		}
		virtual const IExp* Build( const ExpList* kids ) const
		{
			return new BINOP( binop, kids->getTop(), kids->getTail()->getTop() );
		}
		T_Binop getBinOp() const { return binop; }
		const IExp* getLeftExp() const { return left; }
		const IExp* getRightExp() const { return right; }
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }

	private:
		T_Binop binop;
		const IExp* left;
		const IExp* right;
	};

	//--------------------------------------------------------------------------------------

	class CALL : public IExp {
	public:
		CALL( const IExp* _func, const ExpList* _args ) : func( _func ), args( _args ) {}
		~CALL() {}
		virtual const ExpList* Kids() const
		{
			return new ExpList( func, args );
		}
		virtual const IExp* Build( const ExpList* kids ) const
		{
			return new CALL( kids->getTop(), kids->getTail() );
		}
		const IExp* getFuncExp() const { return func; }
		const ExpList* getArgsExpList() const { return args; }
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
	private:
		const IExp* func;
		const ExpList* args;
	};

	//--------------------------------------------------------------------------------------

	class CONST : public  IExp {
	public:
		CONST( int _value ) : value( _value ) {}
		CONST( char* _strvalue ) : strvalue( _strvalue ) {}
		~CONST() {}
		virtual const ExpList* Kids() const
		{
			return 0;
		}
		virtual const IExp* Build( const ExpList* kids ) const
		{
			return this;
		}
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
		int getInt() const { return value; }
		char* getStr() const { return strvalue; }
		std::string toString() const
		{
			char buffer[16] = {0};
			_snprintf_s( buffer, 16, 15, "%d", value );
			return buffer;
		}
	private:
		int value;
		char* strvalue;
	};

	//--------------------------------------------------------------------------------------

	class ESEQ : public  IExp {
	public:
		ESEQ( const IStm* _stm, const IExp* _exp ) : stm( _stm ), exp( _exp ) {}
		~ESEQ() {}
		virtual const ExpList* Kids() const
		{
			printf( "Error: kids() not applicable to ESEQ" );
			assert( false );
			return 0;
		}
		virtual const IExp* Build( const ExpList* kids ) const
		{
			printf( "Error: build() not applicable to ESEQ" );
			assert( false );
			return 0;
		}
		const IStm* getStm() const { return stm; }
		const IExp* getExp() const { return exp; }
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
	private:
		const IStm* stm;
		const IExp* exp;
	};

	//--------------------------------------------------------------------------------------

	class MEM : public  IExp {
	public:
		MEM( const IExp* _exp ) : exp( _exp ) {}
		~MEM() {}
		virtual const ExpList* Kids() const
		{
			return new ExpList( exp, 0 );
		}
		virtual const IExp* Build( const ExpList* kids ) const
		{
			return new MEM( kids->getTop() );
		}
		const IExp* getExp() const { return exp; }
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
	private:
		const IExp* exp;
	};

	//--------------------------------------------------------------------------------------

	class NAME : public  IExp {
	public:
		NAME( const Temp::CLabel* _label ) : label( _label ) {}
		~NAME() {}
		virtual const ExpList* Kids() const
		{
			return 0;
		}
		virtual const IExp* Build( const ExpList* kids ) const
		{
			return this;
		}
		const Temp::CLabel* getLabel() const
		{
			return label;
		}
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
	private:
		const Temp::CLabel* label;
	};

	//--------------------------------------------------------------------------------------

	class TEMP : public  IExp {
	public:
		TEMP( const Temp::CTemp* _temp ) : temp( _temp ) {}
		~TEMP() {}
		virtual const ExpList* Kids() const
		{
			return 0;
		}
		virtual const IExp* Build( const ExpList* kids ) const
		{
			return this;
		}
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
		const Temp::CTemp* getTemp() const { return temp; }
	private:
		const Temp::CTemp* temp;
	};

	//--------------------------------------------------------------------------------------

	class CJUMP : public IStm {
	public:
		enum T_Cjump {
			EQ, NE, LT,
			GT, LE, GE,
			ULT, ULE,
			UGT, UGE
		};
		CJUMP( T_Cjump _relop, const IExp* _left, const IExp* _right,
			const Temp::CLabel* _iftrue, const Temp::CLabel* _iffalse ) :
			relop( _relop ), left( _left ), right( _right ),
			iftrue( _iftrue ), iffalse( _iffalse )
		{}
		~CJUMP() {}
		virtual const ExpList* Kids() const
		{
			return new ExpList( left, new ExpList( right, 0 ) );
		}
		virtual const IStm* Build( const ExpList* kids ) const
		{
			return new CJUMP( relop, kids->getTop(), kids->getTail()->getTop(), iftrue, iffalse );
		}

		T_Cjump getRelOp() const { return relop; }

		static T_Cjump reverseRelOp( T_Cjump relop )
		{
			switch( relop ) {
				case EQ:  return NE;
				case NE:  return EQ;
				case LT:  return GE;
				case GE:  return LT;
				case GT:  return LE;
				case LE:  return GT;
				case ULT: return UGE;
				case UGE: return ULT;
				case UGT: return ULE;
				case ULE: return UGT;
				default:
					assert( false );
					return NE;
			}
		}
		const IExp* getLeftExp() const { return left; }
		const IExp* getRightExp() const { return right; }
		const Temp::CLabel* getTrueLabel() const { return iftrue; }
		const Temp::CLabel* getFalseLabel() const { return iffalse; }
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
	private:
		T_Cjump relop;
		const IExp* left;
		const IExp* right;
		const Temp::CLabel* iftrue;
		const Temp::CLabel* iffalse;
	};

	//--------------------------------------------------------------------------------------

	class EXP : public  IStm {
	public:
		EXP( const IExp* _exp ) : exp( _exp ) {}
		~EXP() {}
		virtual const ExpList* Kids() const
		{
			return new ExpList( exp, 0 );
		}
		virtual const IStm* Build( const ExpList* kids ) const
		{
			return new EXP( kids->getTop() );
		}
		const IExp* getExp() const { return exp; }
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
	private:
		const IExp* exp;
	};

	//--------------------------------------------------------------------------------------

	class JUMP : public  IStm {
	public:
		JUMP( const IExp* _exp, const Temp::CLabelList* _targets ) : exp( _exp ), targets( _targets ) {}
		explicit JUMP( const Temp::CLabel* _target ) :
			exp( new NAME( _target ) ), targets( new Temp::CLabelList( _target, 0 ) )
		{}
		~JUMP() {}
		virtual const ExpList* Kids() const
		{
			return new ExpList( exp, 0 );
		}
		virtual const IStm* Build( const ExpList* kids ) const
		{
			return new JUMP( kids->getTop(), targets );
		}
		const Temp::CLabelList* getTgList() const { return targets; }
		const IExp* getExp() const { return exp; }
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
	private:
		const IExp* exp;
		const Temp::CLabelList* targets;
	};

	//--------------------------------------------------------------------------------------

	class LABEL : public  IStm {
	public:
		LABEL( const Temp::CLabel* _label ) : label( _label ) {}
		~LABEL() {}
		virtual const ExpList* Kids() const
		{
			return 0;
		}
		virtual const IStm* Build( const ExpList* kids ) const
		{
			return this;
		}
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
		const Temp::CLabel* getLabel() const { return label; }
	private:
		const Temp::CLabel* label;
	};

	//--------------------------------------------------------------------------------------

	class MOVE : public  IStm {
	public:
		MOVE( const IExp* _dst, const IExp* _src ) : dst( _dst ), src( _src )
		{
			if( dynamic_cast<const MEM*>(_dst) == 0 && dynamic_cast<const TEMP*>(_dst) == 0 ) {
				assert( false );
			}
		}
		~MOVE() {}
		virtual const ExpList* Kids() const
		{
			if( dynamic_cast<const MEM*>(dst) != 0 ) {
				return new ExpList( dynamic_cast<const MEM*>(dst)->getExp(), new ExpList( src, 0 ) );
			} else {
				return new ExpList( src, 0 );
			}
		}
		virtual const IStm* Build( const ExpList* kids ) const
		{
			if( dynamic_cast<const MEM*>(dst) ) {
				return new MOVE( new MEM( kids->getTop() ), kids->getTail()->getTop() );
			} else {
				return new MOVE( dst, kids->getTop() );
			}
		}
		const IExp* getDst() const { return dst; }
		const IExp* getSrc() const { return src; }
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
	private:
		const IExp* dst;
		const IExp* src;
	};

	//--------------------------------------------------------------------------------------

	class SEQ : public  IStm {
	public:
		SEQ( IStm* _left, IStm* _right ) : left( _left ), right( _right ) {}
		SEQ( const IStm* _left, const IStm* _right ) : left( _left ), right( _right ) {}
		~SEQ() {}
		virtual const ExpList* Kids() const
		{
			printf( "Error: kids() not applicable to SEQ" );
			assert( false );
			return 0;
		}
		virtual const IStm* Build( const ExpList* kids ) const
		{
			printf( "Error: build() not applicable to SEQ" );
			assert( false );
			return 0;
		}
		const IStm* getLeftStm() const { return left; }
		const IStm* getRightStm() const { return right; }
		void Accept( ITreeVisitor* visitor ) const { visitor->Visit( *this ); }
	private:
		const IStm* left;
		const IStm* right;
	};
}