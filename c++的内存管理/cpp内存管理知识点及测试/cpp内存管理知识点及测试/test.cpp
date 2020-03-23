#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

/*
c++内存管理方式：通过new和delete操作符进行动态内存管理
*/

//1.new/delete操作符内置类型：
void Test1(){
/*管理对象：*/
	//动态申请一个int类型的空间
	int* ptr1 = new int;

	//动态申请一个int类型的空间并初始化为10
	int* ptr2 = new int(10);

/*管理对象数组：*/
	//动态申请3个int类型的空间
	int* ptr3 = new int[3];

	delete ptr1;
	delete ptr2;
	delete[] ptr3;
}
//注意：申请和释放单个元素的空间，使用new和delete操作符，申请和释放
//使用new[]和delete[]


//2.new和delete操作自定义类型
class Test{
public:
	Test()
		:_data(0)
	{
		cout << "Test():" << this << endl;
	}
	~Test(){
		cout << "~Test():" << this << endl;
	}
private:
	int _data;
};

void Test2(){
	//申请单个Test类型的对象
	Test* p1 = new Test;
	delete p1;

	//申请10个Test类型的对象
	Test* p2 = new Test[10];
	delete[] p2;
}
//t通过调试我们发现 在申请自定义类型的空间时，new会调用构造函数，
//delete会调用析构函数，而c语言中malloc与free不会
int main(){
	Test2();
}

/*
一、malloc/free和new/delete的的区别
1.malloc/free和new/delete的共同点：都是从堆上申请空间，并且需要用户
手动释放，不同的地方是：
 1.malloc和free是函数，new和delete是操作符
 2.malloc申请的空间不可以初始化，而new可以初始化
 3.malloc申请空间时，需要手动计算空间大小并传递，new只需要在其后跟
 上空间类型即可
 4.malloc的返回值为void*,在使用时必须强转，new不需要，因为new后跟
 的是空间类型。
 5.malloc申请空间失败是，返回的时NULL，因此使用时必须判空，new不需
 要，但是new需要捕获异常
 6.申请自定义类型对象时，malloc/free只会开辟空间，不会调用构造函数
 与析构函数，而new在申请空间后会调用构造函数完成对象的初始化，delete
 在释放空间前会调用析构函数完成空间中的资源的清理

 二、内存泄漏
 什么是内存泄漏，内存泄漏的危害
 什么是内存泄漏：内存泄漏指因为疏忽或错误造成程序未能释放已经不在使
 用的内存的情况。内存泄漏并不是指内存在物理上的消失，而是应用程序分
 配某段内存后，因为设计错误，失去了对该段内存的控制，因而造成了内存
 的浪费。

 内存泄漏的危害:长期运行的程序出现内存泄漏，影响很大，如操作系统、后
 台服务等等，出现内存泄漏会导致响应越来越慢，最终卡死。
*/