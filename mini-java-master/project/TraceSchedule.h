#include "BasicBlocks.h"
#include <map>

namespace Canon
{
	class TraceSchedule {
	public:
		const Tree::StmList* stms;

		TraceSchedule( ÑBasicBlocks b );
	private:
		ÑBasicBlocks theBlocks;
		std::map<const Temp::CLabel*, const Tree::StmList*> table;

		const Tree::StmList* getLast( const Tree::StmList* block );

		void trace( const Tree::StmList* l );

		const Tree::StmList* getNext();
	};
} // end of namespace