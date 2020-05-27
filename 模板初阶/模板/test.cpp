#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

//模板初阶：
	
/*
	1.泛型编程：
		如何实现一个通用交换函数？

			重载: void Swap(int& left,int& right);
				  void Swap(double& left,double& right);
				  void Swap(char& left,char& right);
				  (重载的函数仅是类型不同，代码复用率低，可维护性低)
			函数模板:
				函数模板代表了一个函数家族，该函数模板与类型无关，在使用时
				被参数化，根据实参类型产生函数的特定类型版本。

			  格式: template<typename T1,typename T2,......typename Tn>
					返回值类型 函数名（参数列表）{}

*/
 //测试使用模板来实现一个通用交换函数
//template<typename T>
//void Swap(T& left, T& right){
//	T tmp = left;
//	left = right;
//	right = tmp;
//
//}
//
//int main(){
//	//int a = 10;
//	//int b = 1;
//	
//	//double a= 10.1;
//	//double b = 1.0;
//	
//	char a = 'a';
//	char b = 'b';
//	Swap(a, b);
//	cout << "a = " << a << ",b = " << b << endl;
//	return 0;
//}

/*
2.函数模板的实例化
 用不同类型的参数使用函数模板时，称为函数模板的实例化。
		
*/
	//2.1隐式实例化：让编译器根据实参推演出参数的实际类型
//template<typename T>
//T add(const T& a, const T& b){
//	return a + b;
//}
//
//int main(){
//	int a1 = 10, a2 = 2;
//	double b1 = 10.0, b2 = 20.0;
//	//add(a1, b1);
//	/*
//		该行代码无法通过编译，由于在编译期间，当编译器看到该实例化，需要推演
//		其实参类型，实参a1将T推演为int，b1又为double，但参数模板只有一个T，
//		编译器无法确定T为int还是double
//		（在模板中，编译器一般不会进行类型转换操作）
//	*/
//
//	//处理方式：
//	add(a1, (int)b1); //用户强制转换
//	//（使用显式式实例化）
//	return 0;
//}

   //2.2显式实例化：载函数名后的<>中指定模板参数的实际类型
//int main(){
//	int a = 10;
//	double b = 20.0;
//	add<int>(a, b);
//	add<double>(a, b);
//	return 0;
//}
  
/*3.模板参数的匹配原则
	1.一个非模板函数可以和一个同名的函数模板同时存在，而且该函数模板还可以被
   实例化为这个非模板函数
    2.对于非模板函数和同名函数模板，如果其他条件都相同，在调用时会优先调用
   非模板函数，而不会从该模板产生一个实例。如果模板可以产生一个具有更好匹配
   的函数，那么将选择模板。
   3.模板函数不允许自动类型转换，但普通函数可以进行自动类型转换
*/
//例：
//	//专门处理int的加法函数
//int add(int a, int b){
//	return a + b;
//}
//
////通用加法函数
//template<typename T>
//T add(T a, T b){
//	return a + b;
//}
//
//int main(){
//	add(1, 2);//与非模板函数匹配，编译器不需要特化
//	add<int>(1, 2);//调用编译器特化的add版本
//	add(10.0, 20.0);//模板函数可以生成更加匹配的版本，编译器根据实参生成更加匹配的Add函数
//	add(1, 2.0); //模板函数不允许自动类型转换，调用非模板函数
//
//	return 0;
//}

//4.类模板
/*
	template<class T1,class T2,......class Tn>
	class 类模板名{
	 //类内成员定义
	};
*/
template<class T>
class Vector
{
public:
	Vector(size_t capacity = 10)
		: _pData(new T[capacity])
		, _size(0)
		, _capacity(capacity)
	{}

	// 使用析构函数演示：在类中声明，在类外定义。
	~Vector();

	void PushBack(const T& data)；
		void PopBack()；
		// ...

		size_t Size() { return _size; }

	T& operator[](size_t pos)
	{
		assert(pos < _size);
		return _pData[pos];
	}

private:
	T* _pData;
	size_t _size;
	size_t _capacity;
};