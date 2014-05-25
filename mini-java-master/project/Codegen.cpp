#include <Codegen.h>

#include <map>
#include <string>

static std::map<std::string, Temp::CTemp*> loaded;

void Codegen::munchStm( const Tree::SEQ* target )
{
	munchStm( target->getLeftStm() );
	munchStm( target->getRightStm() );
}

void Codegen::munchStm( const Tree::MOVE* target )
{
	if ( dynamic_cast<const Tree::MEM*>( target->getDst() ) != 0 ) {
		const Tree::MEM* exp1 = dynamic_cast<const Tree::MEM*>( target->getDst() );

		if ( dynamic_cast<const Tree::BINOP*>( exp1->getExp() ) != 0 ) {
			const Tree::BINOP* exp2 = dynamic_cast<const Tree::BINOP*>( exp1->getExp() );

			if ( ( exp2->getBinOp() == Tree::BINOP::PLUS )
				&& ( dynamic_cast<const Tree::CONST*>(exp2->getLeftExp()) != 0 ) )
			{
				const Tree::CONST* exp3 = dynamic_cast<const Tree::CONST*>( exp2->getLeftExp() );
				// MOVE(MEM(BINOP(PLUS,CONST(i),e1)),e2)
				string name = "STORE M['s0+";
				name += exp3->toString();
				name += "] <- 's1\n";
				emit( new Assembler::OPER( name, 0, L( munchExp( exp2->getRightExp() ),
					L( munchExp( target->getSrc() ), 0 ) ) ) );
				return;
			}

			if ( ( exp2->getBinOp() == Tree::BINOP::PLUS )
				&& ( dynamic_cast<const Tree::CONST*>(exp2->getRightExp()) != 0 ) ) 
			{
				const Tree::CONST* exp3 = dynamic_cast<const Tree::CONST*>( exp2->getRightExp() );
				// MOVE(MEM(BINOP(PLUS,e1,CONST(i))),e2)
				string name = "STORE M['s0+";
				name += exp3->toString();
				name += "] <- 's1\n";
				emit( new Assembler::OPER( name, 0, L( munchExp( exp2->getLeftExp() ),
					L( munchExp( target->getSrc() ), 0 ) ) ) );
				return;
			}
		}

		if( dynamic_cast<const Tree::CONST*>( exp1->getExp() ) != 0 ) {
			const Tree::CONST* exp2 = dynamic_cast<const Tree::CONST*>( exp1->getExp() );
			// MOVE(MEM(CONST(i)),e2)
			string name = "STORE M[r0+";
			name += exp2->toString();
			name += "] <- 's0\n";
			emit( new Assembler::OPER( name, 0, L( munchExp( target->getSrc() ), 0 ) ) );
			return;
		}

		if( dynamic_cast<const Tree::MEM*>( target->getSrc() ) != 0 ) {
			const Tree::MEM* exp2 = dynamic_cast<const Tree::MEM*>( target->getSrc() );
			// MOVE(MEM(e1),MEM(e2))
			emit( new Assembler::OPER( "MOVE M['s0] <- M['s1]\n", 0,
				L( munchExp( exp1->getExp() ), L( munchExp( exp2->getExp() ), 0 ) ) ) );
			return;
		}

		// MOVE(MEM(e1),e2)
		emit( new Assembler::OPER( "STORE M['s0] <- 's1\n", 0,
			L( munchExp( exp1->getExp() ), L( munchExp( target->getSrc() ), 0 ) ) ) );
		return;
	}

	if( dynamic_cast<const Tree::TEMP*>( target->getDst() ) != 0 ) {
		const Tree::TEMP* exp = dynamic_cast<const Tree::TEMP*>( target->getDst() );

		if( dynamic_cast<const Tree::CALL*>( target->getSrc()) != 0 ) {
			const Tree::CALL* call = dynamic_cast<const Tree::CALL*>(target->getSrc());
			// MOVE(TEMP(i),CALL(e,args))
			const Temp::CTemp* functionTemp = munchExp( call->getFuncExp() );
			const Temp::CTempList* argList = munchArgs( call->getArgsExpList() );
			emit( new Assembler::OPER( "CALL 's0\n", 0, L( functionTemp, argList ) ) );
			std::string name = "ADD 'd0 <- 'r0 + rv\n";
			emit( new Assembler::OPER( name, L( exp->getTemp(), 0 ), 0 ) );
			return;
		}

		// MOVE(TEMP(i), e2)
		emit( new Assembler::OPER( "ADD 'd0 <- 's0 + r0\n",
			L( exp->getTemp(), 0 ), L( munchExp( target->getSrc() ), 0 ) ) );
		return;
	}
	assert( false );
}

void Codegen::munchStm( const Tree::LABEL* target )
{
	// LABEL(lab)
	emit( new Assembler::LABEL( target->getLabel()->getLabelName() + ":\n", target->getLabel() ) );
}


void Codegen::munchStm( const Tree::JUMP* target )
{
	const Tree::IExp* labelExp = target->getExp();
	std::string name = "JMP 'l0\n";
	emit( new Assembler::OPER( name, 0, 0, target->getTgList() ) );
}

void Codegen::munchStm( const Tree::CJUMP* target )
{
	std::string name;
	Temp::CTemp* resultExp = new Temp::CTemp();
	// cоздаем новый биноп, вычитающий e2 из e1, манчим его
	Tree::IStm* resultExpTree = new Tree::MOVE( new Tree::TEMP( resultExp ),
		new Tree::BINOP( Tree::BINOP::MINUS, target->getLeftExp(), target->getRightExp() ) );
	munchStm( resultExpTree );

	switch( target->getRelOp() ) {
		case Tree::CJUMP::EQ:
			name = "CJmpEQ ";
			break;
		case Tree::CJUMP::NE:
			name = "CJmpNE ";
			break;
		case Tree::CJUMP::GT:
			name = "CJmpGT ";
			break;
		case Tree::CJUMP::LT:
			name = "CJmpLT ";
			break;
		case Tree::CJUMP::LE:
			name = "CJmpLE ";
			break;
		case Tree::CJUMP::GE:
			name = "CJmpGE ";
			break;
		case Tree::CJUMP::ULT:
			name = "CJmpULT ";
			break;
		case Tree::CJUMP::ULE:
			name = "CJmpULE ";
			break;
		case Tree::CJUMP::UGT:
			name = "CJmpUGT ";
			break;
		case Tree::CJUMP::UGE:
			name = "CJmpUGE ";
			break;
		default:
			assert( false );
	}
	name += "'s0 'l0\n";
	Temp::CLabelList* possibleLabels = new Temp::CLabelList( target->getTrueLabel(),
		new Temp::CLabelList( target->getFalseLabel(), 0 ) );
	emit( new Assembler::OPER( name, 0, L( resultExp, 0 ), possibleLabels ) );
}

const Temp::CTempList* Codegen::munchArgs( const Tree::ExpList* args )
{
	if( args->getTail() != 0 ) {
		Temp::CTemp* r = new Temp::CTemp();
		Tree::IStm* newStm = new Tree::MOVE( new Tree::TEMP( r ), args->getTop() );
		munchStm( newStm );
		return new Temp::CTempList( r, munchArgs( args->getTail() ) );
	} else {
		Temp::CTemp* r = new Temp::CTemp();
		Tree::IStm* newStm = new Tree::MOVE( new Tree::TEMP( r ), args->getTop() );
		munchStm( newStm );
		return new Temp::CTempList( r, 0 );
	}
}

void Codegen::munchStm( const Tree::EXP* target )
{
	if( dynamic_cast<const Tree::CALL*>(target->getExp()) != 0 ) {
		const Tree::CALL* exp = dynamic_cast<const Tree::CALL*>(target->getExp());
		//EXP(CALL(e,args))
		const Temp::CTemp* r = munchExp( exp->getFuncExp() );
		const Temp::CTempList* l = munchArgs( exp->getArgsExpList() );
		emit( new Assembler::OPER( "CALL 's0\n", 0, L( r, l ) ) );
		return;
	}
	assert( false );
}

const Temp::CTemp* Codegen::munchExp( const Tree::MEM* target )
{
	if( dynamic_cast<const Tree::BINOP*>( target->getExp() ) != 0 ) {
		const Tree::BINOP* exp1 = dynamic_cast<const Tree::BINOP*>( target->getExp() );

		if( ( exp1->getBinOp() == Tree::BINOP::PLUS )
			&& ( dynamic_cast<const Tree::CONST*>(exp1->getLeftExp()) != 0 ) )
		{
			const Tree::CONST* exp2 = dynamic_cast<const Tree::CONST*>( exp1->getLeftExp() );
			// MEM(BINOP(PLUS,CONST(i),e1))
			Temp::CTemp* r = new Temp::CTemp();
			string name = "LOAD 'd0 <- M['s0+";
			name += exp2->toString();
			name += "]\n";
			emit( new Assembler::OPER( name, L( r, 0 ),
				L( munchExp( exp1->getRightExp() ), 0 ) ) );
			return r;
		}

		if ( ( exp1->getBinOp() == Tree::BINOP::PLUS )
			&& ( dynamic_cast<const Tree::CONST*>( exp1->getRightExp() ) != 0 ) )
		{
			const Tree::CONST* exp2 = dynamic_cast<const Tree::CONST*>( exp1->getRightExp() );
			//MEM(BINOP(PLUS,e1,CONST(i)))
			Temp::CTemp* r;
			if( loaded.find( exp2->toString() ) == loaded.end() ) {
				r = new Temp::CTemp();
				std::string name = "LOAD 'd0 <- M['s0+";
				name += exp2->toString();
				name += "]\n";
				emit( new Assembler::OPER( name,
					L( r, 0 ), L( munchExp( exp1->getLeftExp() ), 0 ) ) );
				loaded.insert( std::pair<std::string, Temp::CTemp*>( exp2->toString(), r ) );
			}
			else {
				r = loaded.find( exp2->toString() )->second;
			}
			return r;
		}
	}

	if ( dynamic_cast<const Tree::CONST*>( target->getExp() ) != 0 ) {
		const Tree::CONST* exp = dynamic_cast<const Tree::CONST*>( target->getExp() );
		// MEM(CONST(i))
		Temp::CTemp* r = new Temp::CTemp();
		string name = "LOAD 'd0 <- M['r0+";
		name += exp->toString();
		name += "]\n";
		emit( new Assembler::OPER( name,
			L( r, 0 ), 0 ) );
		return r;
	}

	// MEM(e1)
	Temp::CTemp* r = new Temp::CTemp();
	emit( new Assembler::OPER( "LOAD 'd0 <- M['s0+0]\n",
		L( r, 0 ), L( munchExp( target->getExp() ), 0 ) ) );
	return r;
}


const Temp::CTemp* Codegen::munchExp( const Tree::BINOP* target )
{
	if ( target->getBinOp() == Tree::BINOP::PLUS ) {
		if ( dynamic_cast<const Tree::CONST*>( target->getLeftExp() ) != 0 ) {
			const Tree::CONST* exp = dynamic_cast<const Tree::CONST*>( target->getLeftExp() );
			// BINOP(PLUS,CONST(i),e1)
			Temp::CTemp* r = new Temp::CTemp();
			string name = "ADDI 'd0 <- 's0+";
			name += exp->toString();
			name += "\n";
			emit( new Assembler::OPER( name,
				L( r, 0 ), L( munchExp( target->getRightExp() ), 0 ) ) );
			return r;
		}

		if ( dynamic_cast<const Tree::CONST*>( target->getRightExp() ) != 0 ) {
			const Tree::CONST* exp = dynamic_cast<const Tree::CONST*>( target->getRightExp() );
			// BINOP(PLUS,e1,CONST(i))
			Temp::CTemp* r = new Temp::CTemp();
			string name = "ADDI 'd0 <- 's0+";
			name += exp->toString();
			name += "\n";
			emit( new Assembler::OPER( name, L( r, 0 ),
				L( munchExp( target->getLeftExp() ), 0 ) ) );
			return r;
		}
		// BINOP(PLUS,e1,e2)
		Temp::CTemp* r = new Temp::CTemp();
		emit( new Assembler::OPER( "ADD 'd0 <- 's0+'s1\n", L( r, 0 ),
			L( munchExp( target->getLeftExp() ), L( munchExp( target->getRightExp() ), 0 ) ) ) );
		return r;
	}

	if ( target->getBinOp() == Tree::BINOP::MINUS ) {
		if ( dynamic_cast<const Tree::CONST*>( target->getLeftExp() ) != 0 ) {
			const Tree::CONST* exp = dynamic_cast<const Tree::CONST*>( target->getLeftExp() );
			// BINOP(MINUS,CONST(i),e1)
			Temp::CTemp* r = new Temp::CTemp();
			string name = "SUBI 'd0 <- 's0-";
			name += exp->toString();
			name += "\n";
			emit( new Assembler::OPER( name,
				L( r, 0 ), L( munchExp( target->getRightExp() ), 0 ) ) );
			return r;
		}

		if( dynamic_cast<const Tree::CONST*>( target->getRightExp() ) != 0 ) {
			const Tree::CONST* exp = dynamic_cast<const Tree::CONST*>( target->getRightExp() );
			// BINOP(MINUS,e1,CONST(i))
			Temp::CTemp* r = new Temp::CTemp();
			string name = "SUBI 'd0 <- 's0-";
			name += exp->toString();
			name += "\n";
			emit( new Assembler::OPER( name,
				L( r, 0 ), L( munchExp( target->getLeftExp() ), 0 ) ) );
			return r;
		}

		// BINOP(MINUS,e1,e2)
		Temp::CTemp* r = new Temp::CTemp();
		emit( new Assembler::OPER( "SUB 'd0 <- 's0-'s1\n",
			L( r, 0 ), L( munchExp( target->getLeftExp() ),
			L( munchExp( target->getRightExp() ), 0 ) ) ) );
		return r;
	}

	if ( target->getBinOp() == Tree::BINOP::MUL ) {
		// BINOP(MUL,e1,e2)
		Temp::CTemp* r = new Temp::CTemp();
		emit( new Assembler::OPER( "MUL 'd0 <- 's0*'s1\n",
			L( r, 0 ), L( munchExp( target->getLeftExp() ),
			L( munchExp( target->getRightExp() ), 0 ) ) ) );
		return r;
	}

	if( target->getBinOp() == Tree::BINOP::DIV ) {
		// BINOP(DIV,e1,e2)
		Temp::CTemp* r = new Temp::CTemp();
		emit( new Assembler::OPER( "DIV 'd0 <- 's0/'s1\n", L( r, 0 ),
			L( munchExp( target->getLeftExp() ), L( munchExp( target->getRightExp() ), 0 ) ) ) );
		return r;
	}
	assert( false );
	return 0;
}


const Temp::CTemp* Codegen::munchExp( const Tree::CONST* target )
{
	// CONST(i)
	Temp::CTemp* r = new Temp::CTemp();
	string name = "ADDI 'd0 <- 'r0+";
	name += target->toString();
	name += "\n";
	emit( new Assembler::OPER( name, L( r, 0 ), 0 ) );
	return r;
}


const Temp::CTemp* Codegen::munchExp( const Tree::TEMP* target )
{
	return target->getTemp();
}

const Temp::CTemp* Codegen::munchExp( const Tree::NAME* target )
{
	return new Temp::CTemp( target->getLabel()->getLabelName() );
}