#pragma once
#include "Temp.h"
#include "Tree.h"

namespace Canon
{

//-------------------------------------------------------------------//

// Помещаем объект типа CALL и Временную переменную, куда заносим значение
// т.е. вызов с записью значения во временную переменную
class CMoveCall : public Tree::IStm {
public:
	// Конструктор
	CMoveCall(const Tree::TEMP* _dst, const Tree::CALL* _src) : dst(_dst), src(_src) {}
	// возвращаем Tree::ExpList, состоящий из Exp и ExpList, находящегося в CALL
	virtual const Tree::ExpList* Kids() const;
	// составляем заного вызов функции с помещением значения во временную переменную
	virtual const Tree::IStm* Build(const Tree::ExpList* kids) const;
private:
	const Tree::TEMP* dst;
	const Tree::CALL* src;
};   
  
//-------------------------------------------------------------------//

// Делаем то-же самое, что и примером выше, только оболочка EXP 
// (т.е. возвращаемое значение отбрасывается)
class CExpCall : public Tree::IStm {
public:
	// Конструктор
	CExpCall(const Tree::CALL* _call) : call(_call) {}
	// возвращаем Tree::ExpList, состоящий из Exp и ExpList, находящегося в CALL
	virtual const Tree::ExpList* Kids() const;
	// составляем заного вызов функции с игнорированием возвращаемого значения
	virtual const Tree::IStm* Build(const Tree::ExpList* kids) const;
private:
	const Tree::CALL* call;
};   
  
//-------------------------------------------------------------------//

// Список работы для аргументов
// Т.е. в классе содержится чистый ExpList(только переменные, никаких действий)
// и stm - все те действия, которые необходимо совершить до вызова функции с этими аргументами
struct CStmExpList {
	// Конструктор
	CStmExpList(const Tree::IStm* _stm, const Tree::ExpList* _exps) : stm(_stm), exps(_exps) {}

	const Tree::IStm* stm;
	const Tree::ExpList* exps;
};

//-------------------------------------------------------------------//

class CCanon {
public:
	// Метод проверяет, является ли выражение stm от константы
	// Пример: 5;
	static bool isNop(const Tree::IStm* a);

	// Метод возвращает упрощенную конструкцию выражений, если такая существует.
	// Пример: 
	// Вход: a+=1 и 5. Выход: a+=1;
	// Вход: a+=1 и b*=2. Выход: SEQ(a+=1, b*=2)
	static const Tree::IStm* simplifySeq(const Tree::IStm* a, const Tree::IStm* b);

	// Метод проверяет, комутируют ли a и b
	// Т.е. повлияет ли на результат смена мест a и b
	// Если комутируют - то менять местами можно
	static bool commute(const Tree::IStm* a, const Tree::IExp* b);

	// do_stm - функции преобразования выражений
	// Метод преобразования SEQ
	// просто вызывает do_stm от детей
	static const Tree::IStm* do_stm(const Tree::SEQ* s);

	// Метод преобразования MOVE
	// Если у нас конструкция вида запись результата вызова функции в переменную - 
	// вызываем reorder_stm от CMoveCall с аргументами TEMP и CALL;
	// Если место записи - ESEQ - преобразуем его в последовательность, сперва выполняя stm из ESEQ, 
	// а потом записывая в exp из ESEQ exp из MOVE, и снова пытаемся преобразовывать получившееся выражение;
	// Иначе - вызываем reorder_stm от MOVE
	static const Tree::IStm* do_stm(const Tree::MOVE* s); 

	// Метод преобразования EXP
	// Если внутри вызов функции - вызываем reorder_stm от CExpCall с аргументом CALL
	// Иначе - вызываем reorder_stm от EXP
	static const Tree::IStm* do_stm(const Tree::EXP* s);

	// Метод преобразования Stm
	// Вызываем соответствующее преобразование, если тип Stm подходит,
	// Иначе - вызываем reorder_stm от Stm
	static const Tree::IStm* do_stm(const Tree::IStm* s);

	// Метод, преобразующий Stm, вынося все производимые в нем действия наверх
	static const Tree::IStm* reorder_stm(const Tree::IStm* s);

	// do_exp - функции преобразования Exp
	// Метод преобразования ESEQ
	// Преобразовывает Exp и Stm, содержащийся в ESEQ и возвращаем упрощенный ESEQ
	static const Tree::ESEQ* do_exp(const Tree::ESEQ* e);

	// Метод преобразования Exp к ESEQ
	// В случае ESEQ вызываем ф-ию преобразования отдельно
	// Иначе - вызываем reorder_exp от Exp
	static const Tree::ESEQ* do_exp(const Tree::IExp* e);

	// Метод, преобразующий Exp, вынося все производимые в нем действия наверх
	static const Tree::ESEQ* reorder_exp(const Tree::IExp* e);

	// Метод, выносящий наружу все действия, производимые в любых эл-тах ExpList
	static const CStmExpList* reorder(const Tree::ExpList* exps);
	   
	// Метод линеаризации SEQ
	// Записываем выражение как s.left, s.right, StmList
	static const Tree::StmList* linear(const Tree::SEQ* s, const Tree::StmList* l);

	// Метод линеаризации списка выражений
	// На выходе получаем последовательность действий типа s1, s2, s3 ... 
	static const Tree::StmList* linear(const Tree::IStm* s, const Tree::StmList* l);

	// Метод линеаризации выражения
	static const Tree::StmList* linearize(const Tree::IStm* s);
private:
	// Пустой список, временная переменная класса
	static CStmExpList* nopNull;
};

} // End of Canon