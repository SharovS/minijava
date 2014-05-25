#pragma once
#include <stdio.h>

//какая-то предыдущая штука, которой у нас нет, а она оказывается нужна

public class Label  {
private: String name;
		 static int count;
public:
	Label(String _name) : name(_name) {}
	Label() {this("L" + count++);}
	String toString() {return name;}
}

public class Temp  {
   private static int count;
   private int num;
   public String toString() {return "t" + num;}
   public Temp() { 
     num=count++;
   }
}


//собственно куски дерева

class Stm
{
public:
	virtual ExpList kids()=0 {};
	virtual Stm build(ExpList kids)=0 {};
}
class StmList
{
public:
	Stm head;
	StmList tail;
	StmList(Stm _head, StmList _tail) : head(_head), tail(_tail) {}
}

class LABEL : public Stm{
public:
	LABEL(Label _label) : label(_label) {}
	ExpList kids () {return 0;};
	Stm build (ExpList kids) {return this;};
private:
	Lable label;
}
class MEM : public Exp{
public:
	MEM( Exp _exp) : exp(_exp) {}
	ExpList kids() {return (new ExpList(exp,null));};
	Exp build(ExpList kids)
	{
		return new MEM (kids.GetHead());
	}
private:
	Exp exp;
}
class MOVE : public Stm{
public:
	MOVE(Exp _dst, Exp _src) : dst(_dst), src(_src) {}
	ExpList kids() {
		if (dynamic_cast<*MEM>&dst) //пойдет? было dst instanceof  MEM
			return new ExpList(((MEM)dst).exp, new ExpList(src,null))
		else return new ExpList(src,null);
	};
	Stm build(ExpList kids) {
		if (dynamic_cast<*MEM>&dst) //пойдет? было dst instanceof  MEM
			return new MOVE(new MEM(kids.head), kids.tail.head)
		else return new MOVE(dst, kids.head);
  }
private:
	Exp dst, src;
}
class NAME : public Exp
{
public:
	string label;
	NAME(string _label) label(_label) {}
	ExpList kids() {return null;}
	Exp build(ExpList kids) {return this;}
}

class SEQ : public Stm{
public:
	Stm left, right;
	SEQ(Stm _left, Stm _right) : left(_left), right(_right) {}
	ExpList kids() {
		printf("kids() not applicable to SEQ");
		return 0;
	}
	Stm build(ExpList kids) {
		printf("build() not applicable to SEQ");
		return 0;
	}
}


class TEMP : public Exp{
public:
	TEMP(Temp.Temp _temp) : temp(_temp) {}
	ExpList kids() {return null;}
	Exp build(ExpList kids) {return this;}
	Temp.Temp temp;
}

class Print
{
 java.io.PrintStream out; //WTH?
 Temp.TempMap tmap; //WTH?

  public Print(java.io.PrintStream o, Temp.TempMap t) {out=o; tmap=t;}

  public Print(java.io.PrintStream o) {out=o; tmap=new Temp.DefaultMap();}

  void indent(int d) {
      for(int i=0; i<d; i++) 
            out.print(' ');
  }

  void say(String s) {
            out.print(s);
  }

  void sayln(String s) {
	say(s); say("\n");
  }

  void prStm(SEQ s, int d) {
      indent(d); sayln("SEQ("); prStm(s.left,d+1); sayln(",");
      prStm(s.right,d+1); say(")");
  }

  void prStm(LABEL s, int d) {
      indent(d); say("LABEL "); say(s.label.toString());
  }

  void prStm(JUMP s, int d) {
      indent(d); sayln("JUMP("); prExp(s.exp, d+1); say(")");
  }

  void prStm(CJUMP s, int d) {
      indent(d); say("CJUMP("); 
      switch(s.relop) {
        case CJUMP.EQ: say("EQ"); break;
        case CJUMP.NE: say("NE"); break;
        case CJUMP.LT: say("LT"); break;
        case CJUMP.GT: say("GT"); break;
        case CJUMP.LE: say("LE"); break;
        case CJUMP.GE: say("GE"); break;
        case CJUMP.ULT: say("ULT"); break;
        case CJUMP.ULE: say("ULE"); break;
        case CJUMP.UGT: say("UGT"); break;
        case CJUMP.UGE: say("UGE"); break;
	default:
         throw new Error("Print.prStm.CJUMP");
       }
       sayln(","); prExp(s.left,d+1); sayln(",");
       prExp(s.right,d+1); sayln(",");
       indent(d+1); say(s.iftrue.toString()); say(","); 
       say(s.iffalse.toString()); say(")");
  }

  void prStm(MOVE s, int d) {
     indent(d); sayln("MOVE("); prExp(s.dst,d+1); sayln(","); 
           prExp(s.src,d+1); say(")");
  }

  void prStm(EXP s, int d) {
     indent(d); sayln("EXP("); prExp(s.exp,d+1); say(")"); 
  }

  void prStm(Stm s, int d) {
        if (s instanceof SEQ) prStm((SEQ)s, d);
   else if (s instanceof LABEL) prStm((LABEL)s, d);
   else if (s instanceof JUMP) prStm((JUMP)s, d);
   else if (s instanceof CJUMP) prStm((CJUMP)s, d);
   else if (s instanceof MOVE) prStm((MOVE)s, d);
   else if (s instanceof EXP) prStm((EXP)s, d);
   else throw new Error("Print.prStm");
  }

  void prExp(BINOP e, int d) {
     indent(d); say("BINOP("); 
      switch(e.binop) {
	case BINOP.PLUS: say("PLUS"); break;
	case BINOP.MINUS: say("MINUS"); break;
	case BINOP.MUL: say("MUL"); break;
	case BINOP.DIV: say("DIV"); break;
	case BINOP.AND: say("AND"); break;
	case BINOP.OR: say("OR"); break;
	case BINOP.LSHIFT: say("LSHIFT"); break;
	case BINOP.RSHIFT: say("RSHIFT"); break;
	case BINOP.ARSHIFT: say("ARSHIFT"); break;
	case BINOP.XOR: say("XOR"); break;
	default:
         throw new Error("Print.prExp.BINOP");
       }
      sayln(",");
      prExp(e.left,d+1); sayln(","); prExp(e.right,d+1); say(")");
   }

  void prExp(MEM e, int d) {
     indent(d);
	sayln("MEM("); prExp(e.exp,d+1); say(")");
  }

  void prExp(TEMP e, int d) {
     indent(d); say("TEMP "); 
     say(tmap.tempMap(e.temp));
  }

  void prExp(ESEQ e, int d) {
     indent(d); sayln("ESEQ("); prStm(e.stm,d+1); sayln(",");
	prExp(e.exp,d+1); say(")");

  }

  void prExp(NAME e, int d) {
     indent(d); say("NAME "); say(e.label.toString());
  }

  void prExp(CONST e, int d) {
     indent(d); say("CONST "); say(String.valueOf(e.value));
  }

  void prExp(CALL e, int d) {
     indent(d); sayln("CALL(");
	prExp(e.func,d+1);
        for(ExpList a = e.args; a!=null; a=a.tail) {
           sayln(","); prExp(a.head,d+2); 
        }
        say(")");
  }

  void prExp(Exp e, int d) {
        if (e instanceof BINOP) prExp((BINOP)e, d);
   else if (e instanceof MEM) prExp((MEM)e, d);
   else if (e instanceof TEMP) prExp((TEMP)e, d);
   else if (e instanceof ESEQ) prExp((ESEQ)e, d);
   else if (e instanceof NAME) prExp((NAME)e, d);
   else if (e instanceof CONST) prExp((CONST)e, d);
   else if (e instanceof CALL) prExp((CALL)e, d);
   else throw new Error("Print.prExp");
  }

  public void prStm(Stm s) {prStm(s,0); say("\n");}
  public void prExp(Exp e) {prExp(e,0); say("\n");}

}

