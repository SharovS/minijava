#include "Canon.h"

namespace Canon
{

	// Пустой список, временная переменная класса Canon
	CStmExpList* CCanon::nopNull = new CStmExpList( new Tree::EXP( new Tree::CONST( 0 ) ), 0 );

	//-------------------------------------------------------------------//

	// возвращаем Tree::ExpList, состоящий из Exp и ExpList, находящегося в CALL
	const Tree::ExpList* CMoveCall::Kids() const
	{
		return src->Kids();
	}

	// составляем заного вызов функции с помещением значения во временную переменную
	const Tree::IStm* CMoveCall::Build( const Tree::ExpList* kids ) const
	{
		return new Tree::MOVE( dst, src->Build( kids ) );
	}

	//-------------------------------------------------------------------//

	// возвращаем Tree::ExpList, состоящий из Exp и ExpList, находящегося в CALL
	const Tree::ExpList* CExpCall::Kids() const
	{
		return call->Kids();
	}

	// составляем заного вызов функции с игнорированием возвращаемого значения
	const Tree::IStm* CExpCall::Build( const Tree::ExpList* kids ) const
	{
		return new Tree::EXP( call->Build( kids ) );
	}

	//-------------------------------------------------------------------//

	// Метод проверяет, является ли выражение stm от константы
	// Пример: 5;
	bool CCanon::isNop( const Tree::IStm* a )
	{
		return dynamic_cast<const Tree::EXP*>(a) != 0
			&& dynamic_cast<const Tree::CONST*>((dynamic_cast<const Tree::EXP*>(a))->getExp()) != 0;
	}

	// Метод возвращает упрощенную конструкцию выражений, если такая существует.
	// Пример: 
	// Вход: a+=1 и 5. Выход: a+=1;
	// Вход: a+=1 и b*=2. Выход: SEQ(a+=1, b*=2)
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

	// Метод проверяет, комутируют ли a и b
	// Т.е. повлияет ли на результат смена мест a и b
	// Если комутируют - то менять местами можно
	bool CCanon::commute( const Tree::IStm* a, const Tree::IExp* b )
	{
		return isNop( a )
			|| dynamic_cast<const Tree::NAME*>(b) != 0
			|| dynamic_cast<const Tree::CONST*>(b) != 0;
	}

	// do_stm - функции преобразования выражений
	// Метод преобразования SEQ
	// просто вызывает do_stm от детей
	const Tree::IStm* CCanon::do_stm( const Tree::SEQ* s )
	{
		return simplifySeq( do_stm( s->getLeftStm() ), do_stm( s->getRightStm() ) );
	}

	// Метод преобразования MOVE
	// Если у нас конструкция вида запись результата вызова функции в переменную - 
	// вызываем reorder_stm от CMoveCall с аргументами TEMP и CALL;
	// Если место записи - ESEQ - преобразуем его в последовательность, сперва выполняя stm из ESEQ, 
	// а потом записывая в exp из ESEQ exp из MOVE, и снова пытаемся преобразовывать получившееся выражение;
	// Иначе - вызываем reorder_stm от MOVE
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

	// Метод преобразования EXP
	// Если внутри вызов функции - вызываем reorder_stm от CExpCall с аргументом CALL
	// Иначе - вызываем reorder_stm от EXP
	const Tree::IStm* CCanon::do_stm( const Tree::EXP* s )
	{
		if( dynamic_cast<const Tree::CALL*>(s->getExp()) != 0 ) {
			return reorder_stm( new CExpCall( dynamic_cast<const Tree::CALL*>(s->getExp()) ) );
		} else {
			return reorder_stm( s );
		}
	}

	// Метод преобразования Stm
	// Вызываем соответствующее преобразование, если тип Stm подходит,
	// Иначе - вызываем reorder_stm от Stm
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

	// Метод, преобразующий Stm, вынося все производимые в нем действия наверх
	const Tree::IStm* CCanon::reorder_stm( const Tree::IStm* s )
	{
		if( s == 0 ) {
			return 0;
		}
		// выносим все действия наружу в x.stm
		const CStmExpList* x = reorder( s->Kids() );
		// упрощаем, если возможно
		return simplifySeq( x->stm, s->Build( x->exps ) );
	}

	// do_exp - функции преобразования Exp
	// Метод преобразования ESEQ
	// Преобразовывает Exp и Stm, содержащийся в ESEQ и возвращаем упрощенный ESEQ
	const Tree::ESEQ* CCanon::do_exp( const Tree::ESEQ* e )
	{
		const Tree::IStm* stms = do_stm( e->getStm() );
		const Tree::ESEQ* b = do_exp( e->getExp() );
		return new Tree::ESEQ( simplifySeq( stms, b->getStm() ), b->getExp() );
	}

	// Метод преобразования Exp к ESEQ
	// В случае ESEQ вызываем ф-ию преобразования отдельно
	// Иначе - вызываем reorder_exp от Exp
	const Tree::ESEQ* CCanon::do_exp( const Tree::IExp* e )
	{
		if( dynamic_cast<const Tree::ESEQ*>(e) != 0 ) {
			return do_exp( dynamic_cast<const Tree::ESEQ*>(e) );
		} else {
			return reorder_exp( e );
		}
	}

	// Метод, преобразующий Exp, вынося все производимые в нем действия наверх
	const Tree::ESEQ* CCanon::reorder_exp( const Tree::IExp* e )
	{
		// выносим все действия наружу в x.stm
		const CStmExpList* x = reorder( e->Kids() );
		// Возвращаем ESEQ
		return new Tree::ESEQ( x->stm, e->Build( x->exps ) );
	}

	// Метод, выносящий наружу все действия, производимые в любых эл-тах ExpList
	const CStmExpList* CCanon::reorder( const Tree::ExpList* exps )
	{
		// Возвращаем пустой список, если нет исходного списка
		if( exps == 0 ) {
			return nopNull;
		} else {
			const Tree::IExp* a = exps->getTop();
			if( dynamic_cast<const Tree::CALL*>(a) != 0 ) {
				// Если 1 элемент списка - вызов функции, 
				// то записываем возвращаемое значение во временную переменную и возвращаем ее
				Temp::CTemp* t = new Temp::CTemp();
				Tree::IExp* e = new Tree::ESEQ( new Tree::MOVE( new Tree::TEMP( t ), a ),
					new Tree::TEMP( t ) );
				// Продолжаем обход с заного составленной ESEQ
				return reorder( new Tree::ExpList( e, exps->getTail() ) );
			} else {
				// Преобразуем Exp к ESEQ, попутно упрощая все содержимое
				const Tree::ESEQ* aa = do_exp( a );
				// Преобразуем остальную часть списка
				const CStmExpList* bb = reorder( exps->getTail() );
				if( commute( bb->stm, aa->getExp() ) ) {
					// Если комутируют - значит получаем готовый список
					return new CStmExpList( simplifySeq( aa->getStm(), bb->stm ),
						new Tree::ExpList( aa->getExp(), bb->exps ) );
				} else {
					// Если не комутируют - упрощаем aa, bb 
					// и производим запись значения во временную переменную
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

	// Метод линеаризации SEQ
	// Записываем выражение как s.left, s.right, StmList
	const Tree::StmList* CCanon::linear( const Tree::SEQ* s, const Tree::StmList* l )
	{
		return linear( s->getLeftStm(), linear( s->getRightStm(), l ) );
	}

	// Метод линеаризации списка выражений
	// На выходе получаем последовательность действий типа s1, s2, s3 ... 
	const Tree::StmList* CCanon::linear( const Tree::IStm* s, const Tree::StmList* l )
	{
		if( dynamic_cast<const Tree::SEQ*>(s) != 0 ) {
			return linear( dynamic_cast<const Tree::SEQ*>(s), l );
		} else {
			return new Tree::StmList( s, l );
		}
	}

	// Метод линеаризации выражения
	const Tree::StmList* CCanon::linearize( const Tree::IStm* s )
	{
		if( s == 0 ) {
			return 0;
		} else {
			return linear( do_stm( s ), 0 );
		}
	}

} // End of Canon