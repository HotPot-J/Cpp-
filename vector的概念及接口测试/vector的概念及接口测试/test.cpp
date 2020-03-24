#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;
/*
一、vector的基本介绍:
vector:#include<vector>
  1.vector是表示可变大小数组的序列容器
  2.就像数组一样，vector也采用的连续存储空间来存储元素。也就是意味着
  可以采用下标对vector的元素进行访问，和数组一样高效。但是又不像数组
  它的大小是可以动态改变的，而且他的大小会被容器自动处理
  3.本质讲，vector使用动态分配数组来存储它的元素。当新元素插入的时候
  这个数组需要被重新分配大小。为了增加存储空间，其做法是分配一个新的
  数组，然后将全部元素移到这个数组，就是时间而言，这是一个相对代价高
  的任务。所以vector并不会每次都重新分配大小。
  4.vector分配空间策略：vector会分配一些额外的空间以适应可能的增长，
  因为存储空间比实际需要的存储空间更大。不同的库采用不同的策略权衡空
  间的使用和重新分配。但无论如何，重新分配都应该是对数增长的间隔的大
  小，以至于在末尾插入一个元素的时候是在常数时间的复杂度完成的。
  5.因此，vector占用了更多的存储空间，为了获得管理存储空间的能力，并
  且以一种有效的方式动态增长。
  6.与其它动态序列容器相比，vector在访问元素的时候更加高效，在末尾增
  删元素相对高效。对于其它不在末尾的删除和插入操作，效率更低。
*/
/*
二、vector的定义：
  vector()   无参构造
  vector(size_type n,const value_type& val = value_type()) 构造并初始化n个val
  vector(const vector& x)   拷贝构造
  vector(Inputlterator first,Inputlterator last) 使用迭代器进行初始化构造
*/ 
void test1(){
	vector<int> first; //int类型的空vector
	vector<int> second(4, 100);//构造一个空间为4的int类型的vector，并初始化这四个为100
	vector<int> third(second.begin(), second.end());//使用迭代器进行初始化
	vector<int> fourth(third);//拷贝构造
}

/*
三、vector iterator的使用 （vector迭代器）：
  begin+end   获取第一个数据位置的iterator_iterator，获取最后一个数据的下一个位置iterator_iterator/const_iterator

    1 2 3 4 5 6 7 8 9 10
	|                    |
	begin()              end()
*/

void PrintVector(const vector<int>& v){
	//const对象使用const迭代器进行遍历打印
	vector<int>::const_iterator it = v.begin();
	while (it != v.end()){
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

//int main(){
//	vector<int> v(4,100);
//	//使用迭代器进行打印
//	PrintVector(v);
//
//	//使用迭代器进行修改
//	vector<int>::iterator it = v.begin();
//	while (it != v.end()){
//		*it = 2;
//		++it;
//	}
//	PrintVector(v);
//	return 0;
//}

/*
四、vector 空间增长问题

size 获取数据个数
capacity 获取容量大小
empty 判空
resize 改变vector的size
reserve 改变vector的容量
注意：vs下capacity是按照1.5倍增长的，g++是按照两倍增长的
reserve只负责开辟空间，如果确定知道需要荣多少空间，reserve可以缓解vector增容的代价缺陷问题
resize在开空间的同时还会进行初始化
*/

void test2(){
	size_t sz;
	vector<int> f;
	sz = f.capacity();
	cout << "f的初始容量为："<<sz << endl;
	cout << "使f增长：" << endl;
	for (int i = 0; i < 100; ++i){
		f.push_back(i);
		if (sz != f.capacity()){
			sz = f.capacity();
			cout << "f的capacity已经被改变为：" << sz << endl;
		}
	}
}
/*
vs下运行结果：
f的初始容量为：0
使f增长：
f的capacity已经被改变为：1
f的capacity已经被改变为：2
f的capacity已经被改变为：3
f的capacity已经被改变为：4
f的capacity已经被改变为：6
f的capacity已经被改变为：9
f的capacity已经被改变为：13
f的capacity已经被改变为：19
f的capacity已经被改变为：28
f的capacity已经被改变为：42
f的capacity已经被改变为：63
f的capacity已经被改变为：94
f的capacity已经被改变为：141  vs下运行的确为1.5倍增长
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
	bar.reserve(100); // 这是与foo不同的地方
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
运行结果：
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
making bar grow:        //我们发现使用reserve设定的空间大小 capacity自动增加不会超过设定大小
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
	myvector.resize(5); //使有效长度为5
	myvector.resize(8, 100);//使有效长度为8 多出的部分用100补齐
	myvector.resize(12); //使有效长度为12 多出的会自动以0补齐
	std::cout << "myvector contains:";
	for (int i = 0; i<myvector.size(); i++)
		std::cout << ' ' << myvector[i];
	cout <<endl;
}
/*
运行结果：
myvector contains: 1 2 3 4 5 100 100 100 0 0 0 0
请按任意键继续. . .
*/

/*
5、vector增删查改
push_back  尾插
pop_back 尾删除
find 查找（这使算法模块的实现，不是vector的成员接口）使用find找到的pos在使用一次后就失效了 下次在使用得重新找（详情见5.vector迭代器失效问题）
insert 在position之前插入val
erase 删除position位置的数据
swap 交换两个vector的数据空间
operator[] 像数组一样访问
*/
//push_back/pop_back
void test5(){
	int a[] = { 1, 2, 3, 4, 5 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));//类似于使用迭代器进行初始化

	vector<int>::iterator it = v.begin();
	while (it != v.end()){
		cout << *it << " ";
		++it;
	}
	cout << endl;
	v.pop_back();//尾删
	it = v.begin();
	while (it != v.end()){
		cout << *it << " ";
		++it;
	}
}

//find/insert/erase/swap
//operator[]+index 和for+auto两种遍历方式
void test6(){
	int a[] = { 1, 2, 3, 4, 5 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));

	//使用find查找3所在位置的iterator
	vector<int>::iterator pos = find(v.begin(), v.end(), 3);

	//在pos位置之前插入6
	v.insert(pos, 6);

    //operator[]+index 遍历
	for (int i = 0; i < v.size(); ++i){
		cout << v[i] << " ";
	}
	cout << endl;

   //删除pos位置的数字
	cout << "删除pos位置的数字:" << endl;
	pos = find(v.begin(), v.end(), 3);//重新找pos 之前pos的值使用过一次后变成随机值了，
	 //该迭代器失效了，即底层所指向的空间在使用一次会被自动释放
	v.erase(pos);

   //for+auto方式遍历
	for (auto x : v){
		cout << x << " ";
	}
	cout << endl;
	//使用swap 交换v和swapv的数据空间
	cout << "使用swap 交换v和swapv的数据空间:"<<endl;
	vector<int> swapv;
	swapv.swap(v);

	cout << "交换后的v：" << endl; //结果无打印输出
	for (auto x : v){
		cout << x << " ";
	}
	cout << endl;
	cout << "交换后的swapv：" << endl;//输出之前v的数值 说明交换成功
	for (auto x : swapv){
		cout << x << " ";
	}
	cout << endl;
}
/*
6、vector迭代器失效问题：
迭代器的主要作用就是让算法能够不用关心底层数据结构，其实底层就是一个指针，
或者说是对指针进行了封装，比如：vector的迭代器就是原声态指针T*。因此
迭代器失效，实际上就是迭代器底层对应指针所指向的空间被销毁了，而使用
一块已经被释放的空间，造成的后果是程序崩溃（即如果使用已经失效的迭代器，
程序可能会崩溃。）
*/
int main(){
	test6();
	return 0;
}
