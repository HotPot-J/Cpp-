#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstring>
using namespace std;

/*
模板的特化：在原模板类的基础上针对特殊类型所进行特殊化的实现方式。模板
特化分为函数模板特化与类模板特化。
*/

//模板函数未经过特化的情况所产生的问题：

//一个比较函数
//template<class T>
//bool isequal(T& a, T& b){
//	return a == b;
//}
//int main(){
//	char* a = "123";
//	char* b = "456";
//	if (isequal(a, b)){
//		cout << 1 << endl;
//	}
//	else{
//		cout << 0 << endl;
//	}
//	return 0;
//}
/*
	上述代码中当a与b为字符串类型时，显然这样比较是不合理的，此时就需要
 对模板进行特化。(或者直接将特殊的函数给出即可)
*/
	

/*
函数模板特化的步骤：
	1.必须要先有一个基础的函数模板
	2.关键字template后接一对空的<>
	3.函数名后跟一对<>，尖括号中指定需要特化的类型
	4.函数形参表：必须要和模板函数的基础参数类型完全相同
*/

//template<class T>
//bool isequal(T& a, T& b){
//	return a == b;
//}
//template<>
//bool isequal<char*>(char*& a, char*& b){
//	return strcmp(a, b) == 0;
//}
//int main(){
//	char* a = "123";
//	char* b = "123";
//	if (isequal(a, b)){
//		cout << 1 << endl;
//	}
//	else{
//		cout << 0 << endl;
//	}
//	return 0;
//}

/*类模板特化
  全特化
	全特化即是将模板参数列表中所有的参数都确定化
  偏特化
	1.特化参数列表的一部分
	2.针对模板参数更进一步的条件限制所设计出来的一个特化版本
*/

//template<class T1, class T2>
//class jxy
//{
//public:
//	jxy() { cout << "jxy<T1, T2>" << endl; }
//private:
//	T1 _d1;
//	T2 _d2;
//};
////全特化
//template<>
//class jxy<int, char> {
//public:
//	jxy() { cout << "jxy<int, char>" << endl; }
//private:
//	int _d1;
//	char _d2;
//};
//
////部分特化
//template<class T1>
//class jxy<T1, char> {
//public:
//	jxy() { cout << "jxy<T1, char>" << endl; }
//private:
//	T1 _d1;
//	char _d2;
//};
//
////两个参数偏特化为指针类型
//template <typename T1, typename T2>
//class jxy <T1*, T2*>
//{
//public:
//	jxy() { cout << "jxy<T1*, T2*>" << endl; }
//
//private:
//	T1 _d1;
//	T2 _d2;
//};
//
//void TestVector()
//{
//	jxy<int, int> d1; //调用类模板
//	jxy<int, char> d2;//调用类模板的全特化
//  jxy<double,char> d3;//调用部分特化
//  jxy<char*,char*>d4;//调用两个参数偏特化为应用类型
//}
//int main(){
//	TestVector();
//	return 0;
//}

/*模板分离编译的问题：
	1.什么是分离编译？
		一个程序（项目）由若干个源文件共同实现，而每个源文件单独编译生成目标文
		件，最后将所有目标文件链接起来形成单一的可执行文件的过程称为分离编译模
		式。 
	2.模板分离编译导致的“链接错误”报错原因：
		c/c++程序要运行，一般经历以下步骤：
			预处理-》编译-》汇编-》链接
		编译：对程序按照语言特性进行词法、语法、语义分析，错误检查无误后生成汇
		编代码（头文件不参与编译，编译器对工程中的多个源文件都是分离开单独编译）
		链接：将多个obj文件合并成一个，并处理没有解决的地址问题

 例子：
// a.h
template<class T> 
T Add(const T& left, const T& right);

// a.cpp
template<class T> 
T Add(const T& left, const T& right){
 return left + right; 
 }

 // main.cpp
#include"a.h"
int main(){
 Add(1, 2);
 Add(1.0, 2.0);
 return 0; 
 }

 由于在a.cpp中，编译器没有看到对Add模板函数的实例化，因此不会生成具体的加法函数
 在main.obj调用Add<int>与Add<double>时，编译器在链接时才会找其地址，但是两个函
 数没有实例化，没用生成具体代码，因此链接时报错。

 如何较好的解决这种问题?
	将生命和定义放到一个文件中
*/

/*
模板总结：
	优点:
		1.模板复用了代码，节省资源，更快的迭代开发，c++的标准模板库因此产生
		2.增强了代码的灵活性
	缺点：
		1.模板会导致代码膨胀的问题，也会导致编译时间变长
		2.出现模板编译错误时，错误信息非常凌乱，不易定位错误
*/