#include <iostream>
using namespace std;

#include "test2.h"

Base2::Base2( )
{
	cout << "Base2( )" << endl;
	init( );
}
Base2::~Base2( )
{
	cout << "~Base2( )" << endl;
	print( );
}
void Base2::init( )
{
	cout << "Base2::init" << endl;
	print( );
}
void Base2::print( )
{
	cout << "Base2::print" << endl;
}

Derived2::Derived2( )
{
	cout << "Derived2( )" << endl;
}
Derived2::~Derived2()
{
	cout << "~Derived2( )" << endl;
}
void Derived2::print( )
{
	cout << "Derived2::print" << endl;
}
