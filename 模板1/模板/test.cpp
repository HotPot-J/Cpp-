#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

//ģ����ף�
	
/*
	1.���ͱ�̣�
		���ʵ��һ��ͨ�ý���������

			����: void Swap(int& left,int& right);
				  void Swap(double& left,double& right);
				  void Swap(char& left,char& right);
				  (���صĺ����������Ͳ�ͬ�����븴���ʵͣ���ά���Ե�)
			����ģ��:
				����ģ�������һ���������壬�ú���ģ���������޹أ���ʹ��ʱ
				��������������ʵ�����Ͳ����������ض����Ͱ汾��

			  ��ʽ: template<typename T1,typename T2,......typename Tn>
					����ֵ���� �������������б�{}

*/
 //����ʹ��ģ����ʵ��һ��ͨ�ý�������
//template<typename T>
//void Swap(T& left, T& right){
//	T tmp = left;
//	left = right;
//	right = tmp;
//
//}
//
//int main(){
//	//int a = 10;
//	//int b = 1;
//	
//	//double a= 10.1;
//	//double b = 1.0;
//	
//	char a = 'a';
//	char b = 'b';
//	Swap(a, b);
//	cout << "a = " << a << ",b = " << b << endl;
//	return 0;
//}

/*
2.����ģ���ʵ����
 �ò�ͬ���͵Ĳ���ʹ�ú���ģ��ʱ����Ϊ����ģ���ʵ������
		
*/
	//2.1��ʽʵ�������ñ���������ʵ�����ݳ�������ʵ������
//template<typename T>
//T add(const T& a, const T& b){
//	return a + b;
//}
//
//int main(){
//	int a1 = 10, a2 = 2;
//	double b1 = 10.0, b2 = 20.0;
//	//add(a1, b1);
//	/*
//		���д����޷�ͨ�����룬�����ڱ����ڼ䣬��������������ʵ��������Ҫ����
//		��ʵ�����ͣ�ʵ��a1��T����Ϊint��b1��Ϊdouble��������ģ��ֻ��һ��T��
//		�������޷�ȷ��TΪint����double
//		����ģ���У�������һ�㲻���������ת��������
//	*/
//
//	//����ʽ��
//	add(a1, (int)b1); //�û�ǿ��ת��
//	//��ʹ����ʽʽʵ������
//	return 0;
//}

   //2.2��ʽʵ�������غ��������<>��ָ��ģ�������ʵ������
//int main(){
//	int a = 10;
//	double b = 20.0;
//	add<int>(a, b);
//	add<double>(a, b);
//	return 0;
//}
  
/*3.ģ�������ƥ��ԭ��
	1.һ����ģ�庯�����Ժ�һ��ͬ���ĺ���ģ��ͬʱ���ڣ����Ҹú���ģ�廹���Ա�
   ʵ����Ϊ�����ģ�庯��
    2.���ڷ�ģ�庯����ͬ������ģ�壬���������������ͬ���ڵ���ʱ�����ȵ���
   ��ģ�庯����������Ӹ�ģ�����һ��ʵ�������ģ����Բ���һ�����и���ƥ��
   �ĺ�������ô��ѡ��ģ�塣
   3.ģ�庯���������Զ�����ת��������ͨ�������Խ����Զ�����ת��
*/
//����
//	//ר�Ŵ���int�ļӷ�����
//int add(int a, int b){
//	return a + b;
//}
//
////ͨ�üӷ�����
//template<typename T>
//T add(T a, T b){
//	return a + b;
//}
//
//int main(){
//	add(1, 2);//���ģ�庯��ƥ�䣬����������Ҫ�ػ�
//	add<int>(1, 2);//���ñ������ػ���add�汾
//	add(10.0, 20.0);//ģ�庯���������ɸ���ƥ��İ汾������������ʵ�����ɸ���ƥ���Add����
//	add(1, 2.0); //ģ�庯���������Զ�����ת�������÷�ģ�庯��
//
//	return 0;
//}

//4.��ģ��
/*
	template<class T1,class T2,......class Tn>
	class ��ģ����{
	 //���ڳ�Ա����
	};
*/
template<class T>
class Vector
{
public:
	Vector(size_t capacity = 10)
		: _pData(new T[capacity])
		, _size(0)
		, _capacity(capacity)
	{}

	// ʹ������������ʾ�������������������ⶨ�塣
	~Vector();

	void PushBack(const T& data)��
		void PopBack()��
		// ...

		size_t Size() { return _size; }

	T& operator[](size_t pos)
	{
		assert(pos < _size);
		return _pData[pos];
	}

private:
	T* _pData;
	size_t _size;
	size_t _capacity;
};