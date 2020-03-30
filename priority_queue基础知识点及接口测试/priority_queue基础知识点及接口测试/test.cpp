#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>


/*
һ��priority_queue�Ľ��ܣ�
  1.���ȶ�����һ�������������������ϸ���������׼�����ĵ�һ��Ԫ��������
������Ԫ�������ġ�
  2.�������������ڶѣ��ڶ��п�����ʱ����Ԫ�أ�����ֻ�ܼ�������Ԫ�أ�����
������λ�ڶ�����Ԫ�أ���
  3.���ȶ��б�ʵ��Ϊ���������������������������ض����������װ��Ϊ��ײ�
�����࣬queue�ṩһ���ض��ĳ�Ա������������Ԫ�ء�Ԫ�ش��ض������ġ�β����
���������Ϊ���ȶ��еĶ�����
  4.�ײ������������κα�׼������ģ�壬Ҳ�����������ض���Ƶ������ࡣ����
Ӧ�ÿ���ͨ��������ʵ��������ʣ���֧�����²�����
  empty() : ��������Ƿ�Ϊ��
  size() : ���������еĵ�һ��Ԫ�ص�����
  push_back() : ������β������Ԫ��
  pop_back(): ɾ������β��Ԫ��
*/

/*
����priority_queue��ʹ�ã�
priority_queue()/priority_queue(first��last) ����һ�����ȼ�����
empty() ������ȼ������Ƿ�Ϊ�գ��Ƿ���true ���򷵻�false
top() �������ȼ����������(��СԪ��0�����Ѷ�Ԫ��)
push(x) �����ȼ������в���Ԫ��x
pop() ɾ�����ȼ����������(��С)Ԫ�أ����Ѷ�Ԫ��
*/

//1.Ĭ������£�priority_queue�Ǵ��
#include<queue>
#include<vector>
#include <functional> // greater�㷨��ͷ�ļ�
using namespace std;
void TestPriorityQueue1(){
	//Ĭ������£��������Ǵ�ѣ���ײ㰴��С�ںűȽ�
	vector<int> v{ 3, 2, 7, 6, 0, 4, 1, 9, 8, 5 };
	priority_queue<int> q1;
	for (auto a : v){
		q1.push(a);
	}
	cout << q1.top() << endl; //9

	//���Ҫ����С�ѣ���������ģ���������greater�ȽϷ�ʽ
	priority_queue<int, vector<int>, greater<int>>q2(v.begin(), v.end());//0
	cout << q2.top() << endl;
}


//2.�����priority_queue�з��Զ����������� �û���Ҫ���Զ����������ṩ>����<������

class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}
	//<����
	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}
	//>����
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
	// ��ѣ���Ҫ�û����Զ����������ṩ<������
	priority_queue<Date> q1;
	q1.push(Date(2018, 10, 29));
	q1.push(Date(2018, 10, 28));
	q1.push(Date(2018, 10, 30));
	cout << q1.top() << endl;
	// ���Ҫ����С�ѣ���Ҫ�û��ṩ>������
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
