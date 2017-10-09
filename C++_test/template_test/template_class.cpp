// 重载的局限性 --> 模板
// 实现代码重用机制的一种工具，实现类型参数化
// 分为两类: a.函数模板 b.类模板
// ----类模板

#include <iostream>
#include "template_class.h"

using std::cout;
using std::endl;


template <typename T1, typename T2>
myClass<T1, T2>::myClass(T1 a, T2 b):I(a),J(b) {}


template <typename T1, typename T2>
myClass<T1, T2>::~myClass() {}


template <typename T1, typename T2>
void myClass<T1, T2>::show()
{
	cout << "I=" << I << ", J=" << J << endl;
}

int main(int argc, char *argv[])
{
	myClass<int,int> class1(1,5);
	class1.show();

	myClass<int,char> class2(2,'a');
	class2.show();

	myClass<char,float> class3('b', 2.5);
	class3.show();
	
	return 0;
}
