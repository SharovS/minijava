#include "Canon.h"

namespace Canon
{

	// ������ ������, ��������� ���������� ������ Canon
	CStmExpList* CCanon::nopNull = new CStmExpList( new Tree::EXP( new Tree::CONST( 0 ) ), 0 );

	//-------------------------------------------------------------------//

	// ���������� Tree::ExpList, ��������� �� Exp � ExpList, ������������ � CALL
	const Tree::ExpList* CMoveCall::Kids() const
	{
		return src->Kids();
	}

	// ���������� ������ ����� ������� � ���������� �������� �� ��������� ����������
	const Tree::IStm* CMoveCall::Build( const Tree::ExpList* kids ) const
	{
		return new Tree::MOVE( dst, src->Build( kids ) );
	}

	//-------------------------------------------------------------------//

	// ���������� Tree::ExpList, ��������� �� Exp � ExpList, ������������ � CALL
	const Tree::ExpList* CExpCall::Kids() const
	{
		return call->Kids();
	}

	// ���������� ������ ����� ������� � �������������� ������������� ��������
	const Tree::IStm* CExpCall::Build( const Tree::ExpList* kids ) const
	{
		return new Tree::EXP( call->Build( kids ) );
	}

	//-------------------------------------------------------------------//

	// ����� ���������, �������� �� ��������� stm �� ���������
	// ������: 5;
	bool CCanon::isNop( const Tree::IStm* a )
	{
		return dynamic_cast<const Tree::EXP*>(a) != 0
			&& dynamic_cast<const Tree::CONST*>((dynamic_cast<const Tree::EXP*>(a))->getExp()) != 0;
	}

	// ����� ���������� ���������� ����������� ���������, ���� ����� ����������.
	// ������: 
	// ����: a+=1 � 5. �����: a+=1;
	// ����: a+=1 � b*=2. �����: SEQ(a+=1, b*=2)
	const Tree::IStm* CCanon::simplifySeq( const Tree::IStm* a, const Tree::IStm* b )
	{
		if( isNop( a ) ) {
			return b;
		} else if( isNop( b ) ) {
			return a;
		} else {
			return new Tree::SEQ( a, b );
		}
	}

	// ����� ���������, ���������� �� a � b
	// �.�. �������� �� �� ��������� ����� ���� a � b
	// ���� ���������� - �� ������ ������� �����
	bool CCanon::commute( const Tree::IStm* a, const Tree::IExp* b )
	{
		return isNop( a )
			|| dynamic_cast<const Tree::NAME*>(b) != 0
			|| dynamic_cast<const Tree::CONST*>(b) != 0;
	}

	// do_stm - ������� �������������� ���������
	// ����� �������������� SEQ
	// ������ �������� do_stm �� �����
	const Tree::IStm* CCanon::do_stm( const Tree::SEQ* s )
	{
		return simplifySeq( do_stm( s->getLeftStm() ), do_stm( s->getRightStm() ) );
	}

	// ����� �������������� MOVE
	// ���� � ��� ����������� ���� ������ ���������� ������ ������� � ���������� - 
	// �������� reorder_stm �� CMoveCall � ����������� TEMP � CALL;
	// ���� ����� ������ - ESEQ - ����������� ��� � ������������������, ������ �������� stm �� ESEQ, 
	// � ����� ��������� � exp �� ESEQ exp �� MOVE, � ����� �������� ��������������� ������������ ���������;
	// ����� - �������� reorder_stm �� MOVE
	const Tree::IStm* CCanon::do_stm( const Tree::MOVE* s )
	{
		if( dynamic_cast<const Tree::TEMP*>(s->getDst()) != 0 &&
			dynamic_cast<const Tree::CALL*>(s->getSrc()) != 0 ) {
			return reorder_stm( new CMoveCall( dynamic_cast<const Tree::TEMP*>(s->getDst()),
				dynamic_cast<const Tree::CALL*>(s->getSrc()) ) );
		} else if( dynamic_cast<const Tree::ESEQ*>(s->getDst()) != 0 ) {
			return do_stm( new Tree::SEQ( (dynamic_cast<const Tree::ESEQ*>(s->getDst()))->getStm(),
				new Tree::MOVE( (dynamic_cast<const Tree::ESEQ*>(s->getDst()))->getExp(),
				s->getSrc() ) ) );
		} else {
			return reorder_stm( s );
		}
	}

	// ����� �������������� EXP
	// ���� ������ ����� ������� - �������� reorder_stm �� CExpCall � ���������� CALL
	// ����� - �������� reorder_stm �� EXP
	const Tree::IStm* CCanon::do_stm( const Tree::EXP* s )
	{
		if( dynamic_cast<const Tree::CALL*>(s->getExp()) != 0 ) {
			return reorder_stm( new CExpCall( dynamic_cast<const Tree::CALL*>(s->getExp()) ) );
		} else {
			return reorder_stm( s );
		}
	}

	// ����� �������������� Stm
	// �������� ��������������� ��������������, ���� ��� Stm ��������,
	// ����� - �������� reorder_stm �� Stm
	const Tree::IStm* CCanon::do_stm( const Tree::IStm* s )
	{
		if( dynamic_cast<const Tree::SEQ*>(s) != 0 ) {
			return do_stm( dynamic_cast<const Tree::SEQ*>(s) );
		} else if( dynamic_cast<const Tree::MOVE*>(s) != 0 ) {
			return do_stm( dynamic_cast<const Tree::MOVE*>(s) );
		} else if( dynamic_cast<const Tree::EXP*>(s) != 0 ) {
			if( isNop( s ) ) {
				return 0;
			} else {
				return do_stm( dynamic_cast<const Tree::EXP*>(s) );
			}
		} else {
			return reorder_stm( s );
		}
	}

	// �����, ������������� Stm, ������ ��� ������������ � ��� �������� ������
	const Tree::IStm* CCanon::reorder_stm( const Tree::IStm* s )
	{
		if( s == 0 ) {
			return 0;
		}
		// ������� ��� �������� ������ � x.stm
		const CStmExpList* x = reorder( s->Kids() );
		// ��������, ���� ��������
		return simplifySeq( x->stm, s->Build( x->exps ) );
	}

	// do_exp - ������� �������������� Exp
	// ����� �������������� ESEQ
	// ��������������� Exp � Stm, ������������ � ESEQ � ���������� ���������� ESEQ
	const Tree::ESEQ* CCanon::do_exp( const Tree::ESEQ* e )
	{
		const Tree::IStm* stms = do_stm( e->getStm() );
		const Tree::ESEQ* b = do_exp( e->getExp() );
		return new Tree::ESEQ( simplifySeq( stms, b->getStm() ), b->getExp() );
	}

	// ����� �������������� Exp � ESEQ
	// � ������ ESEQ �������� �-�� �������������� ��������
	// ����� - �������� reorder_exp �� Exp
	const Tree::ESEQ* CCanon::do_exp( const Tree::IExp* e )
	{
		if( dynamic_cast<const Tree::ESEQ*>(e) != 0 ) {
			return do_exp( dynamic_cast<const Tree::ESEQ*>(e) );
		} else {
			return reorder_exp( e );
		}
	}

	// �����, ������������� Exp, ������ ��� ������������ � ��� �������� ������
	const Tree::ESEQ* CCanon::reorder_exp( const Tree::IExp* e )
	{
		// ������� ��� �������� ������ � x.stm
		const CStmExpList* x = reorder( e->Kids() );
		// ���������� ESEQ
		return new Tree::ESEQ( x->stm, e->Build( x->exps ) );
	}

	// �����, ��������� ������ ��� ��������, ������������ � ����� ��-��� ExpList
	const CStmExpList* CCanon::reorder( const Tree::ExpList* exps )
	{
		// ���������� ������ ������, ���� ��� ��������� ������
		if( exps == 0 ) {
			return nopNull;
		} else {
			const Tree::IExp* a = exps->getTop();
			if( dynamic_cast<const Tree::CALL*>(a) != 0 ) {
				// ���� 1 ������� ������ - ����� �������, 
				// �� ���������� ������������ �������� �� ��������� ���������� � ���������� ��
				Temp::CTemp* t = new Temp::CTemp();
				Tree::IExp* e = new Tree::ESEQ( new Tree::MOVE( new Tree::TEMP( t ), a ),
					new Tree::TEMP( t ) );
				// ���������� ����� � ������ ������������ ESEQ
				return reorder( new Tree::ExpList( e, exps->getTail() ) );
			} else {
				// ����������� Exp � ESEQ, ������� ������� ��� ����������
				const Tree::ESEQ* aa = do_exp( a );
				// ����������� ��������� ����� ������
				const CStmExpList* bb = reorder( exps->getTail() );
				if( commute( bb->stm, aa->getExp() ) ) {
					// ���� ���������� - ������ �������� ������� ������
					return new CStmExpList( simplifySeq( aa->getStm(), bb->stm ),
						new Tree::ExpList( aa->getExp(), bb->exps ) );
				} else {
					// ���� �� ���������� - �������� aa, bb 
					// � ���������� ������ �������� �� ��������� ����������
					Temp::CTemp* t = new Temp::CTemp();
					return new CStmExpList( simplifySeq( aa->getStm(),
						simplifySeq( new Tree::MOVE( new Tree::TEMP( t ),
						aa->getExp() ),
						bb->stm ) ),
						new Tree::ExpList( new Tree::TEMP( t ), bb->exps ) );
				}
			}
		}
	}

	// ����� ������������ SEQ
	// ���������� ��������� ��� s.left, s.right, StmList
	const Tree::StmList* CCanon::linear( const Tree::SEQ* s, const Tree::StmList* l )
	{
		return linear( s->getLeftStm(), linear( s->getRightStm(), l ) );
	}

	// ����� ������������ ������ ���������
	// �� ������ �������� ������������������ �������� ���� s1, s2, s3 ... 
	const Tree::StmList* CCanon::linear( const Tree::IStm* s, const Tree::StmList* l )
	{
		if( dynamic_cast<const Tree::SEQ*>(s) != 0 ) {
			return linear( dynamic_cast<const Tree::SEQ*>(s), l );
		} else {
			return new Tree::StmList( s, l );
		}
	}

	// ����� ������������ ���������
	const Tree::StmList* CCanon::linearize( const Tree::IStm* s )
	{
		if( s == 0 ) {
			return 0;
		} else {
			return linear( do_stm( s ), 0 );
		}
	}

} // End of Canon