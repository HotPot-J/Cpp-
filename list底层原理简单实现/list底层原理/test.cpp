#define _CRT_SECURE_NO_WARNINGS 1

/*
list�ײ�Ϊ��ͷ�ڵ��˫��ѭ������
list�ŵ�:
	1.ͷ�塢�м�岻��ҪŲ������ Ч�ʸߣ�������λ�õĲ����ɾ��Ч�ʸ��ߣ�
	2.list�Ĳ�����������㣬���������ݡ�
ȱ��:
	1.��֧��������ʣ�����Ҫ����֪λ�õ�����Ŀ��λ�ã���Ҫʱ�俪����
	2.list����ҪһЩ����Ŀռ��Ա���ÿ���ڵ�������Ϣ�������һЩС����������Ҫ
	���ǵ����⣨���ܹ˴�ʧ�ˣ���

������ʧЧ���⣺
	������ʧЧ����������ָ��Ľ����Ч�����ýڵ㱻ɾ���ˡ�
	����list�ĵײ�ṹΪ��ͷ�ڵ��˫��ѭ�����������list
	�в��루insert��ʱ���ᵼ��list������ʧЧ��ֻ��ɾ����erase
	��ʱ�Ż�ʧЧ������ʧЧ��ֻ��ָ��ɾ�����ĵ�����������
	�����������ܵ�Ӱ�졣

list��vector�ĶԱȣ�
	1.�ײ�ṹ�ĽǶ�: 
		vector:˳���һ�������Ŀռ䣨�߼����� ����������
		list����ͷ�ڵ��˫��ѭ�������߼�����������������
	2.������ʽǶȣ�
		vector:֧��������ʣ�����ĳ��Ԫ�ص�Ч��ΪO(1)
		List:��֧��������ʣ�����ĳ��Ԫ�ص�Ч��ΪO(n)
	3.�����ɾ����
		vector:����Ч�ʵͣ���ҪŲ��Ԫ�أ�ʱ�临�Ӷ�ΪO(n)
		������ʱ������Ҫ����(�漰��� ���۴�)
		list:������λ�õĲ����ɾ��Ч�ʸߣ�����Ҫ����Ԫ��
		ʱ�临�Ӷ�ΪO(1)
	4.�ռ������ʣ�
		vector:�ײ�Ϊ�����Ŀռ䣬����������ڴ���Ƭ���ռ������ʸ�
		list:�ײ��㶯̬���٣�С�����������ڴ���Ƭ���ռ������ʵ�

	5.��������
		vector:ԭ��ָ��
		list����ԭ��ָ��(���ָ����з�װ)
	6.������ʧЧ��
		vector���κ��漰���������ݵĲ�������ʹ������ʧЧ
		list:ֻ����ɾ��ʱ�ᵼ�µ�ǰ������ʧЧ
	7.ʹ�ó���:
		vector:��Ҫ��Ч�洢��֧��������ʣ������Ĳ���ɾ��Ч��
		list�������Ĳ���ɾ���������������������

*/

/*
��㣺
	template<class T>
	struct _list_node{
		_list_node<T>* next;
		_list_node<T> prev;
		T data;
	};
//ʵ�ֵ�������ǰ��++ --  ����++ -- ����* ->
*/

/*
ģ��ʵ�ֵ�ʱ����ǣ���ײ�Ϊ��ͷ�ڵ��˫��ѭ������ ����ײ�˽�г�Ա�����Ͷ���һ��ͷ�ڵ㼴��
*/

#include<iostream>
using namespace std;

namespace jxy{

	template<class T>
	struct Node{
		Node* _pre;
		Node* _next;
		T val;
		Node(const T& _val = T())
			:_pre(nullptr),
			_next(nullptr),
			val(_val)
		{}
	};

	//��װ������
	template<class T>
	class ListIterator{
		typedef struct Node<T> Node;
		typedef ListIterator<T> Self;
	public:
		Node* _node;
		//����
		ListIterator(Node* node)
			:_node(node)
		{}
		//����*
		T& operator*(){
			return _node->val;
		}
		//����-> (�����Զ�������)
		T* operator->(){
			return &_node->val;
		}
		//����ǰ��++
		Self& operator++(){
			_node = _node->_next;
			return *this;
		}
		//����++
		Self operator++(int){
			Self tmp = *this;
			_node = _node->_next;
			return tmp;
		}
		bool operator!=(const Self& it){
			return it._node != _node;
		}
	};

	template<class T>
	class list{
		typedef  Node<T> Node;
	public:
		typedef  ListIterator<T> iterator;
		//���캯��
		list(){
			_head = new Node();
			_head->_pre = _head;
			_head->_next = _head;
		}
		//push_back β��  
		void push_back(const T& val){
			//�ȴ���һ�����
			Node* newNode = new Node(val);

			_head->_pre->_next = newNode;
			newNode->_pre = _head->_pre;
			_head->_pre = newNode;     //ͷ�ڵ��ǰ����Զ�����һ������λ��     
			newNode->_next = _head;    //���һ�����ĺ����Զ��ͷ�ڵ�
		}
		iterator begin(){
			return iterator(_head->_next); //��һ����Чλ��
		}
		iterator end(){
			return iterator(_head); //���һ����Чλ�õ���һ��λ�þ���ͷ�ڵ� ����ͷ��ѭ��˫������
		}
	private:
		Node* _head;//ͷ
	};

	void test(){
		list<int> l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		list<int>::iterator it = l.begin();
		while (it != l.end()){
			cout << *(++it) << " ";
		}
		cout << endl;
		 it = l.begin();
		while (it != l.end()){
			cout << *(it++) << " ";
		}
	}
}
int main(){
	jxy::test();
	return 0;
}