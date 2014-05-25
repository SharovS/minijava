#pragma once
# include "stdio.h"
#include <Tree.h>

class IntermediateTreeVisitor : public Tree::ITreeVisitor {
public:
	IntermediateTreeVisitor() {}
	void Visit( const Tree::CONST& p );
	void Visit( const Tree::NAME& p );
	void Visit( const Tree::TEMP& p );
	void Visit( const Tree::BINOP& p );
	void Visit( const Tree::MEM& p );
	void Visit( const Tree::CALL& p );
	void Visit( const Tree::ESEQ& p );
	void Visit( const Tree::MOVE& p );
	void Visit( const Tree::EXP& p );
	void Visit( const Tree::JUMP& p );
	void Visit( const Tree::CJUMP& p );
	void Visit( const Tree::SEQ& p );
	void Visit( const Tree::LABEL& p );
	void Visit( const Tree::ExpList& p );
	void Visit( const Tree::StmList& p );

};
