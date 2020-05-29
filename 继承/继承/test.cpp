#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;

/*
一、继承
	1.1概念:
		继承机制是面向对象程序设计使代码可以复用的最重要的手段，它
	允许程序员在保持原有类特性的基础上进行扩展，增加功能，这样产生
	新的类，称派生类。继承呈现了面向对象程序设计的层次结构，体现了
	由简单到复杂的认知过程。（继承是类设计层次的复用）
	（继承解决了重复定义问题，去抽象出一个包含这些成员的公共父类，
	再让具体的子类去继承这个公共父类（基类））
*/

//例子：学生和老师都具有人的共同特征，所以这里人为基类 学生和老师可以分别继承该基类

//class Person
//{
//public:
//	void Print()
//	{
//		cout << "name:" << _name << endl;
//		cout << "age:" << _age << endl;
//	}
//protected:
//	string _name = "jxy"; // 姓名
//	int _age = 22; // 年龄
//};
/*继承后父类的Person的成员（成员函数+成员变量）都会变成子类的一部分。这里体现出了Student和
Teacher复用了Person的成员。使用监视窗口查看Student和Teacher对象，可以看到变量的复用。
调用Print可以看到成员函数的复用。*/
//class Student : public Person
//{
//public:
//	Student(string& name){
//		_name = name;
//	}
//		 
//protected: 
//	
//		   int _stuid; // 学号
//};
//class Teacher : public Person
//{
//protected:
//	int _jobid; // 工号
//};
//int main()
//{
//	string name = "jjj";
//	Student s(name);
//	Teacher t;
//	//s._name = name;报错
//	s.Print();
//	t.Print();
//	return 0;
//}
/*
注意: protected关键字修饰的成员被继承后可见，且在派生类内部才可调用
基类中用protected修饰的成员变量 上例中，在main函数中，s._name=name是会报错
的，若要改变年龄，需要在student类内部中修改（构造函数等）
*/

/*
1.2继承的定义
	格式:
	 class Student（派生类）:public（继承方式） Person（基类）
	 {
		public:
			int _stuid;//学号
	 }

	继承基类成员访问方式的变化:
		1.基类private成员在派生类中无论以什么方式继承都不可见。这里
		的不可见是指基类的私有成员还是被继承到了派生类对象中，但是语
		法上限制派生类对象不管在类里面还是类外面都不能去访问它。

		2.基类的private成员在派生类中是不能被访问的，如果基类成员不想
		在类外直接被访问，但需要在派生类中能访问，就定义为protected。
		
		3.基类的私有成员在子类都是不可见的 public>protected>private

		4.使用关键字class时，默认的继承方式是private，使用struct时默认
		继承方式为public，最好显示的写出继承方式

		5.在实际运用在一般使用public的继承方式
*/

/*
二、基类和派生类对象赋值转换
	1.派生类对象可以赋值给基类的对象/基类的指针/基类的引用（切片赋值
	，即把派生类中父类的那部份切来赋值过去）

	2.基类对象不能赋值给派生类对象

	3.基类的指针可以通过强制类型转换赋值给派生类的指针。但是必须是
	基类的指针是指向派生类对象时才是安全的
*/

//例子:
//class Person
//{
//protected:
//	string _name;
//	string _sex;
//	int _age;
//};
//
//class Student :public Person
//{
//public:
//	int _id;
//};
//
//void Test(){
//	Student a;
//	//1.派生类对象可以赋值给基类对象/指针/引用
//	Person b = a; //值
//	Person* bb = &a;//地址
//	Person& bbb = a;//引用

//	//2.基类对象不能赋值给派生类对象
//	//a = b;报错
//
//	//3.基类的指针可以通过强制类型转换赋值给派生类指针
//	bb = &a; //先将派生类地址赋值给基类指针 此时该基类指针指向派生类地址空间 可以访问到_id
//	Student* aa = (Student*)bb;//该情况可行
//	aa->_id = 1;
//
//	bb = &b;//依然还是基类指针指向基类
//	Student* aaa = (Student*)bb;//可行，但会存在访问越界的问题
//	aaa->_id = 1;//该语句会使程序崩溃掉，因为,该bb指针指向仍为基类，强转为派生类，无法访问到_id
//}

/*
三、继承中的作用域
	1.在继承体系中基类和派生类都有独立的作用域
	2.子类和父类中有同名成员，子类成员将屏蔽父类对同名成员的直接访问，
	这种情况叫做隐藏，也叫做重定义（在子类成员函数中，可以使用 父类::基类成员 显式访问）
	3.需要注意的是如果是成员函数的隐藏，只需要函数名相同就构成隐藏
	4.在实际中的继承体系里最好不要定义同名的成员
*/


/*
四、派生类的默认成员函数 
	1.派生类的构造函数必须调用基类的构造函数初始化基类的那一部分成员。
	如果基类没用默认的构造函数，则必须在派生类构造函数的初始化列表阶
	段显式调用。
	2.派生类的拷贝构造函数必须调用基类的拷贝构造完成基类的拷贝初始化
	3.派生类的operator=必须要调用基类的operator=完成基类的复制
	4.派生类的析构函数会在被调用完成后自动调用基类的析构函数清理基类成员。
	因为这样才能保证派生类对象先清理派生类成员再清理基类成员的顺序。
	5.派生类对象初始化先调用基类构造再调用派生类构造
	6.派生类对象析构清理先调用派生类析构再调用基类的析构  

*/

/*
5.继承与友元
	友元关系不能继承，也就是说基类友元函数不能访问子类私有和保护成员
*/

/*
6.继承与静态成员
	基类定义了static静态成员，则整个继承体系里面只有一个这样的成员。无论派生
	多少个子类，都只有一个static成员实例
*/

/*
七、菱形继承及菱形虚拟继承
	1.单继承: 一个子类只有一个直接父类时称这个继承关系为单继承
		class student ： public person
	2.多继承：一个子类有两个或以上直接父类时，称这个继承关系为多继承
		class assistant（助理） ： public student，public teacher
	3.菱形继承:是多继承的一种特殊情况
			                      class person
								/               \
							   /                 \
	class student：public person               class teacher：public person
		                       \                 /
							    \               /
		    class assistant（助理） ： public student，public teacher
				
		在student中有：person中的：string _name  其特有的：_num
		在teacher中有：person中的：string _name  其特有的：_id
		继承了两者的assistant： 包含了以上两个基类的成员变量和自己特有的成员变量
        （显然，在assistant的对象中的person成员有两份
		使得这样的菱形继承出现了数据冗余和二义性的问题）

		数据冗余可以使用指定作用域来解决：
			例子: assistant a;
				a._name = "jxy";
			//若要访问学生的姓名和老师的姓名可以：
				a.student::_name = "jjj";
				a.teacher::_name = "yyy";
	但是该方法并未解决二义性，难道a当老师一个名字，当学生一个名字？显然是不合适的（艺名除外。。。）

     **虚拟继承可以解决菱形继承的二义性和数据冗余的问题。如上面的继承关系，
  在student和teacher继承person时使用虚拟继承，即可解决。
	 虚拟继承关键字：virtual（虚拟）
*/	
//class Person
//{
//public:
//	string _name; // 姓名
//};
//class Student : virtual public Person
//{
//protected:
//	int _num; //学号
//};
//class Teacher : virtual public Person
//{
//protected:
//	int _id; // 职工编号
//};
//class Assistant : public Student, public Teacher
//{
//protected:
//	string _majorCourse; // 主修课程
//};
//void Test()
//{
//	Assistant a;
//	a._name = "jxy";
//}
//int main(){
//	Test();
//	return 0;
//}

/*
继承和组合:
	class a{
		protected:
			int _a;
	};
	class b{
		protected:
			int _b;
			a aa;
	};
	
	
	继承为is a 的关系 形象来说 学生是一个人 所以student继承person
	组合为has a的关系 形象来说 学生有胳膊 （胳膊类（大臂和小臂）） 所以学生类和胳膊类可以为组合形式

	
*/