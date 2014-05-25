#pragma once
#include "Temp.h"
#include "Tree.h"

namespace Canon
{

	class CStmListList;

	class ÑBasicBlocks {
	public:
		CStmListList* blocks;
		Temp::CLabel* done;

		ÑBasicBlocks( const Tree::StmList* stms );
	private:
		CStmListList* lastBlock;
		Tree::StmList* lastStm;

		void addStm( const Tree::IStm* s );

		void doStms( const Tree::StmList* l );

		void makeBlocks( const Tree::StmList* l );
	};

	//--------------------------------------------------------------------------------------

	class CStmListList {
	public:
		Tree::StmList* head;
		CStmListList* tail;
		CStmListList( Tree::StmList* _head, CStmListList* _tail ) : head( _head ), tail( _tail ) {}
	};
} // end of namespace
