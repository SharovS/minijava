#include <TypeCheckerVisitor.h>
#include <string>
#include <assert.h>
#include <SymbolTable.h>

//MainClass ClassDeclList

void CTypeCheckerVisitor::Visit( const CProgram& p )
{
	p.GetMainClass()->Accept( this );
	if( p.GetClassDeclList() != 0 ) {
		p.GetClassDeclList()->Accept( this );
	}
}

//class id { public static void main ( String [] id ) { Statement }}

void CTypeCheckerVisitor::Visit( const CMainClass& p )
{
	table->EnterClass( table->FindClass( p.GetIdFirst() ) );
	CClass* currClass( table->getCurrClass() );
	table->EnterMethod( currClass->FindMethod( "main", table ) );
	p.GetStm()->Accept( this );
	table->LeaveMethod();
	table->LeaveClass();
}

//class id { VarDeclList MethodDeclList }

void CTypeCheckerVisitor::Visit( const CClassDecl& p )
{
	table->EnterClass( table->FindClass( p.GetId() ) );
	//p.GetVarDeclList()->Accept(this);
	if( p.GetMethodDeclList() ) {
		p.GetMethodDeclList()->Accept( this );
	}
	table->LeaveClass();
}

//class id extends id { VarDeclList MethodDeclList }

void CTypeCheckerVisitor::Visit( const CExClassDecl& p )
{
	//p.GetVarDeclList()->Accept(this);
	table->EnterClass( table->FindClass( p.GetId() ) );
	p.GetMethodDeclList()->Accept( this );
	table->LeaveClass();
}

//Type id

void CTypeCheckerVisitor::Visit( const CVarDecl& p )
{
	//p.GetId ищем в таблице table
	assert( false );
}

//Type id = Exp

void CTypeCheckerVisitor::Visit( const CVarDeclExp& p ) 
{
	CVar* var = new CVar( p.GetType(), p.GetId(), 0 );
	if(table->getCurrClass() == 0 ) {
		assert( false );
	} else if( table->getCurrMethod() == 0 ) {
		table->getCurrClass()->addVar( var );
	} else {
		table->getCurrMethod()->addLoc( var );
	}

	p.GetExp()->Accept( this );
	std::string st = p.GetType();
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ne to vernyli!!!!!!
	//std::string st( table->Lookup( p.GetId() ) );
	if( lastType != st ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error in assignment: different types of id (%s) & Exp (%s) \n"
			" Location: id %s, method %s in Class %s\n\n", st.c_str(), lastType.c_str(),
			(p.GetId()).c_str(), mN, cN );
		assert( false );
	}


}


//public Type id ( FormalList ) { VarDecl* Statement* return Exp ;}

void CTypeCheckerVisitor::Visit( const CMethodDecl& p )
{
	//p.GetType() p.GetExp().GetType() //что-то такое
	//p.GetVarDeclList()->Accept(this);
	CClass* currClass( table->getCurrClass() );
	table->EnterMethod( currClass->FindMethod( p.GetId(), table ) );
	//p.GetFormalList()->Accept(this); //это по€вл€етс€ при построении таблицы

	if( p.GetStmList() ) {
		p.GetStmList()->Accept( this );
	}
	p.GetExp()->Accept( this );
	if( lastType != p.GetType() ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error in method: different retern value & expected value \n Location: method %s in Class %s\n\n", mN, cN );
	}
	table->LeaveMethod();
}

//{ Statement* }

void CTypeCheckerVisitor::Visit( const CCompStm& p )
{
	p.GetStmList()->Accept( this );
}

//if ( Exp ) Statement else Statement

void CTypeCheckerVisitor::Visit( const CIfStm& p )
{
	p.GetExp()->Accept( this );//ƒолжен быть bool
	if( lastType != "boolean" ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error in If(Exp): incorrect type of Exp \n Location: method %s in Class %s\n\n", mN, cN );
	}
	p.GetStmFirst()->Accept( this );
	p.GetlStmSecond()->Accept( this );
}

//while ( Exp ) Statement

void CTypeCheckerVisitor::Visit( const CWhStm& p )
{
	p.GetExp()->Accept( this );//ƒолжен быть bool
	if( lastType != "boolean" ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error in while(Exp): incorrect type of Exp \n Location: method %s in Class %s\n\n", mN, cN );
	}
	p.GetStm()->Accept( this );
}

//System.out.println ( Exp ) ;

void CTypeCheckerVisitor::Visit( const CSOPStm& p )
{
	p.GetExp()->Accept( this );
	if( lastType != "int" && lastType != "string" ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error in System.out.println(Exp): incorrect type of Exp \n Location: method %s in Class %s\n\n", mN, cN );
	}
}

//id = Exp ;

void CTypeCheckerVisitor::Visit( const CAsStm& p )
{
	p.GetExp()->Accept( this );
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ne to vernyli!!!!!!
	std::string st( table->Lookup( p.GetId() ) );
	if( lastType != st ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error in assignment: different types of id (%s) & Exp (%s) \n"
			" Location: id %s, method %s in Class %s\n\n", st.c_str(), lastType.c_str(),
			(p.GetId()).c_str(), mN, cN );
		assert( false );
	}
}

//id [ Exp ] = Exp// проверить, чито тип ID - int[]

void CTypeCheckerVisitor::Visit( const CAsExpStm& p )
{
	p.GetExpFirst()->Accept( this );
	if( lastType != "int" ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error in access to %s -s element: incorrect type\n -Location: id %s, method %s in Class %s\n\n",
			p.GetId(), p.GetId(), mN, cN );
	}
}

//Exp op Exp

void CTypeCheckerVisitor::Visit( const COpExp& p )
{
	p.GetExpFirst()->Accept( this );
	std::string firstExpType( lastType );
	p.GetExpSecond()->Accept( this );
	if( firstExpType != lastType ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error: different types of Exp-s in (Exp op Exp)\n -Location: method %s in class %s\n\n", mN, cN );
		assert( false );
	} else if( (p.GetOp() == B_And) && (lastType != "boolean") ) {
		//как определить где какой знак?!?!
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error: unexpected types(%s) of Exp-s in (Exp && Exp)\n -Location: method %s in class %s\n\n",
			lastType, mN, cN );
		assert( false );
	} else if( p.GetOp() == B_Less && lastType == "int" ) {
		lastType = "boolean";
	} else if( lastType != "int" && lastType != "boolean" ) {
		//кроме интов с чем еще можно операции производить?!
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error: unexpected types(%s) of Exp-s in (Exp && Exp)\n -Location: method %s in class %s\n\n",
			lastType, mN, cN );
		assert( false );
	}
	//else
	//{
	//	lastType = "int";
	//}
}

//Exp [ Exp ]

void CTypeCheckerVisitor::Visit( const CExExp& p )
{
	p.GetExpFirst()->Accept( this );
	if( lastType != "int[]" ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error: type of Exp1 isn't \"int []\", it's \"%s\"\n -Location: method %s in class %s\n\n",
			lastType.c_str(), mN, cN );
	}
	p.GetExpSecondn()->Accept( this );
	if( lastType != "int" ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error: type of Exp2 isn't \"int\", it's \"%s\"\n -Location: method %s in class %s\n\n",
			lastType, mN, cN );
	}
}

//Exp . length

void CTypeCheckerVisitor::Visit( const CLenExp& p )
{
	p.GetExp()->Accept( this );
	if( lastType != "int[]" ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error: type of Exp isn't \"int []\", it's \"%s\"\n -Location: method %s in class %s\n\n",
			lastType, mN, cN );
	}
	lastType = "int";
}

//Exp . id ( ExpList )

void CTypeCheckerVisitor::Visit( const CIdClExp& p )
{
	p.GetExp()->Accept( this );
	if( (lastType != "") && (lastType != "int") && (lastType != "int[]") && (lastType != "boolean") ) {
		//CClass* currClass(table->getCurrClass());
		//CMethod* currMethod(currClass->FindMethod(p.GetId())); //“”“!!!!
		if( table->FindClass( lastType ) != 0 ) {
			CClass* currClass( table->FindClass( lastType ) );
			if( currClass->FindMethod( p.GetId(), table ) != 0 ) {
				CMethod* currMethod( currClass->FindMethod( p.GetId(), table ) );
				//указатель на 1ый элемент параметров
				varList = currMethod->getPar();
				counter = 0;
				std::string st( lastType );
				if( p.GetExpList() ) {
					p.GetExpList()->Accept( this );
				}

				lastType = currMethod->getType();
			} else {
				isError = true;
			}
		} else {
			isError = true;
		}
	} else {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error: Exp isn't a class, it's \"%s\"\n -Location: method %s in class %s\n\n",
			lastType, mN, cN );
	}
}

//num

void CTypeCheckerVisitor::Visit( const CNExp& p )
{
	lastType = "int";
}

void CTypeCheckerVisitor::Visit( const CStrExp& p )
{
	lastType = "string";
}

//true

void CTypeCheckerVisitor::Visit( const CTrExp& p )
{
	lastType = "boolean";
}

//false

void CTypeCheckerVisitor::Visit( const CFExp& p )
{
	lastType = "boolean";
}

//id

void CTypeCheckerVisitor::Visit( const CIdExp& p )
{
	//»справленно 0:11
	std::string idType( table->Lookup( p.GetId() ) );
	if( idType != "" ) {
		lastType = table->Lookup( p.GetId() );
	} else {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Unexpected id \"%s\"\n -Location: method %s in class %s \n\n",
			p.GetId(), mN, cN );
	}
}

//this

void CTypeCheckerVisitor::Visit( const CThExp& p )
{
	CClass* currClass( table->getCurrClass() );
	lastType = (currClass->getName());
}

//new int [ Exp ] 

void CTypeCheckerVisitor::Visit( const CNewIntExp& p )
{
	p.GetExp()->Accept( this );
	if( lastType != "int" ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Error: type of Exp isn't \"int\", it's \"%s\"\n -Location: method %s in class %s \n\n",
			lastType, mN, cN );
	}
	lastType = "int[]";
}

//new id ()

void CTypeCheckerVisitor::Visit( const CNewIdExp& p )
{
	lastType = p.GetId();
}

//!Exp

void CTypeCheckerVisitor::Visit( const CNotExp& p )
{
	p.GetExp()->Accept( this );
}

//( Exp )

void CTypeCheckerVisitor::Visit( const CBrExp& p )
{
	p.GetExp()->Accept( this );
}

// id

void CTypeCheckerVisitor::Visit( const CTypeId& p )
{
	//»справленно 0:03
	std::string idType( table->Lookup( p.GetId() ) );
	if( idType != "" ) {
		lastType = table->Lookup( p.GetId() );
	} else {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Unexpected id \"%s\"\n -Location: method %s in class %s \n\n", p.GetId(), mN, cN );
	}
}

//Exp , ExpList

void CTypeCheckerVisitor::Visit( const CExpList& p )
{
	p.GetExp()->Accept( this );
	++counter;
	if( lastType != varList->getType() ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		const char* vN = (varList->getName()).c_str();
		printf( "Error: type of ExpList #%d isn't %s, it's \"%s\"\n -Location: method %s in class %s \n\n",
			counter, vN, lastType.c_str(), mN, cN );
	}
	if( varList->getNext() ) {
		if( p.GetExpList() ) {
			//!!!!!!!!!!!!!!!!!!!!!!!
			varList = varList->getNext();
			p.GetExpList()->Accept( this );
		} else {
			isError = true;
			std::string methodName( (table->getCurrMethod())->getName() );
			std::string className( (table->getCurrClass())->getName() );
			const char* mN = methodName.c_str();
			const char* cN = className.c_str();
			printf( "Different parametrs in used & defined method %s\n -Location: method %s class %s\n\n",
				table->getCurrMethod(), mN, cN );
		}
	} else if( p.GetExpList() ) {
		isError = true;
		std::string methodName( (table->getCurrMethod())->getName() );
		std::string className( (table->getCurrClass())->getName() );
		const char* mN = methodName.c_str();
		const char* cN = className.c_str();
		printf( "Different parametrs in used & defined method %s\n -Location: method %s class %s\n\n", mN, mN, cN );
	}
}

//Type Id FormalRestList

void CTypeCheckerVisitor::Visit( const CFormalList& p )
{
	// сюда же не надо заходить?!?!?! все в таблице лежит
	assert( false );
}

//ClassDeclList

void CTypeCheckerVisitor::Visit( const CClassDeclList& p )
{
	if( p.GetTop() ) {
		//не надо же мен€ть положение в таблице?!
		p.GetTop()->Accept( this );
	}
	if( p.GetTail() ) {
		p.GetTail()->Accept( this );
	}
}

void CTypeCheckerVisitor::Visit( const CVarDeclList& p )
{
	if( p.GetTop() ) {
		p.GetTop()->Accept( this );
	}
	if( p.GetTail() ) {
		p.GetTail()->Accept( this );
	}
}

void CTypeCheckerVisitor::Visit( const CMethodDeclList& p )
{
	if( p.GetTop() ) {
		p.GetTop()->Accept( this );
	}
	if( p.GetTail() ) {
		p.GetTail()->Accept( this );
	}
}

void CTypeCheckerVisitor::Visit( const CStmList& p )
{
	if( p.GetTop() ) {
		p.GetTop()->Accept( this );
	}
	if( p.GetTail() ) {
		p.GetTail()->Accept( this );
	}
}

bool CTypeCheckerVisitor::wasError()
{
	return isError;
}