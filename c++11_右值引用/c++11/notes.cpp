#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
/*
1.对c++11的认识：
	相对之前的版本，c++11能更好的用于系统开发和库开发、语法更加泛化和简单化
	更加稳定和安全，不仅功能更强大，而且能提升程序员的开发效率
*/

/*
右值引用：
	引用即别名，引用变量与其引用实体公用同一块空间，而引用的底层是通过指针
	来实现的，因此使用引用，可提高程序的可读性。
*/

//不管是左值引用还是右值引用，都是给对象取别名
//不过左值引用主要给左值取别名，右值引用主要是给右值取别名。

//什么是左值什么是右值？
//int a = 10; int b = a;  a在在两个表达式均为左值（并非只依靠方向来判断）
//10为右值，b为左值

//可以修改的为左值，左值通常是变量
//右值通常是常量，表达式或者函数返回值（临时对象）

void test1(){
	//左值引用的定义：
	int a = 0;
	int& b = a;
	//int& c = 10;//左值不可以引用右值
	const int&e = 10; //该情况下可以（e此时为const）
	//右值引用的定义：
	int x = 1, y = 2;
	int&& c = 10;
	int&& d = x + y;//(x+y的返回值为右值)
	//右值不能引用左值，但是可以引用move后的左值
	//int&& m = a;
	int&& m = move(a); //该情况下可以
}

/*
c++11将右值分为:
	纯右值：基本类型的常量或者临时对象
	将亡值：自定义类型的临时对象（即将消亡的值）
*/


class _string{
public:
	_string(const char* str = ""){
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}
	//当传递过来的为左值，硬着头皮去深拷贝
	_string(const _string& s){
		cout << "_string(const _string& s) 深拷贝 效率低" << endl;
		_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);
	}

	//当传递过来的为一个将亡值，既然即将被析构，不如直接交换资源，避免深拷贝
	//浪费空间代价
	_string( _string&& s)
		:_str(nullptr) //防止swap随机值
	{
		cout << "__string(_string&& s) 移动赋值 效率高" << endl;
		swap(s._str, _str);
	}

	_string& operator = (const _string& s){
		cout <<  " _string& operator = (const _string& s) 深拷贝 效率低" << endl;
		if (this != &s){
			char* newstr = new char[strlen(s._str) + 1];
			strcpy(newstr, s._str);
			delete[] _str;
			_str = newstr;
		}
		return *this;
	}

	_string& operator = (_string&& s){
		cout << " _string& operator = (_string&& s) 移动赋值 效率高" << endl;
		swap(_str, s._str);
		return *this;
	}

	~_string(){
		delete[] _str;
	}
private:
	char* _str;
};
_string _tmp(const char* str){
	_string tmp(str);
	return tmp; //该返回值并非上行的tmp，上行的tmp在函数结束声明周期结束
			   //返回的即为右值中的将亡值
}
int main(){
	_string a("左值");
	_string b(a);
	_string c(_tmp("右值-将亡值"));

	_string d("左");
	 d = a;
	 d = _tmp("右值-将亡值");
	return 0;
}
/*
执行结果：
_string(const _string& s) 深拷贝 效率低
__string(_string&& s) 直接交换 效率高
请按任意键继续. . .
*/

/*
现实中不可避免存在传值返回的场景，传值返回的拷贝返回对象的临时对象。
右值本身意义不大，但是右值引用实现了移动构造和移动赋值，那么面对
接收函数传值返回对象（右值）等等场景，可以提高效率。

左值引用和右值引用的本质都是减少拷贝

左值引用: 
	做参数:void f1（T x）--》void f1(T& x)(在传参减少拷贝)
	做返回值: Tf2() --》 T& f2() 但是要注意，如果返回对象出了作用域不在了
								就不能用传值返回

右值引用:
	做参数： void push(const T&& x) --》在push内部减少拷贝） 
										在push内部直接用移动构造或者赋值，避免深拷贝
	做返回值：如果一个函数：T f2（）返回一个将亡值， T ret = f2（）接收
	这个将亡值，在利用将亡值进行移动赋值，就可以避免深拷贝

*/