#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<cstring>
using namespace std;

/*
ģ����ػ�����ԭģ����Ļ�������������������������⻯��ʵ�ַ�ʽ��ģ��
�ػ���Ϊ����ģ���ػ�����ģ���ػ���
*/

//ģ�庯��δ�����ػ�����������������⣺

//һ���ȽϺ���
//template<class T>
//bool isequal(T& a, T& b){
//	return a == b;
//}
//int main(){
//	char* a = "123";
//	char* b = "456";
//	if (isequal(a, b)){
//		cout << 1 << endl;
//	}
//	else{
//		cout << 0 << endl;
//	}
//	return 0;
//}
/*
	���������е�a��bΪ�ַ�������ʱ����Ȼ�����Ƚ��ǲ�����ģ���ʱ����Ҫ
 ��ģ������ػ���(����ֱ�ӽ�����ĺ�����������)
*/
	

/*
����ģ���ػ��Ĳ��裺
	1.����Ҫ����һ�������ĺ���ģ��
	2.�ؼ���template���һ�Կյ�<>
	3.���������һ��<>����������ָ����Ҫ�ػ�������
	4.�����βα�����Ҫ��ģ�庯���Ļ�������������ȫ��ͬ
*/

//template<class T>
//bool isequal(T& a, T& b){
//	return a == b;
//}
//template<>
//bool isequal<char*>(char*& a, char*& b){
//	return strcmp(a, b) == 0;
//}
//int main(){
//	char* a = "123";
//	char* b = "123";
//	if (isequal(a, b)){
//		cout << 1 << endl;
//	}
//	else{
//		cout << 0 << endl;
//	}
//	return 0;
//}

/*��ģ���ػ�
  ȫ�ػ�
	ȫ�ػ����ǽ�ģ������б������еĲ�����ȷ����
  ƫ�ػ�
	1.�ػ������б��һ����
	2.���ģ���������һ����������������Ƴ�����һ���ػ��汾
*/

//template<class T1, class T2>
//class jxy
//{
//public:
//	jxy() { cout << "jxy<T1, T2>" << endl; }
//private:
//	T1 _d1;
//	T2 _d2;
//};
////ȫ�ػ�
//template<>
//class jxy<int, char> {
//public:
//	jxy() { cout << "jxy<int, char>" << endl; }
//private:
//	int _d1;
//	char _d2;
//};
//
////�����ػ�
//template<class T1>
//class jxy<T1, char> {
//public:
//	jxy() { cout << "jxy<T1, char>" << endl; }
//private:
//	T1 _d1;
//	char _d2;
//};
//
////��������ƫ�ػ�Ϊָ������
//template <typename T1, typename T2>
//class jxy <T1*, T2*>
//{
//public:
//	jxy() { cout << "jxy<T1*, T2*>" << endl; }
//
//private:
//	T1 _d1;
//	T2 _d2;
//};
//
//void TestVector()
//{
//	jxy<int, int> d1; //������ģ��
//	jxy<int, char> d2;//������ģ���ȫ�ػ�
//  jxy<double,char> d3;//���ò����ػ�
//  jxy<char*,char*>d4;//������������ƫ�ػ�ΪӦ������
//}
//int main(){
//	TestVector();
//	return 0;
//}

/*ģ������������⣺
	1.ʲô�Ƿ�����룿
		һ��������Ŀ�������ɸ�Դ�ļ���ͬʵ�֣���ÿ��Դ�ļ�������������Ŀ����
		�����������Ŀ���ļ����������γɵ�һ�Ŀ�ִ���ļ��Ĺ��̳�Ϊ�������ģ
		ʽ�� 
	2.ģ�������뵼�µġ����Ӵ��󡱱���ԭ��
		c/c++����Ҫ���У�һ�㾭�����²��裺
			Ԥ����-������-�����-������
		���룺�Գ������������Խ��дʷ����﷨�������������������������ɻ�
		����루ͷ�ļ���������룬�������Թ����еĶ��Դ�ļ����Ƿ��뿪�������룩
		���ӣ������obj�ļ��ϲ���һ����������û�н���ĵ�ַ����

 ���ӣ�
// a.h
template<class T> 
T Add(const T& left, const T& right);

// a.cpp
template<class T> 
T Add(const T& left, const T& right){
 return left + right; 
 }

 // main.cpp
#include"a.h"
int main(){
 Add(1, 2);
 Add(1.0, 2.0);
 return 0; 
 }

 ������a.cpp�У�������û�п�����Addģ�庯����ʵ��������˲������ɾ���ļӷ�����
 ��main.obj����Add<int>��Add<double>ʱ��������������ʱ�Ż������ַ������������
 ��û��ʵ������û�����ɾ�����룬�������ʱ����

 ��νϺõĽ����������?
	�������Ͷ���ŵ�һ���ļ���
*/

/*
ģ���ܽ᣺
	�ŵ�:
		1.ģ�帴���˴��룬��ʡ��Դ������ĵ���������c++�ı�׼ģ�����˲���
		2.��ǿ�˴���������
	ȱ�㣺
		1.ģ��ᵼ�´������͵����⣬Ҳ�ᵼ�±���ʱ��䳤
		2.����ģ��������ʱ��������Ϣ�ǳ����ң����׶�λ����
*/