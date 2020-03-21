#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
class Date
{
public:
	// 获取某年某月的天数
	int GetMonthDay(int year, int month)
	{
		static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = days[month];
		if (month == 2
			&& ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
			//该逻辑判断是否为闰年的二月 若是 则该月为29天
		{
			day += 1;
		}
		return day;
	}
	// 全缺省的构造函数
	Date(int year = 1900, int month = 1, int day = 1){
		if (year > 0
			&& month > 0 && month<13
			&& day>0 && day <= GetMonthDay(year, month)){
			_year = year;
			_month = month;
			_day = day;
		}
		else{
			cout << "该日期非法" << endl;
		}

	}
	


	// 日期+天数
	//d1+100  即 d1.operator+(&d1,100);
	//Data operator+(Date *this,int day);其实参数列表里有个隐含的this指针
	Date operator+(int day){ 
		//+ 不能改变传进来的对象本身 所以需要拷贝构造一个临时的对象
		Date tmp(*this);
		tmp._day += day;
		while (tmp._day > GetMonthDay(tmp._year, tmp._month)){
			tmp._day -= day;
			tmp._month++;
			if (tmp._month == 13){
				tmp._year++;
				tmp._month = 1;
			}
		}
		return tmp; //这里不能用引用返回 因为出了作用域 tmp的空间就被销毁了 
		 //而下面的+=函数 就可以用返回 因为其是直接再主函数中定义的对象进行修改的 所以使用该函数返回值位Date&
	}


	// 日期+=天数
	Date& operator+=(int day){
		if (day<0){
			*this -= -day;
			return *this;
		}
		_day += day;
		while (_day > GetMonthDay(_year, _month)){
			//减到当前月的合法天数
			_day -= GetMonthDay(_year, _month);
			//月进1
			_month++;
			if (_month == 13){
				//当月份超出 年进一  月置为1
				_year++;
				_month = 1;
			}
		}
		return *this;
	}

    // 日期-=天数
	Date& operator-=(int day){
		if (day < 0){
			*this += -day;
			return *this;
		}
		_day -= day;
		while (_day <= 0){
			_month--;
			_day += GetMonthDay(_year, _month);
			if (_month == 0){
				_year--;
				_month = 12;
			}
		}
		return *this;
	}

	// 日期-天数
	Date operator-(int day){
		//由于-和-=逻辑相同 只是-不改变对象本身 所以可以有如下写法
		Date tmp(*this);
		tmp -= day;
		return tmp;
	}


	// 前置++ 
	//++day
	Date& operator++(){
		*this += 1;
		return *this;
	}

	// 后置++
	//day++
	Date operator++(int){ //为了和前置++构成重载 再这里加一个参数int
		//返回++之前的值
		Date tmp(*this);//先拷贝构造一份之前的值
		*this += 1;
		return tmp;
	}

	// 后置--
	Date operator--(int){
		Date tmp(*this);//先拷贝构造一份之前的值
		*this -= 1;
		return tmp;
	}
	// 前置--
	Date operator--(){
		*this += 1;
		return *this;
	}

	//>
	bool operator>(const Date& d){
		if (_year > d._year){
			return true;
		}
		if (_year == d._year&&_month > d._month){
			return true;
		}
		if (_year == d._year&&_month == d._month&&_day > d._month){
			return true;
		}
		return false;
	}

	//==
	bool operator==(const Date&d){
		return  _year == d._year&&
			_month == d._month&&
			_day == d._day;
	}

	//日期-日期 返回天数
	int operator-(const Date& d){
		int ret = 0;
		Date tmp(d);
		//先判断谁大
		if (*this > tmp){
			while (1)
			{
				if (*this == tmp){
					break;
				}
				tmp++;
				ret++;
			}
		}
		else{
			while (1)
			{
				if (*this == tmp){
					break;
				}
				(*this)++;
				ret++;
			}
		}
		return ret;
	}

	void print(){
		cout << _year << "-" << _month << "-" << _day << "-"<<endl;
	}
private:
	int _year;
	int _month;
	int _day;
};
int main(){
	Date d1(2020, 4, 29);
	Date d2(2020, 3, 29);
	cout << (d1 - d2) << endl;
	return 0;
}