#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>


/*
一、priority_queue的介绍：
  1.优先队列是一种容器适配器，根据严格的弱排序标准，它的第一个元素总是它
包含的元素中最大的。
  2.此上下文类似于堆，在堆中可以随时插入元素，并且只能检索最大堆元素（优先
队列中位于顶部的元素）。
  3.优先队列被实现为容器适配器，容器适配器即将特定的容器类封装作为其底层
容器类，queue提供一组特定的成员函数来访问其元素。元素从特定容器的“尾部”
弹出，其称为优先队列的顶部。
  4.底层容器可以是任何标准容器类模板，也可以是其他特定设计的容器类。容器
应该可以通过随机访问迭代器访问，并支持以下操作：
  empty() : 检测容器是否为空
  size() : 返回容器中的第一个元素的引用
  push_back() : 在容器尾部插入元素
  pop_back(): 删除容器尾部元素
*/

/*
二、priority_queue的使用：
priority_queue()/priority_queue(first，last) 构造一个优先级队列
empty() 检测优先级队列是否为空，是返回true 否则返回false
top() 返回优先级队列中最大(最小元素0，即堆顶元素)
push(x) 在优先级队列中插入元素x
pop() 删除优先级队列中最大(最小)元素，即堆顶元素
*/

//1.默认情况下，priority_queue是大堆
#include<queue>
#include<vector>
#include <functional> // greater算法的头文件
using namespace std;
void TestPriorityQueue1(){
	//默认情况下，创建的是大堆，其底层按照小于号比较
	vector<int> v{ 3, 2, 7, 6, 0, 4, 1, 9, 8, 5 };
	priority_queue<int> q1;
	for (auto a : v){
		q1.push(a);
	}
	cout << q1.top() << endl; //9

	//如果要创建小堆，将第三个模板参数换成greater比较方式
	priority_queue<int, vector<int>, greater<int>>q2(v.begin(), v.end());//0
	cout << q2.top() << endl;
}


//2.如果在priority_queue中放自定义类型数据 用户需要在自定义类型中提供>或者<的重载

class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}
	//<重载
	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}
	//>重载
	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}
	friend ostream& operator<<(ostream& _cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}
private:
	int _year;
	int _month;
	int _day;
};
void TestPriorityQueue2()
{
	// 大堆，需要用户在自定义类型中提供<的重载
	priority_queue<Date> q1;
	q1.push(Date(2018, 10, 29));
	q1.push(Date(2018, 10, 28));
	q1.push(Date(2018, 10, 30));
	cout << q1.top() << endl;
	// 如果要创建小堆，需要用户提供>的重载
	priority_queue<Date, vector<Date>, greater<Date>> q2;
	q2.push(Date(2018, 10, 29));
	q2.push(Date(2018, 10, 28));
	q2.push(Date(2018, 10, 30));
	cout << q2.top() << endl;
}
int main(){
	TestPriorityQueue2();
	return 0;
}
