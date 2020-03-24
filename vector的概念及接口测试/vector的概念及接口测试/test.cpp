#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;
/*
һ��vector�Ļ�������:
vector:#include<vector>
  1.vector�Ǳ�ʾ�ɱ��С�������������
  2.��������һ����vectorҲ���õ������洢�ռ����洢Ԫ�ء�Ҳ������ζ��
  ���Բ����±��vector��Ԫ�ؽ��з��ʣ�������һ����Ч�������ֲ�������
  ���Ĵ�С�ǿ��Զ�̬�ı�ģ��������Ĵ�С�ᱻ�����Զ�����
  3.���ʽ���vectorʹ�ö�̬�����������洢����Ԫ�ء�����Ԫ�ز����ʱ��
  ���������Ҫ�����·����С��Ϊ�����Ӵ洢�ռ䣬�������Ƿ���һ���µ�
  ���飬Ȼ��ȫ��Ԫ���Ƶ�������飬����ʱ����ԣ�����һ����Դ��۸�
  ����������vector������ÿ�ζ����·����С��
  4.vector����ռ���ԣ�vector�����һЩ����Ŀռ�����Ӧ���ܵ�������
  ��Ϊ�洢�ռ��ʵ����Ҫ�Ĵ洢�ռ���󡣲�ͬ�Ŀ���ò�ͬ�Ĳ���Ȩ���
  ���ʹ�ú����·��䡣��������Σ����·��䶼Ӧ���Ƕ��������ļ���Ĵ�
  С����������ĩβ����һ��Ԫ�ص�ʱ�����ڳ���ʱ��ĸ��Ӷ���ɵġ�
  5.��ˣ�vectorռ���˸���Ĵ洢�ռ䣬Ϊ�˻�ù���洢�ռ����������
  ����һ����Ч�ķ�ʽ��̬������
  6.��������̬����������ȣ�vector�ڷ���Ԫ�ص�ʱ����Ӹ�Ч����ĩβ��
  ɾԪ����Ը�Ч��������������ĩβ��ɾ���Ͳ��������Ч�ʸ��͡�
*/
/*
����vector�Ķ��壺
  vector()   �޲ι���
  vector(size_type n,const value_type& val = value_type()) ���첢��ʼ��n��val
  vector(const vector& x)   ��������
  vector(Inputlterator first,Inputlterator last) ʹ�õ��������г�ʼ������
*/ 
void test1(){
	vector<int> first; //int���͵Ŀ�vector
	vector<int> second(4, 100);//����һ���ռ�Ϊ4��int���͵�vector������ʼ�����ĸ�Ϊ100
	vector<int> third(second.begin(), second.end());//ʹ�õ��������г�ʼ��
	vector<int> fourth(third);//��������
}

/*
����vector iterator��ʹ�� ��vector����������
  begin+end   ��ȡ��һ������λ�õ�iterator_iterator����ȡ���һ�����ݵ���һ��λ��iterator_iterator/const_iterator

    1 2 3 4 5 6 7 8 9 10
	|                    |
	begin()              end()
*/

void PrintVector(const vector<int>& v){
	//const����ʹ��const���������б�����ӡ
	vector<int>::const_iterator it = v.begin();
	while (it != v.end()){
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

//int main(){
//	vector<int> v(4,100);
//	//ʹ�õ��������д�ӡ
//	PrintVector(v);
//
//	//ʹ�õ����������޸�
//	vector<int>::iterator it = v.begin();
//	while (it != v.end()){
//		*it = 2;
//		++it;
//	}
//	PrintVector(v);
//	return 0;
//}

/*
�ġ�vector �ռ���������

size ��ȡ���ݸ���
capacity ��ȡ������С
empty �п�
resize �ı�vector��size
reserve �ı�vector������
ע�⣺vs��capacity�ǰ���1.5�������ģ�g++�ǰ�������������
reserveֻ���𿪱ٿռ䣬���ȷ��֪����Ҫ�ٶ��ٿռ䣬reserve���Ի���vector���ݵĴ���ȱ������
resize�ڿ��ռ��ͬʱ������г�ʼ��
*/

void test2(){
	size_t sz;
	vector<int> f;
	sz = f.capacity();
	cout << "f�ĳ�ʼ����Ϊ��"<<sz << endl;
	cout << "ʹf������" << endl;
	for (int i = 0; i < 100; ++i){
		f.push_back(i);
		if (sz != f.capacity()){
			sz = f.capacity();
			cout << "f��capacity�Ѿ����ı�Ϊ��" << sz << endl;
		}
	}
}
/*
vs�����н����
f�ĳ�ʼ����Ϊ��0
ʹf������
f��capacity�Ѿ����ı�Ϊ��1
f��capacity�Ѿ����ı�Ϊ��2
f��capacity�Ѿ����ı�Ϊ��3
f��capacity�Ѿ����ı�Ϊ��4
f��capacity�Ѿ����ı�Ϊ��6
f��capacity�Ѿ����ı�Ϊ��9
f��capacity�Ѿ����ı�Ϊ��13
f��capacity�Ѿ����ı�Ϊ��19
f��capacity�Ѿ����ı�Ϊ��28
f��capacity�Ѿ����ı�Ϊ��42
f��capacity�Ѿ����ı�Ϊ��63
f��capacity�Ѿ����ı�Ϊ��94
f��capacity�Ѿ����ı�Ϊ��141  vs�����е�ȷΪ1.5������
*/

//reserve
void test3()
{
	size_t sz;
    vector<int> foo;
	sz = foo.capacity();
	cout << "making foo grow:"<<endl;
	for (int i = 0; i<100; ++i) {
		foo.push_back(i);
		if (sz != foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << endl;
		}
	}
	vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100); // ������foo��ͬ�ĵط�
	cout << "making bar grow:"<<endl;
	for (int i = 0; i<100; ++i) {
		bar.push_back(i);
		if (sz != bar.capacity()) {
			sz = bar.capacity();
			cout << "capacity changed: " << sz << endl;
		}
	}
}
/*
���н����
making foo grow:
capacity changed: 1
capacity changed: 2
capacity changed: 3
capacity changed: 4
capacity changed: 6
capacity changed: 9
capacity changed: 13
capacity changed: 19
capacity changed: 28
capacity changed: 42
capacity changed: 63
capacity changed: 94
capacity changed: 141
making bar grow:        //���Ƿ���ʹ��reserve�趨�Ŀռ��С capacity�Զ����Ӳ��ᳬ���趨��С
capacity changed: 100
*/

// vector::resize
void test4()
{
	vector<int> myvector;
	// set some initial content:
	for (int i = 1; i < 10; i++){
		myvector.push_back(i);
	}
	myvector.resize(5); //ʹ��Ч����Ϊ5
	myvector.resize(8, 100);//ʹ��Ч����Ϊ8 ����Ĳ�����100����
	myvector.resize(12); //ʹ��Ч����Ϊ12 ����Ļ��Զ���0����
	std::cout << "myvector contains:";
	for (int i = 0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	cout <<endl;
}
/*
���н����
myvector contains: 1 2 3 4 5 100 100 100 0 0 0 0
�밴���������. . .
*/

/*
5��vector��ɾ���
push_back  β��
pop_back βɾ��
find ���ң���ʹ�㷨ģ���ʵ�֣�����vector�ĳ�Ա�ӿڣ�ʹ��find�ҵ���pos��ʹ��һ�κ��ʧЧ�� �´���ʹ�õ������ң������5.vector������ʧЧ���⣩
insert ��position֮ǰ����val
erase ɾ��positionλ�õ�����
swap ��������vector�����ݿռ�
operator[] ������һ������
*/
//push_back/pop_back
void test5(){
	int a[] = { 1, 2, 3, 4, 5 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));//������ʹ�õ��������г�ʼ��

	vector<int>::iterator it = v.begin();
	while (it != v.end()){
		cout << *it << " ";
		++it;
	}
	cout << endl;
	v.pop_back();//βɾ
	it = v.begin();
	while (it != v.end()){
		cout << *it << " ";
		++it;
	}
}

//find/insert/erase/swap
//operator[]+index ��for+auto���ֱ�����ʽ
void test6(){
	int a[] = { 1, 2, 3, 4, 5 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));

	//ʹ��find����3����λ�õ�iterator
	vector<int>::iterator pos = find(v.begin(), v.end(), 3);

	//��posλ��֮ǰ����6
	v.insert(pos, 6);

    //operator[]+index ����
	for (int i = 0; i < v.size(); ++i){
		cout << v[i] << " ";
	}
	cout << endl;

   //ɾ��posλ�õ�����
	cout << "ɾ��posλ�õ�����:" << endl;
	pos = find(v.begin(), v.end(), 3);//������pos ֮ǰpos��ֵʹ�ù�һ�κ������ֵ�ˣ�
	 //�õ�����ʧЧ�ˣ����ײ���ָ��Ŀռ���ʹ��һ�λᱻ�Զ��ͷ�
	v.erase(pos);

   //for+auto��ʽ����
	for (auto x : v){
		cout << x << " ";
	}
	cout << endl;
	//ʹ��swap ����v��swapv�����ݿռ�
	cout << "ʹ��swap ����v��swapv�����ݿռ�:"<<endl;
	vector<int> swapv;
	swapv.swap(v);

	cout << "�������v��" << endl; //����޴�ӡ���
	for (auto x : v){
		cout << x << " ";
	}
	cout << endl;
	cout << "�������swapv��" << endl;//���֮ǰv����ֵ ˵�������ɹ�
	for (auto x : swapv){
		cout << x << " ";
	}
	cout << endl;
}
/*
6��vector������ʧЧ���⣺
����������Ҫ���þ������㷨�ܹ����ù��ĵײ����ݽṹ����ʵ�ײ����һ��ָ�룬
����˵�Ƕ�ָ������˷�װ�����磺vector�ĵ���������ԭ��ָ̬��T*�����
������ʧЧ��ʵ���Ͼ��ǵ������ײ��Ӧָ����ָ��Ŀռ䱻�����ˣ���ʹ��
һ���Ѿ����ͷŵĿռ䣬��ɵĺ���ǳ�������������ʹ���Ѿ�ʧЧ�ĵ�������
������ܻ��������
*/
int main(){
	test6();
	return 0;
}
