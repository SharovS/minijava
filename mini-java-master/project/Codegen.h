#pragma once;

#include <string.h>

#include "AssemblerGenerator.h"
#include "Translator.h"
#include "Tree.h"
#include "Frame.h"
#include "Temp.h"

using namespace std;

class Codegen {
public:
	Codegen( const Frame::CFrame* f ) : frame( f ), ilist( 0 ), last( 0 ) {}

	virtual void munchStm( const Tree::IStm* target )
	{
		if( dynamic_cast<const Tree::SEQ*>( target ) != 0 ) {
			munchStm( dynamic_cast<const Tree::SEQ*>( target ) );
			return;
		}
		if ( dynamic_cast<const Tree::MOVE*>( target ) != 0 ) {
			munchStm( dynamic_cast<const Tree::MOVE*>(target) );
			return;
		}
		if ( dynamic_cast<const Tree::LABEL*>( target ) != 0 ) {
			munchStm( dynamic_cast<const Tree::LABEL*>( target ) );
			return;
		}
		if ( dynamic_cast<const Tree::JUMP*>( target ) != 0 ) {
			munchStm( dynamic_cast<const Tree::JUMP*>( target ) );
			return;
		}
		if ( dynamic_cast<const Tree::CJUMP*>( target ) != 0 ) {
			munchStm( dynamic_cast<const Tree::CJUMP*>( target ) );
			return;
		}
		if( dynamic_cast<const Tree::EXP*>( target ) != 0 ) {
			munchStm( dynamic_cast<const Tree::EXP*>( target ) );
			return;
		}
		assert( false );
	}

	virtual void munchStm( const Tree::SEQ* target );
	virtual void munchStm( const Tree::MOVE* target );
	virtual void munchStm( const Tree::LABEL* target );
	virtual void munchStm( const Tree::JUMP* target );
	virtual void munchStm( const Tree::CJUMP* target );
	virtual void munchStm( const Tree::EXP* target );

	virtual const Temp::CTemp* munchExp( const Tree::IExp* target )
	{
		if( dynamic_cast<const Tree::MEM*>(target) != 0 ) {
			munchExp( dynamic_cast<const Tree::MEM*>(target) );
		} else if( dynamic_cast<const Tree::BINOP*>(target) != 0 ) {
			munchExp( dynamic_cast<const Tree::BINOP*>(target) );
		} else if( dynamic_cast<const Tree::CONST*>(target) != 0 ) {
			munchExp( dynamic_cast<const Tree::CONST*>(target) );
		} else if( dynamic_cast<const Tree::TEMP*>(target) != 0 ) {
			munchExp( dynamic_cast<const Tree::TEMP*>(target) );
		} else if( dynamic_cast<const Tree::NAME*>(target) != 0 ) {
			munchExp( dynamic_cast<const Tree::NAME*>(target) );
		} else {
			assert( false );
			return 0;
		}
	}

	virtual const Temp::CTemp* munchExp( const Tree::MEM* target );
	virtual const Temp::CTemp* munchExp( const Tree::BINOP* target );
	virtual const Temp::CTemp* munchExp( const Tree::CONST* target );
	virtual const Temp::CTemp* munchExp( const Tree::TEMP* target );
	virtual const Temp::CTemp* munchExp( const Tree::NAME* target );

	Assembler::IInstrList* generateCode( Translation::CProgramFragment* fragment )
	{
		Assembler::IInstrList* l;
		const Tree::ESEQ* funccode = dynamic_cast<const Tree::ESEQ*>( fragment->funcCode );
		//munchStm(funccode->getStm());
		for( const Tree::StmList* list = fragment->funcCodeLinearized;
			list != 0; list = list->getTail() )
		{
			munchStm( list->getTop() );
		}
		const Temp::CTemp* retval = munchExp( funccode->getExp() );
		emit( new Assembler::MOVE( "MOVE rv <- 's0\n", 0, retval ) );
		l = ilist;
		ilist = 0;
		last = 0;
		return l;
	}

	Assembler::IInstrList* generateCode( Tree::IStm* s )
	{
		Assembler::IInstrList* l;
		munchStm( s );
		l = ilist;
		ilist = 0;
		last = 0;
		return l;
	}

private:
	Assembler::IInstrList* last;
	Assembler::IInstrList* ilist;
	const Frame::CFrame* frame;

	const Temp::CTempList* munchArgs( const Tree::ExpList* args );

	const Temp::CTempList* L( const Temp::CTemp* h, const Temp::CTempList* t )
	{
		return new Temp::CTempList( h, t );
	}

	void emit( Assembler::IInstr* inst )
	{
		if( last != 0 ) {
			last->setTail( new Assembler::IInstrList( inst, 0 ) );
			last = const_cast<Assembler::IInstrList*>( last->getTail() );
		}
		else {
			ilist = new Assembler::IInstrList( inst, 0 );
			last = ilist;
		}
	}

};