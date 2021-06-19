/*
 * virtual in construction|destruction
 */

#include "test1.h"
#include "test2.h"

int main( )
{
	{
		Derived d;
	}
	{
		Derived2 d;
	}
	return 0;
}
