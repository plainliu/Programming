#include <iostream>
using namespace std;

#include "test1.h"

Base::Base( )
{
	cout << "Base( )" << endl;
	print( );
}
Base::~Base( )
{
	cout << "~Base( )" << endl;
	print( );
}
void Base::print( )
{
	cout << "Base::print" << endl;
}

Derived::Derived( )
{
	cout << "Derived( )" << endl;
}
Derived::~Derived( )
{
	cout << "~Derived( )" << endl;
}
void Derived::print( )
{
	cout << "Derived::print" << endl;
}
