#include <AssemblerGenerator.h>
namespace Assembler
{
	//������� �������, ������ ���������, � ���� - �� ����, � ���� - �� �����
	string replace( const Temp::CTempList* dst, const Temp::CTempList* src, const Temp::CLabelList* jump, std::string str )
	{
		int count = 0; // ����� ����� ����
		std::string s_d = "'d0";
		int position = str.find( s_d, 0 );
		while( position != string::npos ) {
			str.replace( position, s_d.length(), dst->getTop()->getId(), 0, (dst->getTop()->getId()).length() );
			dst = dst->getTail();
			count++;
			std::string scount;
			std::stringstream ss;
			ss << count;
			ss >> scount;
			s_d = "'d" + scount; //�������� � 's0 0 �� 1 � ��� ����� ���� �� ����� ����
			position = str.find( s_d, 0 ); // ����� ��������� ����������
		}
		count = 0;//�������� �� 1
		s_d = "'s0";
		position = str.find( s_d, 0 );
		while( position != string::npos ) {
			str.replace( position, s_d.length(), src->getTop()->getId(), 0, (src->getTop()->getId()).length() );
			src = src->getTail();
			count++;
			std::string scount;
			std::stringstream ss;
			ss << count;
			ss >> scount;
			s_d = "'s" + scount; //�������� � 's0 0 �� 1 � ��� ����� ���� �� ����� ����
			position = str.find( s_d, 0 ); // ����� ��������� ����������
		}
		count = 0;//�������� �� 1
		s_d = "'l0";
		position = str.find( s_d, 0 );
		while( position != string::npos ) {
			str.replace( position, s_d.length(), jump->getTop()->getLabelName(), 0, (jump->getTop()->getLabelName()).length() );
			jump = jump->getTail();
			count++;
			std::string scount;
			std::stringstream ss;
			ss << count;
			ss >> scount;
			s_d = "'d" + scount; //�������� � 's0 0 �� 1 � ��� ����� ���� �� ����� ����
			position = str.find( s_d, 0 ); // ����� ��������� ����������
		}
		return str;
	}
	string OPER::format( const Temp::CTempMap m ) const
	{
		return replace( this->def(), this->use(), this->getJump(), this->assem );
	}
	string MOVE::format( const Temp::CTempMap m ) const
	{
		return replace( this->def(), this->use(), 0, this->getAssem() );
	}
	string LABEL::format( const Temp::CTempMap m ) const
	{
		return this->getAssem();
	}
}