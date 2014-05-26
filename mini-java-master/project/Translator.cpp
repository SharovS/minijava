#pragma once

#include <Translator.h>
#include <Temp.h>
#include <Tree.h>
#include <Frame.h>
#include <SymbolTable.h>

using namespace Frame;

namespace Translation
{

	class Ex : public Translation::Exp {
	public:
		Ex( const Tree::IExp* _exp ) : exp( _exp ) {}
		~Ex() {}

		virtual Tree::IExp* unEx()
		{
			return const_cast<Tree::IExp*>(exp);
		}
		virtual Tree::IStm* unNx()
		{
			return new Tree::EXP( exp );
		}
		virtual Tree::IStm* unCx( Temp::CLabel* t, Temp::CLabel* f )
		{
			return new Tree::CJUMP( Tree::CJUMP::NE, exp, new Tree::CONST( 0 ), t, f );
		}

	private:
		const Tree::IExp* exp;

	};

	class Nx : public Translation::Exp//done
	{
	public:
		Nx( Tree::IStm* _stm ) : stm( _stm ) {}
		~Nx() {}
		virtual Tree::IStm* unNx()
		{
			return stm;
		}
		virtual Tree::IStm* unCx( Temp::CLabel* t, Temp::CLabel* f )
		{
			assert( false );
			return 0;
		}
		virtual Tree::IExp* unEx()
		{
			assert( false );
			return 0;
		}
	private:
		Tree::IStm* stm;
	};

	class Cx : public Translation::Exp {
	public:
		Cx() {}
		virtual Tree::IExp* unEx()
		{
			Temp::CTemp* r = new Temp::CTemp();
			Temp::CLabel* t = new Temp::CLabel();
			Temp::CLabel* f = new Temp::CLabel();
			Temp::CLabel* end = new Temp::CLabel();
			Tree::IStm* trueRoute = new Tree::SEQ( new Tree::LABEL( t ),
				new Tree::SEQ( new Tree::MOVE( new Tree::TEMP( r ), new Tree::CONST( 1 ) ),
				new Tree::JUMP( end ) ) );
			Tree::IStm* falseRoute = new Tree::SEQ( new Tree::LABEL( f ),
				new Tree::SEQ( new Tree::MOVE( new Tree::TEMP( r ), new Tree::CONST( 0 ) ),
				new Tree::LABEL( end ) ) );

			return new Tree::ESEQ( new Tree::SEQ( unCx( t, f ), new Tree::SEQ( trueRoute, falseRoute ) ),
				new Tree::TEMP( r ) );

		}

		virtual Tree::IStm* unNx()
		{
			// ��-���� �� �����������
			assert( false );
			Temp::CLabel* fake = new Temp::CLabel();
			return new Tree::SEQ( unCx( fake, fake ), new Tree::LABEL( fake ) );
		}
		virtual Tree::IStm* unCx( Temp::CLabel* t, Temp::CLabel* f ) = 0;//still abstract
	};

	class CArifmCx : public Cx {
	public:
		CArifmCx( CBinop _op, Tree::IExp* _exp1, Tree::IExp* _exp2 ) : op( _op ), exp1( _exp1 ), exp2( _exp2 ) {}
		virtual Tree::IStm* unCx( Temp::CLabel* t, Temp::CLabel* f )
		{
			switch( op ) {
				case B_Less:
					return new Tree::CJUMP( Tree::CJUMP::LT, exp1, exp2, t, f );
				default:
					// ������ Less, ������ �������!!!
					assert( false );
					return 0;
			}
		}
	private:
		CBinop op;
		Tree::IExp* exp1, *exp2;
	};

	class CLogicCx : public Cx {
	public:
		CLogicCx( CBinop _op, Tree::IExp* _exp1, Tree::IExp* _exp2 ) : op( _op ), exp1( _exp1 ), exp2( _exp2 ) {}
		virtual Tree::IStm* unCx( Temp::CLabel* t, Temp::CLabel* f )
		{
			Temp::CLabel* exp2Label;
			switch( op ) {
				case B_And:
					exp2Label = new Temp::CLabel();
					return new Tree::SEQ( new Tree::CJUMP( Tree::CJUMP::NE, exp1, new Tree::CONST( 0 ), exp2Label, f ),
						new Tree::SEQ( new Tree::LABEL( exp2Label ),
						new Tree::CJUMP( Tree::CJUMP::NE, exp2, new Tree::CONST( 0 ), t, f ) ) );
				default:
					// ������ ���������� ��������(And), ������ �������!!!
					assert( false );
					return 0;
			}
		}
	private:
		CBinop op;
		Tree::IExp* exp1, *exp2;
	};

	class CNotOpCx : public Cx {
	public:
		CNotOpCx( Tree::IExp* _exp ) : exp( _exp ) {}
		virtual Tree::IStm* unCx( Temp::CLabel* t, Temp::CLabel* f )
		{
			return new Tree::CJUMP( Tree::CJUMP::EQ, exp, new Tree::CONST( 0 ), t, f );
		}
	private:
		Tree::IExp* exp;
	};

	CProgramFragment * Translator::getFragments()
	{
		return Frag;
	}
	Tree::IExp* Translator::ExternalCall( Tree::NAME* _func, Tree::ExpList* _args )
	{
		return new Tree::CALL( _func, _args );
	}

	void Translator::Visit( const CProgram& p ) //MainClass ClassDeclList
	{
		p.GetMainClass()->Accept( this );
		p.GetClassDeclList()->Accept( this );
	}

	void Translator::Visit( const CMainClass& p ) //class id { public static void main ( String [] id ) { Statement }}
	{
		table->EnterClass( table->FindClass( p.GetIdFirst() ) );
		CFrame * MainClass = new CFrame( new Temp::CLabel( "main" ), 0 );
		CurrFrame = MainClass;

		Tree::IStm* bodyStm = 0;
		p.GetStm()->Accept( this );
		bodyStm = Previous->unNx();

		table->LeaveClass();
		//______________________________________________________________________________________

		CProgramFragment* TempFrag = new CProgramFragment();
		TempFrag->funcFrame = CurrFrame;
		TempFrag->funcCode = new Tree::ESEQ( bodyStm, new Tree::CONST( 0 ) );//??????????????
		TempFrag->nextFragment = Frag;
		Frag = TempFrag;
		CurrFrame = 0;

	}
	void Translator::Visit( const CClassDecl& p ) //class id { VarDeclList MethodDeclList }
	{
		table->EnterClass( table->FindClass( p.GetId() ) );
		//p.GetVarDeclList()->Accept(this);//  ���� �����������!!!!!!!
		p.GetMethodDeclList()->Accept( this );

		table->LeaveClass();
	}
	void Translator::Visit( const CExClassDecl& p ) //class id extends id { VarDeclList MethodDeclList }
	{
		table->EnterClass( table->FindClass( p.GetId() ) );
		//p.GetVarDeclList()->Accept(this);// ���� �����������!!!!!!!
		p.GetMethodDeclList()->Accept( this );

		table->LeaveClass();
	}
	void Translator::Visit( const CVarDecl& p ) //Type id
	{
		variables.insert( make_pair( p.GetId(), CurrFrame->allocLocal() ) );
	}
	void Translator::Visit( const CMethodDecl& p ) //public Type id ( FormalList ) { VarDecl* Statement* return Exp ;}
	{
		map<string, const Frame::CAccess*> variablesCopy( variables );
		CMethod* currentMethod = (table->getCurrClass())->FindMethod( p.GetId(), table );
		table->EnterMethod( currentMethod );

		string methodName = table->getCurrClass()->getName() + currentMethod->getName();// ��� ������ � ��� ������ �� ���� � ���-�� ���������?!
		CVar* formalsList = currentMethod->getPar();
		CurrFrame = new CFrame( new Temp::CLabel( methodName ),
			formalsList != 0 ? formalsList->Length() : 0 );
		//p.GetFormalList()->Accept(this);
		// ��������� ���������� ��������� ������ � ���������� �� Frame
		CVar* tbVariable = formalsList;
		Frame::CAccessList* frameVariable = CurrFrame->getFormals();
		while( tbVariable != 0 && frameVariable != 0 ) {
			variables.insert( make_pair( tbVariable->getName(), frameVariable->getHead() ) );

			tbVariable = tbVariable->getNext();
			frameVariable = frameVariable->getTail();

		}
		assert( tbVariable == 0 && frameVariable == 0 );

		if( p.GetVarDeclList() != 0 ) {
			p.GetVarDeclList()->Accept( this );
		}
		const Tree::IStm* bodyStm = 0;
		if( p.GetStmList() != 0 ) {
			p.GetStmList()->Accept( this );
			bodyStm = Previous->unNx();
		} else {
			bodyStm = new Tree::EXP( new Tree::CONST( 0 ) );
		}
		p.GetExp()->Accept( this );
		const Tree::IExp* retExp = Previous->unEx();
		table->LeaveMethod();

		CProgramFragment* TempFrag = new CProgramFragment();
		TempFrag->funcFrame = CurrFrame;
		TempFrag->funcCode = new Tree::ESEQ( bodyStm, retExp );
		TempFrag->nextFragment = Frag;
		Frag = TempFrag;
		CurrFrame = 0;
		variables = variablesCopy;//����� �� ���?????????????????????

	}
	void Translator::Visit( const CCompStm& p )  //{ Statement* }
	{
		// ������ ���� ������, ��������� statement
		p.GetStmList()->Accept( this );
	}
	void Translator::Visit( const CIfStm& p ) //if ( Exp ) Statement else Statement
	{
		// ��������� exp � statement
		p.GetExp()->Accept( this );
		Exp* condExp = Previous;
		p.GetStmFirst()->Accept( this );
		Exp* trueExp = Previous;
		p.GetlStmSecond()->Accept( this );
		Exp* falseExp = Previous;
		// ������� ����� true, false � end
		Temp::CLabel* t = new Temp::CLabel();
		Temp::CLabel* f = new Temp::CLabel();
		Temp::CLabel* end = new Temp::CLabel();
		// ������� ����� true � false
		Tree::IStm* trueSeq = new Tree::SEQ( new Tree::LABEL( t ), trueExp->unNx() );
		Tree::IStm* falseSeq = new Tree::SEQ( new Tree::LABEL( f ), falseExp->unNx() );
		// ��������� �������� �������
		Tree::IStm* res = new Tree::SEQ( condExp->unCx( t, f ),
			new Tree::SEQ( new Tree::SEQ( trueSeq,
			new Tree::JUMP( end ) ),
			new Tree::SEQ( falseSeq,
			new Tree::LABEL( end ) ) ) );
		// ���������� ������� statement
		Previous = new Nx( res );
	}
	void Translator::Visit( const CWhStm& p ) //while ( Exp ) Statement
	{
		// ��������� ��������� 
		p.GetExp()->Accept( this );
		Exp* condExp = Previous;
		p.GetStm()->Accept( this );
		Exp* actExp = Previous;
		// ������� ����� start, action � end
		Temp::CLabel * start = new Temp::CLabel();
		Temp::CLabel * action = new Temp::CLabel();
		Temp::CLabel * end = new Temp::CLabel();
		// ������� ����� action
		Tree::IStm* actionSeq = new Tree::SEQ( new Tree::LABEL( action ), actExp->unNx() );
		// ��������� �������� �������
		Tree::IStm* res = new Tree::SEQ( new Tree::SEQ( new Tree::LABEL( start ),
			condExp->unCx( action, end ) ),
			new Tree::SEQ( actionSeq,
			new Tree::SEQ( new Tree::JUMP( start ),
			new Tree::LABEL( end ) ) ) );
		// ���������� ������� statement
		Previous = new Nx( res );

	}

	void Translator::Visit( const CForStm& p ) //for ( Statement, Exp, Statement ) Statement
	{
		// ��������� ��������� 
		p.GetInitStm()->Accept( this );
		Exp* initStm = Previous;
		p.GetCheckExp()->Accept( this );
		Exp* checkExp = Previous;
		p.GetUpdateStm()->Accept( this );
		Exp* updateStm = Previous;
		p.GetBodyStm()->Accept( this );
		Exp* bodyStm = Previous;
		// ������� ����� body � end
		Temp::CLabel * body = new Temp::CLabel();
		Temp::CLabel * end = new Temp::CLabel();
		// ������� ����� body
		Tree::IStm* bodySeq = new Tree::SEQ( 
			new Tree::LABEL( body ), 
			new Tree::SEQ(
				bodyStm->unNx(),
				updateStm->unNx()
			)
		);
		Tree::IStm* res = new Tree::SEQ( 
			initStm->unNx(),
			new Tree::SEQ(
				new Tree::SEQ( 
					checkExp->unCx( body, end ),
					bodySeq
				),
				new Tree::SEQ( 
					checkExp->unCx( body, end ),
					new Tree::LABEL(end)
				)
			)
		);
		// ���������� ������� statement
		Previous = new Nx( res );
	}

	void Translator::Visit( const CSOPStm& p ) //System.out.println ( Exp ) ;
	{
		p.GetExp()->Accept( this );
		// system.out.println - ��� ���������� ������� �������
		Temp::CLabel* systemOutPrintln = new Temp::CLabel( "System.out.println" );
		// �������� ������� � ���������� Exp
		Tree::IStm* call = new Tree::EXP( ExternalCall( new Tree::NAME( systemOutPrintln ), new Tree::ExpList( Previous->unEx(), 0 ) ) );
		// ���������� ������� statement
		Previous = new Nx( call );
	}

	void Translator::Visit( const CVarDeclExp& p ) {
		variables.insert( make_pair( p.GetId(), CurrFrame->allocLocal() ) );
		Visit( *p.GetAsStm() );
	}

	void Translator::Visit( const CAsStm& p ) //id = Exp ;
	{
		// ���������, ��� ���� ����� ����������
		//assert(variables.find(p.GetId()) != variables.end());
		//// ��������� ����������, ������� � ������
		//const Tree::IExp* id = variables[p.GetId()]->getVariable();
		//p.GetExp()->Accept(this);
		//// ���������� �������� � ���������� � ���������� statement
		//Previous = new Nx( new Tree::MOVE(id, Previous->unEx()) );

		// ���������, ��� ���� ����� ����������
		int offset( 0 );
		if( variables.find( p.GetId() ) != variables.end() ) {
			// ��������� ����������
			const Tree::IExp* id = variables[p.GetId()]->getVariable();
			p.GetExp()->Accept( this );
			// ���������� �������� � ���������� � ���������� statement
			Previous = new Nx( new Tree::MOVE( id, Previous->unEx() ) );
		} else if( table->getCurrClass()->lookUpVarOffset( p.GetId(), table, offset ) ) {
			p.GetExp()->Accept( this );
			const Tree::IExp* id = new Tree::MEM( new Tree::BINOP( Tree::BINOP::PLUS, new Tree::TEMP( CurrFrame->getThis() ),
				new Tree::BINOP( Tree::BINOP::MUL, new Tree::CONST( CurrFrame->wordSize() ), new Tree::CONST( offset ) ) ) );

			Previous = new Nx( new Tree::MOVE( id, Previous->unEx() ) );
		} else // ���������� ������ ���!
		{
			assert( false );
		}

	}

	void Translator::Visit( const CAsExpStm& p ) //id [ Exp ] = Exp
	{
		//// ���������, ��� ���� ����� ����������
		//assert(variables.find(p.GetId()) != variables.end());
		//// ��������� ����������, ������� � ������
		//const Tree::IExp* id = variables[p.GetId()]->getVariable();
		//// ��������� ������ exp
		//p.GetExpFirst()->Accept(this);
		//// ������� �� �� n+1 ������� (������, ��� id[0] - ������ �������
		//id = new Tree::BINOP(Tree::BINOP::PLUS,
		//					 id,
		//					 new Tree::BINOP(Tree::BINOP::MUL,
		//									 new Tree::BINOP(Tree::BINOP::PLUS, Previous->unEx(), new Tree::CONST(1)),
		//									 new Tree::CONST(sizeof(int))));
		//p.GetExpSecond()->Accept(this);
		//// ���������� �������� � ���������� � ���������� statement
		//Previous = new Nx( new Tree::MOVE(id, Previous->unEx()) );

		//------------------------------------ ����� ��������!!!!!!!!!!!!
		int offset( 0 );

		// ���������, ��� ���� ����� ����������
		if( variables.find( p.GetId() ) != variables.end() ) {
			// ��������� ����������
			const Tree::IExp* id = variables[p.GetId()]->getVariable();
			// ��������� ������ exp
			p.GetExpFirst()->Accept( this );
			// ������� �� �� n+1 ������� (������, ��� id[0] - ������ �������
			id = new Tree::MEM( new Tree::BINOP( Tree::BINOP::PLUS,
				id,
				new Tree::BINOP( Tree::BINOP::MUL,
				new Tree::BINOP( Tree::BINOP::PLUS, Previous->unEx(), new Tree::CONST( 1 ) ),
				new Tree::CONST( sizeof( int ) ) ) ) );
			p.GetExpSecond()->Accept( this );
			// ���������� �������� � ���������� � ���������� statement
			Previous = new Nx( new Tree::MOVE( id, Previous->unEx() ) );
		} else if( table->getCurrClass()->lookUpVarOffset( p.GetId(), table, offset ) ) {


			// ��������� ������ exp
			p.GetExpFirst()->Accept( this );
			// ������� �� �� n+1 ������� (������, ��� id[0] - ������ �������
			const Tree::IExp* id = new Tree::MEM( new Tree::BINOP( Tree::BINOP::PLUS, new Tree::TEMP( CurrFrame->getThis() ),
				new Tree::BINOP( Tree::BINOP::MUL, new Tree::CONST( CurrFrame->wordSize() ), new Tree::CONST( offset ) ) ) );

			p.GetExpSecond()->Accept( this );
			// ���������� �������� � ���������� � ���������� statement
			Previous = new Nx( new Tree::MOVE( id, Previous->unEx() ) );
			/*Previous = new Ex(new Tree::MEM(
				new Tree::BINOP(Tree::BINOP::PLUS,new Tree::TEMP(CurrFrame->getThis()),
				new Tree::BINOP(Tree::BINOP::MUL, new Tree::CONST(CurrFrame->wordSize()), new Tree::CONST(offset)))));*/
		} else // ���������� ������ ���!
		{
			assert( false );
		}

	}

	void Translator::Visit( const COpExp& p ) //Exp op Exp
	{
		// ��������� ��� exp
		p.GetExpFirst()->Accept( this );
		Tree::IExp* firstExp = Previous->unEx();
		p.GetExpSecond()->Accept( this );
		Tree::IExp* secondExp = Previous->unEx();
		// ������������ ������ ��� �������� �������� � ���������� exp
		switch( p.GetOp() ) {
			case B_And:
				Previous = new CLogicCx( B_And, firstExp, secondExp );
				break;
			case B_Less:
				Previous = new CArifmCx( B_Less, firstExp, secondExp );
				break;
			case B_Div:
				Previous = new Ex( new Tree::BINOP( Tree::BINOP::DIV, firstExp, secondExp ) );
				break;
			case B_Mult:
				Previous = new Ex( new Tree::BINOP( Tree::BINOP::MUL, firstExp, secondExp ) );
				break;
			case B_Plus:
				Previous = new Ex( new Tree::BINOP( Tree::BINOP::PLUS, firstExp, secondExp ) );
				break;
			case B_Minus:
				Previous = new Ex( new Tree::BINOP( Tree::BINOP::MINUS, firstExp, secondExp ) );
				break;
		}

	}

	void Translator::Visit( const CPreUnOpExp& p ) //++id, --id
	{
		// ���������, ��� ���� ����� ����������
		int offset( 0 );
		if( variables.find( p.GetId() ) != variables.end() ) {
			// ��������� ����������
			const Tree::IExp* id = variables[p.GetId()]->getVariable();
			// ���������� �������� � ���������� � ����������
			Previous = new Ex( new Tree::ESEQ(
				new Tree::MOVE( id, new Tree::BINOP(Tree::BINOP::PLUS, id, new Tree::CONST(p.GetValue()) )),
				id
			));
		} else if( table->getCurrClass()->lookUpVarOffset( p.GetId(), table, offset ) ) {
			// ��������� ����������
			const Tree::IExp* id = new Tree::MEM( new Tree::BINOP( Tree::BINOP::PLUS, new Tree::TEMP( CurrFrame->getThis() ),
				new Tree::BINOP( Tree::BINOP::MUL, new Tree::CONST( CurrFrame->wordSize() ), new Tree::CONST( offset ) ) ) );

			Previous = new Ex( new Tree::ESEQ(
				new Tree::MOVE( id, new Tree::BINOP(Tree::BINOP::PLUS, id, new Tree::CONST(p.GetValue()) )),
				id
			));
		} else // ���������� ������ ���!
		{
			assert( false );
		}
	}

	void Translator::Visit( const CPostUnOpExp& p ) //id++, id--
	{
		// ���������, ��� ���� ����� ����������
		int offset( 0 );
		if( variables.find( p.GetId() ) != variables.end() ) {
			// ��������� ����������
			const Tree::IExp* id = variables[p.GetId()]->getVariable();
			//������� ��������� � �������� � ���
			Tree::IExp* temp = new Tree::TEMP( new Temp::CTemp );
			Tree::IStm* copy = new Tree::MOVE( temp, new Tree::MEM( id ) );
			// ���������� �������� � ���������� � ���������� ���������
			Previous = new Ex( new Tree::ESEQ(
				new Tree::SEQ(
					copy,
					new Tree::MOVE( id, new Tree::BINOP(Tree::BINOP::PLUS, id, new Tree::CONST(p.GetValue()) ))
				),
				temp
			));
		} else if( table->getCurrClass()->lookUpVarOffset( p.GetId(), table, offset ) ) {
			// ��������� ����������
			const Tree::IExp* id = new Tree::MEM( new Tree::BINOP( Tree::BINOP::PLUS, new Tree::TEMP( CurrFrame->getThis() ),
				new Tree::BINOP( Tree::BINOP::MUL, new Tree::CONST( CurrFrame->wordSize() ), new Tree::CONST( offset ) ) ) );

			//������� ��������� � �������� � ���
			Tree::IExp* temp = new Tree::TEMP( new Temp::CTemp );
			Tree::IStm* copy = new Tree::MOVE( temp, new Tree::MEM( id ) );
			// ���������� �������� � ���������� � ���������� ���������
			Previous = new Ex( new Tree::ESEQ(
				new Tree::SEQ(
					copy,
					new Tree::MOVE( id, new Tree::BINOP(Tree::BINOP::PLUS, id, new Tree::CONST(p.GetValue()) ))
				),
				temp
			));
		} else // ���������� ������ ���!
		{
			assert( false );
		}
	}

	void Translator::Visit( const CExExp& p )//Exp [ Exp ]
	{
		// ��������� ��� exp
		p.GetExpSecondn()->Accept( this );
		Exp* exSecond( Previous );
		p.GetExpFirst()->Accept( this );
		// ������� ����� �� ������ n+1, �.�. �� 0 ����� ������ �������
		Tree::IExp* res = new Tree::MEM(
			new Tree::BINOP( Tree::BINOP::PLUS,
			Previous->unEx(),
			new Tree::BINOP( Tree::BINOP::MUL,
			new Tree::BINOP( Tree::BINOP::PLUS, exSecond->unEx(), new Tree::CONST( 1 ) ),
			new Tree::CONST( sizeof( int ) ) ) ) );
		// ���������� exp
		Previous = new Ex( res );

	}

	void Translator::Visit( const CLenExp& p )//Exp . length
	{
		// ��������� exp
		p.GetExp()->Accept( this );
		// ������� ��������� ����������
		Tree::IExp* temp = new Tree::TEMP( new Temp::CTemp );
		// �������� ���� ������
		Tree::IStm* copy = new Tree::MOVE( temp, new Tree::MEM( Previous->unEx() ) );
		// ���������� exp
		Previous = new Ex( new Tree::ESEQ( copy, temp ) );
	}

	void Translator::Visit( const CIdClExp& p )//Exp . id ( ExpList )  
	{
		//��������� ������ ���� ����������
		Tree::ExpList* elTemp( expListPrevious );
		// �������� �����
		expListPrevious = 0;
		// ��������� ���������� ������, ��� ����� ��������
		p.GetExp()->Accept( this );
		// ������ � ������ ���������� �� this 
		expListPrevious = new Tree::ExpList( Previous->unEx(), expListPrevious );
		// ��������� ���������� �����������
		if( p.GetExpList() != 0 ) {
			p.GetExpList()->Accept( this );
		}
		// �������� ������� � ������ id � ������� ���������� expListPrevious
		Tree::IExp* res = new Tree::CALL( new Tree::NAME( new Temp::CLabel( p.GetId() ) ), expListPrevious );
		// ��������������� ������ ������ ����������
		expListPrevious = elTemp;
		// ���������� exp
		Previous = new Ex( res );
	}

	void Translator::Visit( const CNExp& p ) //num
	{
		// ��������� ��������� 
		Tree::IExp* res = new Tree::CONST( p.GetNum() );
		// ���������� exp
		Previous = new Ex( res );
	}

	void Translator::Visit( const CStrExp& p ) //str
	{
		Temp::CLabel* stringLabel = new Temp::CLabel("L" + p.GetId() );
		Tree::IExp* length = new Tree::CONST( p.GetStr().length() );
		Tree::IExp* res = new Tree::NAME( stringLabel ); /* ExternalCall( new Tree::NAME( stringLabel ), new Tree::ExpList( length, 0 ) );*/
		// ���������� exp
		//Previous = new Ex( res/*new Tree::ESEQ(res, length)*/ );
		Previous = new Ex(res);
	}

	void Translator::Visit( const CTrExp& p ) //true
	{
		// ��������� true ���������� 1
		Tree::IExp* res = new Tree::CONST( 1 );
		// ���������� exp
		Previous = new Ex( res );
	}

	void Translator::Visit( const CFExp& p ) //false
	{
		// ��������� false ���������� 0
		Tree::IExp* res = new Tree::CONST( 0 );
		// ���������� exp
		Previous = new Ex( res );
	}

	void Translator::Visit( const CIdExp& p )  //id
	{
		int offset( 0 );

		// ���������, ��� ���� ����� ����������
		if( variables.find( p.GetId() ) != variables.end() ) {
			// ��������� ����������
			const Tree::IExp* id = variables[p.GetId()]->getVariable();
			// ���������� exp
			Previous = new Ex( id );
		} else if( table->getCurrClass()->lookUpVarOffset( p.GetId(), table, offset ) ) {
			Previous = new Ex( new Tree::MEM(
				new Tree::BINOP( Tree::BINOP::PLUS, new Tree::TEMP( CurrFrame->getThis() ),
				new Tree::BINOP( Tree::BINOP::MUL, new Tree::CONST( CurrFrame->wordSize() ), new Tree::CONST( offset ) ) ) ) );
		} else // ���������� ������ ���!
		{
			assert( false );
		}

	}

	//bool Translator::checkClassVariable(Translation::Exp *prv, std::string name)
	//{
	//	bool res(false);
	//	int ofset(0);
	//	if(variables.find(name) != variables.end())
	//	{
	//		// ��������� ����������
	//		const Tree::IExp* id = variables[name]->getVariable();
	//		// ���������� exp
	//		prv = new Ex(id);	
	//		res = true;
	//	}
	//	else if(table->getCurrClass()->lookUpVarOffset(name, table, offset))
	//	{
	//		prv = new Ex(new Tree::MEM(
	//			new Tree::BINOP(Tree::BINOP::PLUS,new Tree::TEMP(CurrFrame->getThis()),
	//			new Tree::BINOP(Tree::BINOP::MUL, new Tree::CONST(CurrFrame->wordSize()), new Tree::CONST(offset)))));
	//		res = true;
	//	}
	//
	//}

	void Translator::Visit( const CThExp& p ) //this 
	{
		// ��������� this
		Temp::CTemp* tempThis = CurrFrame->getThis();
		// ���������� exp
		Previous = new Ex( new Tree::TEMP( tempThis ) );
	}

	void Translator::Visit( const CNewIntExp& p ) //new int [ Exp ]
	{
		// ��������� exp
		p.GetExp()->Accept( this );
		// ���������� ������, ������� ���������� ��������
		Tree::IExp* size = new Tree::BINOP( Tree::BINOP::MUL, new Tree::CONST( CurrFrame->wordSize() ),
			new Tree::BINOP( Tree::BINOP::PLUS, Previous->unEx(), new Tree::CONST( 1 ) ) );
		// initArray - ��� ������� �������, ������� ������� ������
		Temp::CLabel* initArray = new Temp::CLabel( "initArray" );
		// �������� ������� � ���������� size
		Tree::IExp* getSpace = ExternalCall( new Tree::NAME( initArray ), new Tree::ExpList( size, 0 ) );
		// � ������� ���� ���������� ������ �������
		Tree::IStm* b = new Tree::MOVE( new Tree::MEM( getSpace ), size );
		// ���������� exp
		Previous = new Ex( new Tree::ESEQ( b, getSpace ) );
	}

	void Translator::Visit( const CNewIdExp& p ) //new id ()
	{
		// ���� �����, ������ �������� ���������� �������
		std::string classId( p.GetId() );
		CClass* clss( table->FindClass( classId ) );
		// ������� ���������� ���������� ������ (������ ���������� - ������ ������)
		int sz( 1 );
		CVar* vr( clss->getVar() );
		if( vr ) {
			++sz;
			while( vr->getNext() ) {
				vr = vr->getNext();
				++sz;
			}
		}
		// ����������, ������� ����� ����� ��������
		Tree::IExp* size = new Tree::BINOP( Tree::BINOP::MUL,
			new Tree::CONST( sz ),
			new Tree::CONST(CurrFrame->wordSize()));
		// initClass - ��� ������� �������, ������� ������� ������ ������
		Temp::CLabel* initClass = new Temp::CLabel( "initClass" );
		// �������� ������� � ���������� size � ��������� �� � ����������
		Tree::IExp* variable = new Tree::TEMP( new Temp::CTemp() );
		Tree::IStm* getSpace = new Tree::MOVE( variable, ExternalCall( new Tree::NAME( initClass ), new Tree::ExpList( size, 0 ) ) );

		// � ������� ���� ���������� ������ ������
		Tree::IStm* b = new Tree::MOVE( variable, size );
		// ���������� ��� ��� � ������������������
		getSpace = new Tree::SEQ( getSpace, b );
		// ���������� exp
		Previous = new Ex( new Tree::ESEQ( getSpace, variable ) );
	}

	void Translator::Visit( const CNotExp& p ) // !Exp
	{
		// ��������� exp
		p.GetExp()->Accept( this );
		// ������� CNotOpCx ��� �����������
		// ���������� exp
		Previous = new CNotOpCx( Previous->unEx() );;
	}

	void Translator::Visit( const CBrExp& p ) //( Exp )
	{
		// ������� � ��������� exp
		if( p.GetExp() ) {
			p.GetExp()->Accept( this );
		}
	}
	void Translator::Visit( const CTypeId& p ) //id
	{
		// ���� �� ������
		assert( false );
	}


	void Translator::Visit( const CExpList& p )
	{
		if( p.GetExp() ) {
			p.GetExp()->Accept( this );
			// ����������� ExpList ������ ��������������� ������� � ExpList ������ �������������� �������������
			expListPrevious = new Tree::ExpList( Previous->unEx(), expListPrevious );
		}
		if( p.GetExpList() ) {
			p.GetExpList()->Accept( this );
		}
	}

	void Translator::Visit( const CFormalList& p )
	{
		// ���� ������� �� ������
		assert( false );
	}

	void Translator::Visit( const CClassDeclList& p )//ClassDeclList
	{
		if( p.GetTop() ) {
			p.GetTop()->Accept( this );
		}
		if( p.GetTail() ) {
			p.GetTail()->Accept( this );
		}
	}

	void Translator::Visit( const CVarDeclList& p )
	{
		if( p.GetTop() ) {
			p.GetTop()->Accept( this );
		}
		if( p.GetTail() ) {
			p.GetTail()->Accept( this );
		}
	}

	void Translator::Visit( const CMethodDeclList& p )
	{
		if( p.GetTop() ) {
			p.GetTop()->Accept( this );
		}
		if( p.GetTail() ) {
			p.GetTail()->Accept( this );
		}
	}

	void Translator::Visit( const CStmList& p )
	{
		Tree::IStm* exp = 0;
		if( p.GetTop() ) {
			p.GetTop()->Accept( this );
			exp = Previous->unNx();
		}
		if( p.GetTail() ) {
			p.GetTail()->Accept( this );
			if( exp != 0 ) {
				exp = new Tree::SEQ( exp, Previous->unNx() );
			} else {
				exp = Previous->unNx();
			}
		}
		Previous = new Translation::Nx( exp );
	}

	void Translator::Visit( const CEmptyStm& p )
	{
		Previous = new Translation::Nx( new Tree::LABEL(new Temp::CLabel() )); // fake label
	}

	void Translator::Visit( const CExpStm& p )
	{
		p.GetExp()->Accept( this );
		Previous = new Translation::Nx( Previous->unNx() );
	}
}