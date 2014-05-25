#pragma once
#include "Temp.h"
#include "Tree.h"

namespace Canon
{

//-------------------------------------------------------------------//

// �������� ������ ���� CALL � ��������� ����������, ���� ������� ��������
// �.�. ����� � ������� �������� �� ��������� ����������
class CMoveCall : public Tree::IStm {
public:
	// �����������
	CMoveCall(const Tree::TEMP* _dst, const Tree::CALL* _src) : dst(_dst), src(_src) {}
	// ���������� Tree::ExpList, ��������� �� Exp � ExpList, ������������ � CALL
	virtual const Tree::ExpList* Kids() const;
	// ���������� ������ ����� ������� � ���������� �������� �� ��������� ����������
	virtual const Tree::IStm* Build(const Tree::ExpList* kids) const;
private:
	const Tree::TEMP* dst;
	const Tree::CALL* src;
};   
  
//-------------------------------------------------------------------//

// ������ ��-�� �����, ��� � �������� ����, ������ �������� EXP 
// (�.�. ������������ �������� �������������)
class CExpCall : public Tree::IStm {
public:
	// �����������
	CExpCall(const Tree::CALL* _call) : call(_call) {}
	// ���������� Tree::ExpList, ��������� �� Exp � ExpList, ������������ � CALL
	virtual const Tree::ExpList* Kids() const;
	// ���������� ������ ����� ������� � �������������� ������������� ��������
	virtual const Tree::IStm* Build(const Tree::ExpList* kids) const;
private:
	const Tree::CALL* call;
};   
  
//-------------------------------------------------------------------//

// ������ ������ ��� ����������
// �.�. � ������ ���������� ������ ExpList(������ ����������, ������� ��������)
// � stm - ��� �� ��������, ������� ���������� ��������� �� ������ ������� � ����� �����������
struct CStmExpList {
	// �����������
	CStmExpList(const Tree::IStm* _stm, const Tree::ExpList* _exps) : stm(_stm), exps(_exps) {}

	const Tree::IStm* stm;
	const Tree::ExpList* exps;
};

//-------------------------------------------------------------------//

class CCanon {
public:
	// ����� ���������, �������� �� ��������� stm �� ���������
	// ������: 5;
	static bool isNop(const Tree::IStm* a);

	// ����� ���������� ���������� ����������� ���������, ���� ����� ����������.
	// ������: 
	// ����: a+=1 � 5. �����: a+=1;
	// ����: a+=1 � b*=2. �����: SEQ(a+=1, b*=2)
	static const Tree::IStm* simplifySeq(const Tree::IStm* a, const Tree::IStm* b);

	// ����� ���������, ���������� �� a � b
	// �.�. �������� �� �� ��������� ����� ���� a � b
	// ���� ���������� - �� ������ ������� �����
	static bool commute(const Tree::IStm* a, const Tree::IExp* b);

	// do_stm - ������� �������������� ���������
	// ����� �������������� SEQ
	// ������ �������� do_stm �� �����
	static const Tree::IStm* do_stm(const Tree::SEQ* s);

	// ����� �������������� MOVE
	// ���� � ��� ����������� ���� ������ ���������� ������ ������� � ���������� - 
	// �������� reorder_stm �� CMoveCall � ����������� TEMP � CALL;
	// ���� ����� ������ - ESEQ - ����������� ��� � ������������������, ������ �������� stm �� ESEQ, 
	// � ����� ��������� � exp �� ESEQ exp �� MOVE, � ����� �������� ��������������� ������������ ���������;
	// ����� - �������� reorder_stm �� MOVE
	static const Tree::IStm* do_stm(const Tree::MOVE* s); 

	// ����� �������������� EXP
	// ���� ������ ����� ������� - �������� reorder_stm �� CExpCall � ���������� CALL
	// ����� - �������� reorder_stm �� EXP
	static const Tree::IStm* do_stm(const Tree::EXP* s);

	// ����� �������������� Stm
	// �������� ��������������� ��������������, ���� ��� Stm ��������,
	// ����� - �������� reorder_stm �� Stm
	static const Tree::IStm* do_stm(const Tree::IStm* s);

	// �����, ������������� Stm, ������ ��� ������������ � ��� �������� ������
	static const Tree::IStm* reorder_stm(const Tree::IStm* s);

	// do_exp - ������� �������������� Exp
	// ����� �������������� ESEQ
	// ��������������� Exp � Stm, ������������ � ESEQ � ���������� ���������� ESEQ
	static const Tree::ESEQ* do_exp(const Tree::ESEQ* e);

	// ����� �������������� Exp � ESEQ
	// � ������ ESEQ �������� �-�� �������������� ��������
	// ����� - �������� reorder_exp �� Exp
	static const Tree::ESEQ* do_exp(const Tree::IExp* e);

	// �����, ������������� Exp, ������ ��� ������������ � ��� �������� ������
	static const Tree::ESEQ* reorder_exp(const Tree::IExp* e);

	// �����, ��������� ������ ��� ��������, ������������ � ����� ��-��� ExpList
	static const CStmExpList* reorder(const Tree::ExpList* exps);
	   
	// ����� ������������ SEQ
	// ���������� ��������� ��� s.left, s.right, StmList
	static const Tree::StmList* linear(const Tree::SEQ* s, const Tree::StmList* l);

	// ����� ������������ ������ ���������
	// �� ������ �������� ������������������ �������� ���� s1, s2, s3 ... 
	static const Tree::StmList* linear(const Tree::IStm* s, const Tree::StmList* l);

	// ����� ������������ ���������
	static const Tree::StmList* linearize(const Tree::IStm* s);
private:
	// ������ ������, ��������� ���������� ������
	static CStmExpList* nopNull;
};

} // End of Canon