#ifndef TEMPLATE_CLASS_H_
#define TEMPLATE_CLASS_H_

template <typename T1, typename T2>
class myClass {
private:
	T1 I;
	T2 J;
public:
	myClass(T1 a, T2 b);
	~myClass();
	void show();
};

#endif
