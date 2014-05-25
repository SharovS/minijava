#include <Tree.h>
#include <Temp.h>

//--------------------------------------------------- от IExp
class BINOP : public Tree::IExp {
public:
	BINOP(int _binop, Tree::IExp* _left, Tree::IExp* _right) : binop(_binop), left(_left), right(_right) {} 
	Tree::ExpList kids()  
	{
		return Tree::ExpList(left, Tree::ExpList(right,0));
	}
	Tree::Exp build(Tree::ExpList kids)
	{
		return BINOP(binop, kids.head, kids.tail.head);
	}
	enum T_Binop//?????????????????????????????????
	{
		PLUS,
		MINUS,
		MUL,
		DIV,
		AND,
		OR,
		LSHIFT,
		RSHIFT,
		ARSHIFT,
		XOR
	}
private:
	int binop;
    Tree::IExp* left;
	Tree::IExp* right;
};

class CALL : public  Tree::IExp {
public:
	CALL(Tree::IExp* _func, Tree::ExpList* _args) : func(_func), args(_args) {}
	Tree::ExpList kids(){
		return Tree::ExpList(func,args);
	}
	Tree::IExp build(Tree::ExpList kids){
		return CALL(kids.head,kids.tail);
	}
private:  
	Tree::IExp* func;
    Tree::ExpList* args;
};

class CONST : public Tree::IExp{
public:
	CONST(int _value) : value(_value) {}
	Tree::ExpList kids(){
		return 0;
	}
	Tree::IExp build(Tree::ExpList kids){
		return this;
	}
private: 
	int value;
};

class ESEQ : public Tree::IExp{
public: 
	ESEQ(Tree::IStm* _stm, Tree::IExp* _exp) : stm(_stm), exp(_exp) {}
	Tree::ExpList kids(){
		printf("Error: kids() not applicable to ESEQ");
	}
	Tree::IExp build(Tree::ExpList kids){
		printf("Error: build() not applicable to ESEQ");
	}
private:
	Tree::IStm* stm;
	Tree::IExp* exp;
};

class MEM : public Tree::IExp{
public:
	MEM(Tree::Exp* _exp) : exp(_exp) {}
	Tree::ExpList kids(){
		return Tree::ExpList(exp, 0);
	}
	Tree::IExp build(Tree::ExpList kids)
	{
		return MEM(kids.GetHead());
	}
private:
	Tree::IExp* exp;
};

class NAME : public Tree::IExp
{
public:
	NAME(std::string _label) label(_label) {}
	ExpList kids(){
		return 0;
	}
	Tree::IExp build(Tree::ExpList kids){
		return this;
	}
	std::string getLabel()//????????? Были паблик, надо ли их получать?
	{
		return label;
	}
private:
	strd::string label;
};

class TEMP : public Tree::IExp{
public:
	TEMP(Temp::CTemp* _temp) : temp(_temp) {}
	Tree::ExpList kids(){
		return 0;
	}
	Tree::IExp build(Tree::ExpList kids){
		return this;
	}
private:
	Temp::CTemp* temp;
};

//--------------------------------------------------- от IStm
class CJUMP : Tree::IStm {
public:
	CJUMP(int _relop, Tree::IExp* _left, Tree::IExp* _right, std::string _iftrue, std::string _iffalse) : 
	  relop(_relop), left(_left), right(_right), iftrue(_iftrue), iffalse(_iffalse) {}
  
    Tree::ExpList kids(){
		return Tree::ExpList(left, Tree::ExpList(right, 0));
	}
	Tree::IStm build(Tree::ExpList kids){
		return Tree::CJUMP(relop, kids.head, kids.tail.head, iftrue, iffalse);
	}
	enum T_Cjump
	{
		EQ, NE, LT,
		GT, LE, GE,
		ULT, ULE,
		UGT, UGE
	}

	static int notRel(int relop) {
		switch (relop) {
			case EQ:  
				return NE;
			case NE:  
				return EQ;
			case LT: 
				return GE;
			case GE:  
				return LT;
			case GT: 
				return LE;
			case LE:
				return GT;
			case ULT:
				return UGE;
			case UGE:
				return ULT;
			case UGT:
				return ULE;
			case ULE: 
				return UGT;
			//default: throw new Error("bad relop in CJUMP.notRel");
		}
   }
private:
	int relop;
	Tree::IExp* left;
	Tree::IExp* right;
	std::string iftrue;
	std::string iffalse;
};

class EXP : public Tree::IStm {
public: 
	EXP(Tree::IExp* _exp) : exp(_exp) {}
	ExpList kids(){
		return Tree::ExpList(exp,null);
	}
	Tree::IStm build(Tree::ExpList kids){
		return EXP(kids.head);
	}
private:
	Tree::IExp* exp;
};

class JUMP : public Tree::IStm {
public:
	JUMP(Tree::IExp* _exp, Temp::CLabelList* _targets) : exp(e), targets(_targets) {}
	JUMP(Temp::CLabel _target){//??????????????????????????????????????????????????
		//this(new NAME(_target), new Temp.LabelList(_target,0));
	}
	Tree::ExpList kids(){
		return ExpList(exp,null);
	}
	Tree::IStm build(Tree::ExpList kids){
		return JUMP(kids.head, targets);
	}
private:
	Tree::IExp* exp;
	Temp::CLabelList* targets;
};

class LABEL : public Tree::IStm{
public:
	LABEL(std::string _label) : label(_label) {}
	Tree::ExpList kids(){
		return 0;
	}
	Tree::IStm build(Tree::ExpList kids){
		return this;
	}
	std::string getLabel(){
		return label;
	}
private:
	std::string label;
};

class MOVE : public Tree::IStm{
public:
	MOVE(Tree::IExp* _dst, Tree::IExp* _src) : dst(_dst), src(_src) {}
	Tree::ExpList kids(){
		if (dynamic_cast<*MEM>& dst)
		{//пойдет? было dst instanceof  MEM
			return Tree::ExpList(((MEM)dst).exp, Tree::ExpList(src, 0));
		}
		else
		{
			return Tree::ExpList(src, 0);
		}
	}
	Tree::IStm build(Tree::ExpList kids){
		if (dynamic_cast<*MEM>&dst)
		{//пойдет? было dst instanceof  MEM
			return new MOVE(MEM(kids.head), kids.tail.head);
		}
		else
		{
			return MOVE(dst, kids.head);
	    }
	}
private:
	Tree::IExp* dst;
	Tree::IExp* src;
};


class SEQ : public Tree::IStm{
public:
	SEQ(Tree::IStm* _left, Tree::Stm* _right) : left(_left), right(_right) {}
	Tree::ExpList kids() {
		printf("Error: kids() not applicable to SEQ");
		return 0;
	}
	Tree::Stm build(ExpList kids) {
		printf("Error: build() not applicable to SEQ");
		return 0;
	}
private:
	Tree::IStm* left;
	Tree::IStm* right;
};