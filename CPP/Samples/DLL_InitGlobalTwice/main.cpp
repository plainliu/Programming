#include "dll.h"

#include <windows.h>
#include <iostream>
using namespace std;

int main( )
{
	cout << "main()" << endl;

	// Use func in DLL obj
	// TestDLL::func( );

	// dll动态加载时，执行.init，构造一次全局对象
	HINSTANCE handle = ::LoadLibrary( "dll_initGlobal.dll" );

	cout << "handle: " << (void*)handle << endl;

	if ( handle != 0 )
		::FreeLibrary( handle );
}
