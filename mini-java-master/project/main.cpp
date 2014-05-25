#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <interface.h>

#include <Syntax.hpp>

#include <SymbolTable.h>
#include <PrettyPrintVisitor.h>
#include <TypeCheckerVisitor.h>
#include <Frame.h>
#include <Translator.h>
#include <IntermediateTreePrinter.h>
#include <Canon.h>
#include <AssemblerGenerator.h>
#include <BasicBlocks.h>
#include <Codegen.h>
#include <TraceSchedule.h>

int yyparse();
extern IProgram* yyprogram;
using namespace std;

int main()
{
	if( yyparse() ) {
		system( "Pause" );
		return -1;
	}

	// �������� ��� ���������
	PrettyPrintVisitor PrintV;
	yyprogram->Accept( &PrintV );

	printf( "\n\n-------------------------------------------\n\n" );

	// ������ ������� ��������
	CSTVisitor STBuilder;
	yyprogram->Accept( &STBuilder );
	STBuilder.GetTable()->Print();

	//Type cheking
	CTypeCheckerVisitor typeCheker( STBuilder.GetTable() );
	yyprogram->Accept( &typeCheker );//!!!!
	cout << "------------Type cheking completed-----------" << endl;

	if( !typeCheker.wasError() ) {

		//Translation
		Translation::Translator Trans( STBuilder.GetTable() );
		yyprogram->Accept( &Trans );
		IntermediateTreeVisitor TPrint;
		Translation::CProgramFragment* Frag = Trans.getFragments();

		while( Frag != 0 ) {
			cout << endl;
			cout << "-----------CODE BEFORE CANONIZING--------------" << endl;
			cout << Frag->funcFrame->getName()->getLabelName() << endl;;
			// ������������� ����������������� ���
			Frag->funcCode->Accept( &TPrint );

			cout << endl;
			cout << "--------------CANONIZING FINISHED-----------------" << endl;
			// ������� ��� ESEQ ������, �������� ���,
			const Tree::ESEQ* temp = Canon::CCanon::do_exp( Frag->funcCode );
			// ��������� �� �����, ����������� �����
			Canon::�BasicBlocks blocks( Canon::CCanon::linearize( temp->getStm() ) );

			// ����� ������
			for( const Canon::CStmListList* list = blocks.blocks; list != 0; list = list->tail ) {
				cout << endl;
				cout << "--------------------BLOCK-------------------------" << endl;
				for( const Tree::StmList* list2 = list->head; list2 != 0; list2 = list2->getTail() ) {
					list2->getTop()->Accept( &TPrint );
				}
				cout << endl;
				cout << "----------------END OF BLOCK----------------" << endl;
			}
			// ������ ����� � ������ �������, ��������� false-����� � CJUMP
			Canon::TraceSchedule schedule( blocks );

			Frag->funcCodeLinearized = schedule.stms;
			// ������� ��������������� ���
			for( const Tree::StmList* list = Frag->funcCodeLinearized; list != 0; list = list->getTail() ) {
				list->getTop()->Accept( &TPrint );
			}
			cout << endl;
			cout << "--------------CANONIZING CODE END------------" << endl;

			cout << endl;
			cout << "----------------ASSEMBLER CODE---------------------" << endl;
			// ���������� ������������ ���
			Codegen code( Frag->funcFrame );
			Frag->assemblerCode = code.generateCode( Frag );
			// ������� ����� ���������� (�� ����� ���� �� �����������)
			Temp::CTempMap map;
			// ������������� ������������ ���
			const Assembler::IInstrList* list;
			std::string s = "";
			for( list = Frag->assemblerCode;
				list != 0; list = list->getTail() ) {
				if( ! ((s[0] == 'J') && (s[1] == 'M') && (s[2] == 'P')) ){
					cout << s;
				}
				else {
					std::string s2 = list->getTop()->format( map );
					if( !((s2[0] == s[4]) && (s2[1] == s[5])) ) {
						cout << s;
					}
				}
				s = list->getTop()->format( map );
			}
			cout << s;
			Frag = Frag->nextFragment;

			cout << endl;
			cout << "----------------ASSEMBLER CODE FINISHED-------------------" << endl;
		}
	}
	system( "Pause" );
	return 0;
}
