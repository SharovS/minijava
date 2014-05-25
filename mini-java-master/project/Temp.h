#pragma once
#include <string>
#include <stdlib.h>



namespace Temp
{

	class CTemp {
	public:
		CTemp()
		{
			char buffer[16] = {0};
			_snprintf_s( buffer, 16, 15, "T%d", counter );
			++counter;
			name = buffer;
		}

		CTemp( std::string _name ) : name( _name ) {}
		std::string getId() const { return name; }
	private:
		std::string name;
		static int counter;
	};

	//--------------------------------------------------------------------------------------

	class CTempList {
	public:
		CTempList( const CTemp* _top, const CTempList* _tail ) : top( _top ), tail( _tail ) {} \
			const CTemp* getTop() const { return top; }
		const CTempList* getTail() const { return tail; }
	private:
		const CTemp* top;
		const CTempList* tail;
	};

	//--------------------------------------------------------------------------------------

	class CTempMap {
	public:
		CTempMap() {}
		std::string TempMap( const CTemp* temp )
		{
			return temp->getId();
		}
	};

	//--------------------------------------------------------------------------------------

	class CLabel {
	public:
		CLabel()
		{
			char buffer[16] = {0};
			_snprintf_s( buffer, 16, 15, "L%d", counter );
			++counter;
			name = buffer;
		}
		CLabel( std::string _name ) : name( _name ) {}
		std::string getLabelName() const { return name; }
	private:
		std::string name;
		static int counter;
	};

	//--------------------------------------------------------------------------------------

	class CLabelList {
	public:
		CLabelList( const CLabel* _top, CLabelList* _tail ) : top( _top ), tail( _tail ) {}
		const CLabel* getTop() const { return top; }
		CLabelList* getTail() const { return tail; }
	private:
		const CLabel* top;
		CLabelList* tail;
	};
}