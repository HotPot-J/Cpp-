#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

/*
什么是重载、重定义、重写
	重载: 两个函数在同一作用域
	重写（覆盖）: 两个函数分别在基类和派生类的作用域
		  函数名 参数 返回值都必须相同（协变例外）
		  两个函数都必须是虚函数
	重定义（隐藏）：两个函数分别在基类和派生类的作用域
				    函数名相同
					两个基类和派生类的同名函数不构成重写就是重定义

2.c++11中override和final
	final可以修饰类：这个类变成最终类，不能被继承
	final可以修饰虚函数，这个虚函数不能被重写
	class Car
   {
     public:
       virtual void Drive() final {}
    };

    class Benz :public Car
   {
     public:
       virtual void Drive() {cout << "Benz-舒适" << endl};//报错 无法重写
	 };


	override：检查派生类虚函数是否重写了基类某个函数，如果没有重写编译报错
	class Car{
	public:
	virtual void Drive(){}
	};
	class Benz :public Car {
	public:
	virtual void Drive(int) override { cout << "Benz-舒适" << endl; }
	//Drive(int)未构成重写 由于使用了override关键字，就会报错提醒未重写
	};

3.抽象类
	
	概念:
		在虚函数后面写上 =0 ，则这个函数为纯虚函数，包含纯虚函数的类叫做抽象类(接口类)
		class person{
			virtual void age() = 0;
		};
	抽象类的特点:
		1.抽象类不能实例化出对象。
		2.其派生类继承后也不能实例化出对象，只有重写纯虚函数，派生类才能实例化

	纯虚函数的作用？
		1.纯虚函数可以定义抽象类
		2.纯虚函数强制其派生类重写虚函数（其和override的区别：override是检查是否重写虚函数）

	什么情况下定义纯虚函数呢？
		1.希望定义的类为抽象类
		2.一个类很抽象，作为父类存在，在现实中没有对应的实体对象

	接口继承和实现继承:
		1.虚函数的继承是一种接口继承，派生类继承的是基类虚函数的接口，目的是
		为了重写，达成多态，继承的是接口。（所以如果不实现多态，不要把函数定义为虚函数）
		2.普通函数的继承是一种实现继承，派生类继承了基类函数，可以使用函数，
		继承的是函数的实现。
		
*/


