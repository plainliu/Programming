#include "dll.h"

#include <iostream>
using namespace std;

TestDLL gObj;
TestDLL* TestDLL::mGlobal = &gObj;

TestDLL::TestDLL( )
{
	cout<<"TestDLL ctor " << this << endl;
}

void TestDLL::func( )
{
	cout << "TestDLL::func " << endl;
}


