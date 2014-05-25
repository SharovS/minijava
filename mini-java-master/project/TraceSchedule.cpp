#include "TraceSchedule.h"

namespace Canon
{

	TraceSchedule::TraceSchedule( СBasicBlocks b ) : theBlocks( b ), stms( 0 ), table()
	{
		for( CStmListList* l = b.blocks; l != 0; l = l->tail ) {
			table[(dynamic_cast<const Tree::LABEL*>(l->head->getTop()))->getLabel()] = l->head;
		}
		stms = getNext();
	}

	const Tree::StmList* TraceSchedule::getLast( const Tree::StmList* block )
	{
		const Tree::StmList* l = block;
		while( l->getTail()->getTail() != 0 ) {
			l = l->getTail();
		}
		return l;
	}

	void TraceSchedule::trace( const Tree::StmList* l )
	{
		for( ;; ) {
			const Tree::LABEL* lab = dynamic_cast<const Tree::LABEL*>(l->getTop());
			table[lab->getLabel()] = 0;
			const Tree::StmList* last = getLast( l );
			const Tree::IStm* s = last->getTail()->getTop();
			if( dynamic_cast<const Tree::JUMP*>(s) != 0 ) {
				const Tree::JUMP* j = dynamic_cast<const Tree::JUMP*>(s);
				const Tree::StmList* target = dynamic_cast<const Tree::StmList*>(table[j->getTgList()->getTop()]);
				if( j->getTgList()->getTail() == 0 && target != 0 ) {
					// cнимем константность
					const_cast<Tree::StmList*>(last->getTail())->setTail( const_cast<Tree::StmList*>(target) );
					l = target;
				} else {
					const_cast<Tree::StmList*>(last->getTail())->setTail( const_cast<Tree::StmList*>(getNext()) );
					return;
				}
			} else if( dynamic_cast<const Tree::CJUMP*>(s) != 0 ) {
				const Tree::CJUMP* j = dynamic_cast<const Tree::CJUMP*>(s);
				const Tree::StmList* t = dynamic_cast<const Tree::StmList*>(table[j->getTrueLabel()]);
				const Tree::StmList* f = dynamic_cast<const Tree::StmList*>(table[j->getFalseLabel()]);
				if( f != 0 ) {
					// cнимем константность
					const_cast<Tree::StmList*>(last->getTail())->setTail( const_cast<Tree::StmList*>(f) );
					l = f;
				} else if( t != 0 ) {
					// cнимем константность
					const_cast<Tree::StmList*>(last->getTail())->setTop( new Tree::CJUMP( Tree::CJUMP::reverseRelOp( j->getRelOp() ),
						j->getLeftExp(), j->getRightExp(),
						j->getFalseLabel(), j->getTrueLabel() ) );
					const_cast<Tree::StmList*>(last->getTail())->setTail( const_cast<Tree::StmList*>(t) );
					l = t;
				} else {
					Temp::CLabel* ff = new Temp::CLabel();
					const_cast<Tree::StmList*>(last->getTail())->setTop( new Tree::CJUMP( j->getRelOp(), j->getLeftExp(), j->getRightExp(),
						j->getTrueLabel(), ff ) );
					const_cast<Tree::StmList*>(last->getTail())->setTail( new Tree::StmList( new Tree::LABEL( ff ),
						new Tree::StmList( new Tree::JUMP( j->getFalseLabel() ),
						getNext() ) ) );
					return;
				}
			} else {
				assert( false );
			}
		}
	}

	const Tree::StmList* TraceSchedule::getNext()
	{
		if( theBlocks.blocks == 0 ) {
			return new Tree::StmList( new Tree::LABEL( theBlocks.done ), 0 );
		} else {
			Tree::StmList* s = theBlocks.blocks->head;
			const Tree::LABEL* lab = dynamic_cast<const Tree::LABEL*>(s->getTop());
			if( table[lab->getLabel()] != 0 ) {
				trace( s );
				return s;
			} else {
				theBlocks.blocks = theBlocks.blocks->tail;
				return getNext();
			}
		}
	}
} // end of namespace
