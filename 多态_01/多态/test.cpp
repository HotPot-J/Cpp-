#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

/*
多态

	一、概念：通俗讲多态即多种形态，具体讲即去完成某个行为，当不同的对象去
	完成时会产生出不同的状态

	二、多态构成的条件
		（多态是在不同继承关系的类对象，去调用同一函数，产生了不同的行为。比如
	   student继承person，person买车票全价，student对象买车票半价）
	   1.必须通过基类的指针或者引用调用虚函数
	   2.被调用的函数必须是虚函数，且派生类必须对基类的虚函数进行重写
			虚函数:
		      被virtual修饰的类成员函数称为虚函数
			虚函数的重写:
			  派生类中有一个跟基类完全相同的虚函数(即派生类虚函数与基类虚函数的返回值类
			  型、函数名字、参数列表完全相同)，称子类的虚函数重写了基类的虚函数
		 例:（person的派生类student重写了其BuyTicket函数）
		class person{
			public:
			    virtual void BuyTicket(){
					printf("全价票\n");
				}
		};
		class student:public person{
			public:
				virtual void BuyTicket(){
					printf("半价票\n");
				}
		};
		
		//**必须通过基类的指针或者引用调用虚函数的具体实现
			void Fun(person& a){
				a.BuyTicket();
			}

			int main(){
				person p;
				student s;
				p.Fun(p); //结果为全票
				s.Fun(s); //结果为半票
				return 0;
			}
		//不同的对象完成（调用）同一个行为效果是不一样的


		虚函数重写的例外：
			协变（基类与派生类虚函数返回值类型不同）
			派生类重写基类虚函数时，与基类函数指针返回值类型不同。但返回值
			类型必须为基类的对象的指针或者引用

			例子：
		class person{
			public:
			    virtual person* BuyTicket(){
					printf("全价票\n");
					return this;
				}
		};
		class student:public Person{
			public:
				virtual student* BuyTicket(){
					printf("半价票\n");
					return this;
				}
		};
	
*/

//析构函数的重写（基类与派生类析构函数的名字不同）

//假如多态中 析构函数不采用虚函数重写可能引发的问题
//class person{
//public:
//	 ~person(){
//		printf("全价票\n");
//	}
//};
//class student :public person{
//public:
//		~student(){
//		printf("半价票\n");
//	}
//};
//
//int main(){
//	person* p1 = new person();
//	person* p2 = new student();
//	delete p1;
//	delete p2;
//	return 0;
//	/*
//	全价票   
//    全价票（是一个student对象 却调用了person的析构，由于p1为基类指针，指向
//			派生类，这样的问题会导致内存泄漏（未调用派生类析构））
//      请按任意键继续. . .
//	*/
//}

//使用多态机制，重写析构函数什么对象就怎么调用析构（基类调基类  派生类掉基类+派生类自己的析构）

class person{
public:
	virtual ~person(){
		printf("全价票\n");
	}
};
class student :public person{
public:
	virtual ~student(){
		printf("半价票\n");
	}
};

int main(){
	person* p1 = new person();
	person* p2 = new student();
	delete p1;
	delete p2;
	return 0;
	/*
	全价票
    半价票
    全价票
请按任意键继续. . .
	*/
}