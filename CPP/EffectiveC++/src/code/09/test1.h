/*
 * ���������С�ֱ�ӡ�����virtual���������½����������
 *	1. impure virtual: ���ø���汾
 *	2. pure virtual:
 *		2.1 �ж���: ���ø���汾
 *		2.2 �޶���: ����ʧ��
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
