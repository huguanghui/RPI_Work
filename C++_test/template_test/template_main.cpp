// 重载的局限性 --> 模板
// 实现代码重用机制的一种工具，实现类型参数化
// 分为两类: a.函数模板 b.类模板
// ----函数模板

#include <iostream>

using std::cout;
using std::endl;

template <class T>
T min(T x, T y)
{
	return (x < y)?x:y;
}

int main(int argc, char *argv[])
{
	int n1 = 2, n2 = 10;
	double d1 = 1.5, d2 = 5.5;

	cout << "较小整数" << min(n1, n2) << endl;
	cout << "较小实数" << min(d1, d2) << endl;
	
	return 0;
}
