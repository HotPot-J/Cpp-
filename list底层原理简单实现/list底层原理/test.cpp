#define _CRT_SECURE_NO_WARNINGS 1

/*
list底层为带头节点的双向循环链表
list优点:
	1.头插、中间插不需要挪动数据 效率高（在任意位置的插入和删除效率更高）
	2.list的插入是新增结点，而不是增容。
缺点:
	1.不支持随机访问（其需要从已知位置迭代到目标位置，需要时间开销）
	2.list还需要一些额外的空间以保存每个节点的相关信息（这对于一些小型数据是需要
	考虑的问题（不能顾此失彼））

迭代器失效问题：
	迭代器失效即迭代器所指向的结点无效，即该节点被删除了。
	由于list的底层结构为带头节点的双向循环链表，因此在list
	中插入（insert）时不会导致list迭代器失效，只有删除（erase
	）时才会失效。而且失效的只是指向被删除结点的迭代器，其他
	迭代器不会受到影响。

list与vector的对比：
	1.底层结构的角度: 
		vector:顺序表，一段连续的空间（逻辑连续 物理连续）
		list：带头节点的双向循环链表（逻辑连续，物理不连续）
	2.随机访问角度：
		vector:支持随机访问，访问某个元素的效率为O(1)
		List:不支持随机访问，访问某个元素的效率为O(n)
	3.插入和删除：
		vector:插入效率低，需要挪动元素，时间复杂度为O(n)
		插入有时可能需要增容(涉及深拷贝 代价大)
		list:在任意位置的插入和删除效率高，不需要搬移元素
		时间复杂度为O(1)
	4.空间利用率：
		vector:底层为连续的空间，不容易造成内存碎片，空间利用率高
		list:底层结点动态开辟，小结点容易造成内存碎片，空间利用率低

	5.迭代器：
		vector:原生指针
		list：对原生指针(结点指针进行封装)
	6.迭代器失效：
		vector：任何涉及到可能增容的操作都会使迭代器失效
		list:只有在删除时会导致当前迭代器失效
	7.使用场景:
		vector:需要高效存储，支持随机访问，不关心插入删除效率
		list：大量的插入删除操作，不关心随机访问

*/

/*
结点：
	template<class T>
	struct _list_node{
		_list_node<T>* next;
		_list_node<T> prev;
		T data;
	};
//实现迭代器的前置++ --  后置++ -- 重载* ->
*/

/*
模拟实现的时候谨记：其底层为带头节点的双向循环链表 ，其底层私有成员变量就定义一个头节点即可
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

	//封装迭代器
	template<class T>
	class ListIterator{
		typedef struct Node<T> Node;
		typedef ListIterator<T> Self;
	public:
		Node* _node;
		//构造
		ListIterator(Node* node)
			:_node(node)
		{}
		//重载*
		T& operator*(){
			return _node->val;
		}
		//重载-> (方便自定义类型)
		T* operator->(){
			return &_node->val;
		}
		//重载前置++
		Self& operator++(){
			_node = _node->_next;
			return *this;
		}
		//后置++
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
		//构造函数
		list(){
			_head = new Node();
			_head->_pre = _head;
			_head->_next = _head;
		}
		//push_back 尾插  
		void push_back(const T& val){
			//先创建一个结点
			Node* newNode = new Node(val);

			_head->_pre->_next = newNode;
			newNode->_pre = _head->_pre;
			_head->_pre = newNode;     //头节点的前驱永远是最后一个结点的位置     
			newNode->_next = _head;    //最后一个结点的后继永远是头节点
		}
		iterator begin(){
			return iterator(_head->_next); //第一个有效位置
		}
		iterator end(){
			return iterator(_head); //最后一个有效位置的下一个位置就是头节点 （带头的循环双向链表）
		}
	private:
		Node* _head;//头
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