#include "dll.h"

#include <windows.h>
#include <iostream>
using namespace std;

int main( )
{
	cout << "main()" << endl;

	// Use func in DLL obj
	// TestDLL::func( );

	// dll��̬����ʱ��ִ��.init������һ��ȫ�ֶ���
	HINSTANCE handle = ::LoadLibrary( "dll_initGlobal.dll" );

	cout << "handle: " << (void*)handle << endl;

	if ( handle != 0 )
		::FreeLibrary( handle );
}
