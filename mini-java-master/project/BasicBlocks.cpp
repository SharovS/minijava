#include "BasicBlocks.h"

namespace Canon
{

	�BasicBlocks::�BasicBlocks( const Tree::StmList* stms ) : lastBlock( 0 ), lastStm( 0 ), blocks( 0 )
	{
		done = new Temp::CLabel();
		makeBlocks( stms );
	}
	void �BasicBlocks::addStm( const Tree::IStm* s )
	{
		lastStm->setTail( new Tree::StmList( s, 0 ) );
		// ��... ������������ ���������� � ��������������... :-(
		lastStm = const_cast<Tree::StmList*>(lastStm->getTail());
	}

	void �BasicBlocks::doStms( const Tree::StmList* l )
	{
		if( l == 0 ) {
			doStms( new Tree::StmList( new Tree::JUMP( done ), 0 ) );
		} else if( dynamic_cast<const Tree::JUMP*>(l->getTop()) != 0 || dynamic_cast<const Tree::CJUMP*>(l->getTop()) != 0 ) {
			addStm( l->getTop() );
			makeBlocks( l->getTail() );
		} else if( dynamic_cast<const Tree::LABEL*>(l->getTop()) != 0 ) {
			doStms( new Tree::StmList( new Tree::JUMP( (dynamic_cast<const Tree::LABEL*>(l->getTop()))->getLabel() ), l ) );
		} else {
			addStm( l->getTop() );
			doStms( l->getTail() );
		}
	}

	void �BasicBlocks::makeBlocks( const Tree::StmList* l )
	{
		if( l == 0 ) {
			return;
		} else if( dynamic_cast<const Tree::LABEL*>(l->getTop()) != 0 ) {
			lastStm = new Tree::StmList( l->getTop(), 0 );
			if( lastBlock == 0 ) {
				blocks = new CStmListList( lastStm, 0 );
				lastBlock = blocks;
			} else {
				lastBlock->tail = new CStmListList( lastStm, 0 );
				lastBlock = lastBlock->tail;
			}
			doStms( l->getTail() );
		} else {
			makeBlocks( new Tree::StmList( new Tree::LABEL( new Temp::CLabel() ), l ) );
		}
	}

} // end of namespace
