#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
/*
1.��c++11����ʶ��
	���֮ǰ�İ汾��c++11�ܸ��õ�����ϵͳ�����Ϳ⿪�����﷨���ӷ����ͼ򵥻�
	�����ȶ��Ͱ�ȫ���������ܸ�ǿ�󣬶�������������Ա�Ŀ���Ч��
*/

/*
��ֵ���ã�
	���ü����������ñ�����������ʵ�幫��ͬһ��ռ䣬�����õĵײ���ͨ��ָ��
	��ʵ�ֵģ����ʹ�����ã�����߳���Ŀɶ��ԡ�
*/

//��������ֵ���û�����ֵ���ã����Ǹ�����ȡ����
//������ֵ������Ҫ����ֵȡ��������ֵ������Ҫ�Ǹ���ֵȡ������

//ʲô����ֵʲô����ֵ��
//int a = 10; int b = a;  a�����������ʽ��Ϊ��ֵ������ֻ�����������жϣ�
//10Ϊ��ֵ��bΪ��ֵ

//�����޸ĵ�Ϊ��ֵ����ֵͨ���Ǳ���
//��ֵͨ���ǳ��������ʽ���ߺ�������ֵ����ʱ����

void test1(){
	//��ֵ���õĶ��壺
	int a = 0;
	int& b = a;
	//int& c = 10;//��ֵ������������ֵ
	const int&e = 10; //������¿��ԣ�e��ʱΪconst��
	//��ֵ���õĶ��壺
	int x = 1, y = 2;
	int&& c = 10;
	int&& d = x + y;//(x+y�ķ���ֵΪ��ֵ)
	//��ֵ����������ֵ�����ǿ�������move�����ֵ
	//int&& m = a;
	int&& m = move(a); //������¿���
}

/*
c++11����ֵ��Ϊ:
	����ֵ���������͵ĳ���������ʱ����
	����ֵ���Զ������͵���ʱ���󣨼���������ֵ��
*/


class _string{
public:
	_string(const char* str = ""){
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}
	//�����ݹ�����Ϊ��ֵ��Ӳ��ͷƤȥ���
	_string(const _string& s){
		cout << "_string(const _string& s) ��� Ч�ʵ�" << endl;
		_str = new char[strlen(s._str) + 1];
		strcpy(_str, s._str);
	}

	//�����ݹ�����Ϊһ������ֵ����Ȼ����������������ֱ�ӽ�����Դ���������
	//�˷ѿռ����
	_string( _string&& s)
		:_str(nullptr) //��ֹswap���ֵ
	{
		cout << "__string(_string&& s) �ƶ���ֵ Ч�ʸ�" << endl;
		swap(s._str, _str);
	}

	_string& operator = (const _string& s){
		cout <<  " _string& operator = (const _string& s) ��� Ч�ʵ�" << endl;
		if (this != &s){
			char* newstr = new char[strlen(s._str) + 1];
			strcpy(newstr, s._str);
			delete[] _str;
			_str = newstr;
		}
		return *this;
	}

	_string& operator = (_string&& s){
		cout << " _string& operator = (_string&& s) �ƶ���ֵ Ч�ʸ�" << endl;
		swap(_str, s._str);
		return *this;
	}

	~_string(){
		delete[] _str;
	}
private:
	char* _str;
};
_string _tmp(const char* str){
	_string tmp(str);
	return tmp; //�÷���ֵ�������е�tmp�����е�tmp�ں��������������ڽ���
			   //���صļ�Ϊ��ֵ�еĽ���ֵ
}
int main(){
	_string a("��ֵ");
	_string b(a);
	_string c(_tmp("��ֵ-����ֵ"));

	_string d("��");
	 d = a;
	 d = _tmp("��ֵ-����ֵ");
	return 0;
}
/*
ִ�н����
_string(const _string& s) ��� Ч�ʵ�
__string(_string&& s) ֱ�ӽ��� Ч�ʸ�
�밴���������. . .
*/

/*
��ʵ�в��ɱ�����ڴ�ֵ���صĳ�������ֵ���صĿ������ض������ʱ����
��ֵ�������岻�󣬵�����ֵ����ʵ�����ƶ�������ƶ���ֵ����ô���
���պ�����ֵ���ض�����ֵ���ȵȳ������������Ч�ʡ�

��ֵ���ú���ֵ���õı��ʶ��Ǽ��ٿ���

��ֵ����: 
	������:void f1��T x��--��void f1(T& x)(�ڴ��μ��ٿ���)
	������ֵ: Tf2() --�� T& f2() ����Ҫע�⣬������ض����������������
								�Ͳ����ô�ֵ����

��ֵ����:
	�������� void push(const T&& x) --����push�ڲ����ٿ����� 
										��push�ڲ�ֱ�����ƶ�������߸�ֵ���������
	������ֵ�����һ��������T f2��������һ������ֵ�� T ret = f2��������
	�������ֵ�������ý���ֵ�����ƶ���ֵ���Ϳ��Ա������

*/