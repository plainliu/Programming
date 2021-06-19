/*
 * 构造析构中【间接】调用virtual函数不会下降到子类对象
 *	1. impure virtual: 调用父类版本
 *	2. pure virtual:
 *		不论有无定义，调用print时，运行abort
 */

class Base2
{
public:
	Base2( );
	~Base2( );

	void init( );
	virtual void print( );
	//virtual void print( ) = 0;
};

class Derived2 : public Base2
{
public:
	Derived2( );
	~Derived2( );
	virtual void print( );
};
