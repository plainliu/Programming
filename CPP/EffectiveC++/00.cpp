/*
 * 
 */

extern int x;

size_t t1;
// std::size_t t2;

// declaration|signature|definition
// initialization

class Widgt
{
	public:
	Widgt();
};
// copy 赋值|构造
// 如果写了带参构造函数，构造时算拷贝构造吗
// 重写了=符号，还是拷贝赋值吗(不重写等号报错？)
Widgt w1;
Widgt w2;
w2 = w1;

int main( )
{
	return 0;
}