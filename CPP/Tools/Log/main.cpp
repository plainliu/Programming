#include "log.h"

#include <iostream>
using namespace std;

int main( )
{
	//cout << L"123"<< endl;
	PrintHelper( L"123 %d %p", 123, (void*)0 );
	MyPrint( L"123 %d %p", 123, (void*)0 );
	LJJ_LOG( L"123 %d %p", 123, (void*)0 );
	LJJ_LOGT( LJJ, L"123 %d %p", 123, (void*)0 );
}
