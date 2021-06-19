/*
 * 构造析构中【直接】调用virtual函数不会下降到子类对象
 *	1. impure virtual: 调用父类版本
 *	2. pure virtual:
 *		2.1 有定义: 调用父类版本
 *		2.2 无定义: 链接失败
 */

class Base
{
public:
	Base( );
	~Base( );
	//virtual void print( );
	virtual void print( ) = 0;
};

class Derived : public Base
{
public:
	Derived( );
	~Derived( );
	virtual void print( );
};
