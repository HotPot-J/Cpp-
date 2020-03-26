#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<list>
#include<vector>
using namespace std;

/*
一、list的介绍：#include<list>
 1.list是可以在常数范围内在任意位置进行插入和删除的序列式容器，并且
该容器可以前后双向迭代。
 2.list的底层是双向链表结构，双向链表中每个元素在互不相关的独立节点
 中，在节点中通过指针指向其前一个元素和后一个元素。
 3.list与forward_list非常相似：最主要的不同在于forward_list是单链表，
 只能朝前迭代，已让其更简单高效。
 4.与其他序列式容器相比（arry，vector，deque），list通常在任意位置进
 行插入、移除元素的执行效率更好。
 5.与其他的序列容器相比，list和forward_list最大的缺陷是不支持任意位置
 的随机访问，比如：要访问list的第六个元素，必须从已知的位置（比如头尾）
 迭代到该位置，在这段位置上迭代需要线性的时间开销；list还需要一些额外
 的空间，以保存每个节点的相关联信息（对于存储类型较小的元素的list来说
 这可能是一个重要的因素）；
*/

//list的使用
/*
二、list的构造：
  list()   构造空的list
  list(size_type n,const value_type& val = value_type()) 构造的list中包含n个值为val的元素
  list(const list& x) 拷贝构造函数
  list(Inputlerator first，Inputlerator last) 用[first，last）区间中的元素构造list
*/

/*
三、list iterator的使用
 begin()+end()返回第一个元素的迭代器+返回最后一个元素下一个位置的迭代器
 rbegin+rend 返回第一个元素的reverse_iterator，即end位置，返回最后一个元素
 的reverse_iterator,即begin位置

 注意：begin与end为正向迭代器，对迭代器执行++操作，迭代器向后移动
 rbegin(end)与rend(begin)为反向迭代器，对迭代器执行++操作，迭代器向前移动

*/
void test1(){
	list<int> L1; //构造空的L1
	list<int> L2(4, 100); //L2中放四个值为100的元素
	list<int> L3(L2.begin(), L2.end()); //用L2的[begin(),end())左闭右开区间构造L3
	list<int> L4(L3); //用L3拷贝构造L4

	//以数组为迭代器区间构造L5 简单理解就是begin-end
	int arry[] = { 16, 2, 77, 29 };
	list<int> L5(arry, arry + sizeof(arry) / sizeof(int));

	//用迭代器打印L5中的元素
	list<int>::iterator it = L5.begin();
	while (it!=L5.end()){
		cout << *it << " ";
		++it;
	}
	cout << endl;
	//范围for遍历L5
	for (auto L : L5){
		cout << L << " ";
	}
	cout << endl;
}

/*
四、各种函数接口
 1.list capacity
  empty 检测list是否为空，是返回true，否则返回false
  size  返回list中有效节点的个数

 2.list element access（列表元素访问）
 front 返回list的第一个节点中值的引用
 back  返回list的最后一个节点中值的引用

 3.对list的各种增删操作
 push_front 头插
 pop_front 头删
 push_back 尾插
 pop_back 尾删
 insert 在某个位置进行插入操作
 erase 删除某个位置的元素
 swap 交换两个list中的元素
 clear 清空list中的有效元素
*/

//打印函数
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

	//在list头部插入0 尾部插入4
	L.push_front(0);
	L.push_back(4);
	PrintList(L); //0 1 2 3 4

	//删除头节点和尾节点
	L.pop_front();
	L.pop_back();
	PrintList(L);//1 2 3
}

//insert/erase
void TestList2(){
	int array[] = { 1, 2, 3 };
	list<int> L(array, array + sizeof(array) / sizeof(array[0]));

	//获取链表中的第二个节点
	auto pos = ++L.begin();
	cout << *pos << endl; //2

	//在pos前插入值为4的元素
	L.insert(pos, 4);
	PrintList(L);//1 4 2 3

	//在pos前插入3个值为3的元素
	L.insert(pos, 3, 3);
	PrintList(L);//1 4 3 3 3 2 3

	//在pos前插入一个[v.begin(),v.end())区间中的元素
	vector<int> v{ 7, 8, 9 };
	L.insert(pos, v.begin(), v.end());
	PrintList(L);//1 4 3 3 3 7 8 9 2 3

	//删除pos位置上的元素
	L.erase(pos);
	PrintList(L);//1 4 3 3 3 7 8 9 3

	//删除list[begin,end)区间中的元素，即删除L中所有元素
	L.erase(L.begin(), L.end());
	PrintList(L);
	//判断是否删除成功
	if (L.empty()){
		cout << "L为空" << endl;
	}
}

//size/swap/clear
void TestList3(){
	//用数组构造list
	int array[] = { 1, 2, 3 };
	list<int> L1(array, array + sizeof(array) / sizeof(array[0]));
	list<int> L2;
	PrintList(L1);
	if (L2.empty()){
		cout << "L2为空" << endl;
	}

	cout << "交换L1和L2中的元素:" << endl;
	//交换L1和L2中的元素
	L1.swap(L2);
	if (L1.empty()){
		cout << "L1为空" << endl;
	}
	PrintList(L2);

	//将L2中的元素清空
	L2.clear();
	cout << L2.size() << endl;
	
}

int main(){
	TestList3();
	return 0;
}

/*
list迭代器失效：
  迭代器失效即迭代器所指向的节点的无效，即该节点被删除了。由于list的
底层结构为带头节点的双向循环链表，因此在list中进行插入时是不会导致list
的迭代器失效的，只有在删除时才会失效，并且失效的只是指向被删除节点的迭代器，
其他迭代器不会受到影响。
*/

/*
list与vector的对比：
vector与list都是STL中非常重要的序列式容器，由于两个容器的底层结构不同，
导致其特性以及应用场景不同，其主要不同如下：


1.底层结构的不同：
             vector：动态顺序表，一段连续的空间
			 list：带头节点的双向循环链表

2.随机访问:  
             vector：支持随机访问，访问某个元素的效率O(1)
             list:不支持随机访问，访问某个元素效率O(n)

3.插入和删除：
             vector：任意位置插入和删除效率低，需要搬移元素，时间复杂度
			 为O(N),插入又是可能需要增容（开辟新的空间，拷贝元素，释放旧空间，导致效率更低）
			 list：任意位置插入和删除效率高，不需要搬移元素，时间复杂度为O(1)

4.空间利用率： 
             vector：底层为连续空间，不容易造成内存碎片，空间利用率高，缓存利用率高
             list：底层节点动态开辟，小结点容易造成内存碎片，空间利用率低，缓存利用率低

5.迭代器：   
             vector：原生态指针
			 list：对原生态指针(节点指针)进行封装

6.迭代器失效：
             vector：在插入元素时，要给所有的迭代器重新赋值，因为插入元素有可能会导致重新扩容，致使原来的迭代器失效
			 list： 插入元素不会导致迭代器失效，删除元素时只会导致当前迭代器失效，其他迭代器不受影响

7.使用场景：
             vector：需要高效存储，支持随机访问，不关心插入删除删除效率
			 list：大量插入和删除操作，不关心随机访问
*/