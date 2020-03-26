#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<list>
#include<vector>
using namespace std;

/*
һ��list�Ľ��ܣ�#include<list>
 1.list�ǿ����ڳ�����Χ��������λ�ý��в����ɾ��������ʽ����������
����������ǰ��˫�������
 2.list�ĵײ���˫������ṹ��˫��������ÿ��Ԫ���ڻ�����صĶ����ڵ�
 �У��ڽڵ���ͨ��ָ��ָ����ǰһ��Ԫ�غͺ�һ��Ԫ�ء�
 3.list��forward_list�ǳ����ƣ�����Ҫ�Ĳ�ͬ����forward_list�ǵ�����
 ֻ�ܳ�ǰ��������������򵥸�Ч��
 4.����������ʽ������ȣ�arry��vector��deque����listͨ��������λ�ý�
 �в��롢�Ƴ�Ԫ�ص�ִ��Ч�ʸ��á�
 5.������������������ȣ�list��forward_list����ȱ���ǲ�֧������λ��
 ��������ʣ����磺Ҫ����list�ĵ�����Ԫ�أ��������֪��λ�ã�����ͷβ��
 ��������λ�ã������λ���ϵ�����Ҫ���Ե�ʱ�俪����list����ҪһЩ����
 �Ŀռ䣬�Ա���ÿ���ڵ���������Ϣ�����ڴ洢���ͽ�С��Ԫ�ص�list��˵
 �������һ����Ҫ�����أ���
*/

//list��ʹ��
/*
����list�Ĺ��죺
  list()   ����յ�list
  list(size_type n,const value_type& val = value_type()) �����list�а���n��ֵΪval��Ԫ��
  list(const list& x) �������캯��
  list(Inputlerator first��Inputlerator last) ��[first��last�������е�Ԫ�ع���list
*/

/*
����list iterator��ʹ��
 begin()+end()���ص�һ��Ԫ�صĵ�����+�������һ��Ԫ����һ��λ�õĵ�����
 rbegin+rend ���ص�һ��Ԫ�ص�reverse_iterator����endλ�ã��������һ��Ԫ��
 ��reverse_iterator,��beginλ��

 ע�⣺begin��endΪ������������Ե�����ִ��++����������������ƶ�
 rbegin(end)��rend(begin)Ϊ������������Ե�����ִ��++��������������ǰ�ƶ�

*/
void test1(){
	list<int> L1; //����յ�L1
	list<int> L2(4, 100); //L2�з��ĸ�ֵΪ100��Ԫ��
	list<int> L3(L2.begin(), L2.end()); //��L2��[begin(),end())����ҿ����乹��L3
	list<int> L4(L3); //��L3��������L4

	//������Ϊ���������乹��L5 ��������begin-end
	int arry[] = { 16, 2, 77, 29 };
	list<int> L5(arry, arry + sizeof(arry) / sizeof(int));

	//�õ�������ӡL5�е�Ԫ��
	list<int>::iterator it = L5.begin();
	while (it!=L5.end()){
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//��Χfor����L5
	for (auto L : L5){
		cout << L << " ";
	}
	cout << endl;
}

/*
�ġ����ֺ����ӿ�
 1.list capacity
  empty ���list�Ƿ�Ϊ�գ��Ƿ���true�����򷵻�false
  size  ����list����Ч�ڵ�ĸ���

 2.list element access���б�Ԫ�ط��ʣ�
 front ����list�ĵ�һ���ڵ���ֵ������
 back  ����list�����һ���ڵ���ֵ������

 3.��list�ĸ�����ɾ����
 push_front ͷ��
 pop_front ͷɾ
 push_back β��
 pop_back βɾ
 insert ��ĳ��λ�ý��в������
 erase ɾ��ĳ��λ�õ�Ԫ��
 swap ��������list�е�Ԫ��
 clear ���list�е���ЧԪ��
*/

//��ӡ����
void PrintList(list<int>& L){
	for (auto l : L){
		cout << l << " ";
	}
	cout << endl;
}

//push_back/pop_back/push_front/pop_front
void TestList1(){
	int array[] = { 1, 2, 3 };
	list<int> L(array, array + sizeof(array) / sizeof(array[0]));

	//��listͷ������0 β������4
	L.push_front(0);
	L.push_back(4);
	PrintList(L); //0 1 2 3 4

	//ɾ��ͷ�ڵ��β�ڵ�
	L.pop_front();
	L.pop_back();
	PrintList(L);//1 2 3
}

//insert/erase
void TestList2(){
	int array[] = { 1, 2, 3 };
	list<int> L(array, array + sizeof(array) / sizeof(array[0]));

	//��ȡ�����еĵڶ����ڵ�
	auto pos = ++L.begin();
	cout << *pos << endl; //2

	//��posǰ����ֵΪ4��Ԫ��
	L.insert(pos, 4);
	PrintList(L);//1 4 2 3

	//��posǰ����3��ֵΪ3��Ԫ��
	L.insert(pos, 3, 3);
	PrintList(L);//1 4 3 3 3 2 3

	//��posǰ����һ��[v.begin(),v.end())�����е�Ԫ��
	vector<int> v{ 7, 8, 9 };
	L.insert(pos, v.begin(), v.end());
	PrintList(L);//1 4 3 3 3 7 8 9 2 3

	//ɾ��posλ���ϵ�Ԫ��
	L.erase(pos);
	PrintList(L);//1 4 3 3 3 7 8 9 3

	//ɾ��list[begin,end)�����е�Ԫ�أ���ɾ��L������Ԫ��
	L.erase(L.begin(), L.end());
	PrintList(L);
	//�ж��Ƿ�ɾ���ɹ�
	if (L.empty()){
		cout << "LΪ��" << endl;
	}
}

//size/swap/clear
void TestList3(){
	//�����鹹��list
	int array[] = { 1, 2, 3 };
	list<int> L1(array, array + sizeof(array) / sizeof(array[0]));
	list<int> L2;
	PrintList(L1);
	if (L2.empty()){
		cout << "L2Ϊ��" << endl;
	}

	cout << "����L1��L2�е�Ԫ��:" << endl;
	//����L1��L2�е�Ԫ��
	L1.swap(L2);
	if (L1.empty()){
		cout << "L1Ϊ��" << endl;
	}
	PrintList(L2);

	//��L2�е�Ԫ�����
	L2.clear();
	cout << L2.size() << endl;
	
}

int main(){
	TestList3();
	return 0;
}

/*
list������ʧЧ��
  ������ʧЧ����������ָ��Ľڵ����Ч�����ýڵ㱻ɾ���ˡ�����list��
�ײ�ṹΪ��ͷ�ڵ��˫��ѭ�����������list�н��в���ʱ�ǲ��ᵼ��list
�ĵ�����ʧЧ�ģ�ֻ����ɾ��ʱ�Ż�ʧЧ������ʧЧ��ֻ��ָ��ɾ���ڵ�ĵ�������
���������������ܵ�Ӱ�졣
*/

/*
list��vector�ĶԱȣ�
vector��list����STL�зǳ���Ҫ������ʽ�������������������ĵײ�ṹ��ͬ��
�����������Լ�Ӧ�ó�����ͬ������Ҫ��ͬ���£�


1.�ײ�ṹ�Ĳ�ͬ��
             vector����̬˳���һ�������Ŀռ�
			 list����ͷ�ڵ��˫��ѭ������

2.�������:  
             vector��֧��������ʣ�����ĳ��Ԫ�ص�Ч��O(1)
             list:��֧��������ʣ�����ĳ��Ԫ��Ч��O(n)

3.�����ɾ����
             vector������λ�ò����ɾ��Ч�ʵͣ���Ҫ����Ԫ�أ�ʱ�临�Ӷ�
			 ΪO(N),�������ǿ�����Ҫ���ݣ������µĿռ䣬����Ԫ�أ��ͷžɿռ䣬����Ч�ʸ��ͣ�
			 list������λ�ò����ɾ��Ч�ʸߣ�����Ҫ����Ԫ�أ�ʱ�临�Ӷ�ΪO(1)

4.�ռ������ʣ� 
             vector���ײ�Ϊ�����ռ䣬����������ڴ���Ƭ���ռ������ʸߣ����������ʸ�
             list���ײ�ڵ㶯̬���٣�С�����������ڴ���Ƭ���ռ������ʵͣ����������ʵ�

5.��������   
             vector��ԭ��ָ̬��
			 list����ԭ��ָ̬��(�ڵ�ָ��)���з�װ

6.������ʧЧ��
             vector���ڲ���Ԫ��ʱ��Ҫ�����еĵ��������¸�ֵ����Ϊ����Ԫ���п��ܻᵼ���������ݣ���ʹԭ���ĵ�����ʧЧ
			 list�� ����Ԫ�ز��ᵼ�µ�����ʧЧ��ɾ��Ԫ��ʱֻ�ᵼ�µ�ǰ������ʧЧ����������������Ӱ��

7.ʹ�ó�����
             vector����Ҫ��Ч�洢��֧��������ʣ������Ĳ���ɾ��ɾ��Ч��
			 list�����������ɾ���������������������
*/