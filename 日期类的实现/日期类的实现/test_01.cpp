#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
class Date
{
public:
	// ��ȡĳ��ĳ�µ�����
	int GetMonthDay(int year, int month)
	{
		static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = days[month];
		if (month == 2
			&& ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
			//���߼��ж��Ƿ�Ϊ����Ķ��� ���� �����Ϊ29��
		{
			day += 1;
		}
		return day;
	}
	// ȫȱʡ�Ĺ��캯��
	Date(int year = 1900, int month = 1, int day = 1){
		if (year > 0
			&& month > 0 && month<13
			&& day>0 && day <= GetMonthDay(year, month)){
			_year = year;
			_month = month;
			_day = day;
		}
		else{
			cout << "�����ڷǷ�" << endl;
		}

	}
	


	// ����+����
	//d1+100  �� d1.operator+(&d1,100);
	//Data operator+(Date *this,int day);��ʵ�����б����и�������thisָ��
	Date operator+(int day){ 
		//+ ���ܸı䴫�����Ķ����� ������Ҫ��������һ����ʱ�Ķ���
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
		return tmp; //���ﲻ�������÷��� ��Ϊ���������� tmp�Ŀռ�ͱ������� 
		 //�������+=���� �Ϳ����÷��� ��Ϊ����ֱ�����������ж���Ķ�������޸ĵ� ����ʹ�øú�������ֵλDate&
	}


	// ����+=����
	Date& operator+=(int day){
		if (day<0){
			*this -= -day;
			return *this;
		}
		_day += day;
		while (_day > GetMonthDay(_year, _month)){
			//������ǰ�µĺϷ�����
			_day -= GetMonthDay(_year, _month);
			//�½�1
			_month++;
			if (_month == 13){
				//���·ݳ��� ���һ  ����Ϊ1
				_year++;
				_month = 1;
			}
		}
		return *this;
	}

    // ����-=����
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

	// ����-����
	Date operator-(int day){
		//����-��-=�߼���ͬ ֻ��-���ı������ ���Կ���������д��
		Date tmp(*this);
		tmp -= day;
		return tmp;
	}


	// ǰ��++ 
	//++day
	Date& operator++(){
		*this += 1;
		return *this;
	}

	// ����++
	//day++
	Date operator++(int){ //Ϊ�˺�ǰ��++�������� �������һ������int
		//����++֮ǰ��ֵ
		Date tmp(*this);//�ȿ�������һ��֮ǰ��ֵ
		*this += 1;
		return tmp;
	}

	// ����--
	Date operator--(int){
		Date tmp(*this);//�ȿ�������һ��֮ǰ��ֵ
		*this -= 1;
		return tmp;
	}
	// ǰ��--
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

	//����-���� ��������
	int operator-(const Date& d){
		int ret = 0;
		Date tmp(d);
		//���ж�˭��
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