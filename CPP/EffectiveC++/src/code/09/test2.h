/*
 * ���������С���ӡ�����virtual���������½����������
 *	1. impure virtual: ���ø���汾
 *	2. pure virtual:
 *		�������޶��壬����printʱ������abort
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
