#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
/*
一、智能指针主要是针对内存泄漏问题，利用对象生命周期来控制程序资源(如内存、
文件句柄，网络连接、互斥量等等)的简单技术（RALL 一种利用对象生命周期控制资源的
思想）。

在对象构造时获取资源，接着控制对资源的访问，使之在对象的生命周期内始终保持有效
，最后在对象析构的时候释放资源，借此，实际上我们是把一份资源责任托管给了一个
对象。这样做的好处:
	1.不需要显式的释放资源。
	2.采用这种方式，对象所需的资源在其生命周期内始终保持有效。
*/

/*
1、std::auto_ptr :管理权限转移思想 当对象赋值或者赋值后，前面的对象就被悬空
*/
namespace jxy{
	template<class T>
	class auto_ptr{
	public:
		auto_ptr(T* ptr = NULL)
			:_ptr(ptr)
		{}
		~auto_ptr(){
			if (_ptr){ delete _ptr; }
		}
		/*一旦发生拷贝，就将a的资源转移到b对象中，然后另a与其所管理的
		资源断开联系，这样就解决了一款空间被多次释放的问题
		*/
		auto_ptr(auto_ptr<T>&a)
			:_ptr(a._ptr)
		{
			a._ptr = NULL;
		}

		auto_ptr& operator=(auto_ptr<T>& a){
			//判断是否为自己赋值
			if (a._ptr != _ptr){
				//释放当前对象中的资源
				if (_ptr){ delete _ptr; }
				_ptr = a._ptr;
				a._ptr = NULL;
			}
			return *this;
		}
	  //让auto_ptr对象有原生指针的功能
		T& operator*(){ return *_ptr; }
		T* operator->(){ return _ptr; }
	private:
		T* _ptr;
	};
}

//int main(){
//	jxy::auto_ptr<int> a(new int);
//	/*
//	执行完上一行 ：//a{_ptr=0x012654e8 {-842150451} 
//			         b{_ptr=0xcccccccc {???} }	
//
//	*/
//	jxy::auto_ptr<int> b(a);
//	/*
//	再执行完上一行 ：a{_ptr=0xcccccccc {???} }
//			         b{_ptr=0x012654e8 {-842150451}
//	*/
//	//此时若给a赋值，则就是给*NULL赋值 发生错误
//	*a = 1;
//	return 0;
//}

/*
对auto_ptr总结:采用管理权限转移思想解决智能指针存在的多次析构问题，会导致
原来的指针失效，若在接下俩的代码里使用会引发bug。
*/

/*
2.std::unique_ptr ： 防拷贝 即不允许拷贝和赋值

在unique_ptr类内部将拷贝和赋值定义成如下：
 unique_ptr(unique_ptr<T> const &) = delete;
 unique_ptr& operator=(unique_ptr<T>const &) = delete;

 对unique_ptr总结：简单粗暴。。。 但是如果程序中有需要拷贝的场景，就无法使用
 该智能指针了。
*/

/*
3.std::shared_ptr ：是通过引用计数的方式来实现多个shared_ptr对象之间共享资源
  （1）shared_ptr在其内部，给每个资源都维护着一份计数，用来记录该份资源被
  几个资源共享。
  （2）在对象被销毁时(也就是析构函数调用)，说明自己不使用该资源了，对象的
  引用减一。
  （3）如果减一后引用技术器为0，则说明自己是最后一个使用该资源的对象，此时
  再释放该资源。
  （4）如果不是0，就说明除了自己还有其他对象在使用该份资源，不能释放该资源。

  **线程安全问题：
		但是如果多个执行流去进行技术器的加减操作 或者析构 会导致线程安全问题
  这里我们使用互斥锁来解决该问题。

  **循环引用问题：
		假设一个结构体：
			struct list{
				shared_ptr<list> perv;
				shared_ptr<list> rear;
			}
			shared_ptr<list> a(new list);
			shared_ptr<L=list> b(new list);
			a->rear = b;
			b->perv = a;
	这样一个代码，a管理着lista结构体 b中的perv管理者lista
				  b管理着listb结构体 a中的rear管理者listb
				当a生命周期到了，计数器-- 但是由于lista被b->perv管理着 lista无法释放
				  b声明周期到了，技术器-- 但是由于listb被a->rear管理着 listb无法释放
			这样就造成了循环引用的问题。
	*如何解决循环引用问题?
		c++库里实现了weak_ptr来解决该问题。（该指针内部实现赋值和拷贝构造
		时，直接传递的就是shared_ptr,所以即保证了析构安全，又解决了循环引用的问题）
				struct list{
				weak_ptr<list> perv;
				weak_ptr<list> rear;
			}
	//注意 weak_ptr的原理是，在该对象内取消了计数器，使得其参与管理另一个大
	结构体（lista/listb）管理时，不对技术器++，所以当lista/listb声明周期结束
	大家都可以各自释放各自的
	（weak_ptr该指针内部实现赋值和拷贝构造
	时，直接传递的就是shared_ptr,所以即保证了析构安全，又解决了循环引用的问题）

  *仿函数删除器，在一些new[]类型 melloc 或者一些操作句柄的关闭，需要针对这些情况
  自定义一个删除器 例子:
	1.针对new[]
	template<class T>
	struct DeleteArrayFunc{
		void operator()(T* ptr){
			delete[] ptr;
		}
	};
	2.针对malloc
	template<class T>
	struct FreeFunc{
		void operator()(void* ptr){
			free(ptr);
		}
	};
	3.针对文件
	struct Fclose{
		void operator()(FILE* pa){
			fclose(pa); 
		}
	}；
	定义shared_ptr指针传递参数时:
	shared_ptr<int> sp1(new A[4], DeleteFunc<T>());
	shared_ptr<int> sp2((int*)malloc(4), freeFunc());
	shared_ptr<int> sp3(fopen("test.txt","w"), Fclose());
 */

//模拟实现shared_ptr（非线程安全版 可以加互斥锁来拓展）

namespace Jxy{
	template<class T>
	class shared_ptr{
	public:
		shared_ptr(T* ptr=NULL)
			:_ptr(ptr),
			_pcount(new int(1))
		{}

		//拷贝构造
		shared_ptr(shared_ptr<T>& ptr){
				_pcount = ptr._pcount;
				++(*_pcount);
				_ptr = ptr._ptr;
		}

		//赋值
		shared_ptr<T>& operator=(shared_ptr<T>& ptr){
			if (ptr._ptr != _ptr){
					if (--*(_pcount) == 0){
						//如果本身_pcount正在管理一块空间 先把自己的事情做好再去
						//管理别人
						delete _ptr;
						delete _pcount;
					}
				_pcount = ptr._pcount;
				++(*_pcount);
				_ptr = ptr._ptr;
			}
			return *this;
		}
		~shared_ptr(){
			if (--(*_pcount) == 0 && _ptr){
				cout << "delete: " << _ptr << endl;
				delete _ptr;
				delete _pcount;
				_ptr = NULL;
			}
		}
		T operator*(){ return *_ptr; }
		T* operator->(){ return _ptr; }
	private:
		T* _ptr;
		//增加一个计数器 记录当前管理同一块资源的指针个数 
		int* _pcount;
	};
}

//int main(){
//	Jxy::shared_ptr<int> a(new int);
//	Jxy::shared_ptr<int>b(a);
//	Jxy::shared_ptr<int>c = b;
//
//	Jxy::shared_ptr<int>d(new int);
//	b = d; //本来管理a那块资源的b现在和d一起管理d所指向的资源
//
//	/* 结果正确 只申请了两次空间 也只析构了两次 
//	delete: 00DAC478
//	delete: 00DAC7A8
//	请按任意键继续. . .
//	*/
//	return 0;
//}

/*
内存泄漏相关知识点:
1.什么是内存泄漏？
分析:
内存泄漏一般是指我们申请了资源，在使用完毕后，忘记释放，或者因为执行流的改变
未正常释放。
 
如果我们申请了内存没有手动释放，如果最终进程正常结束，那么操作系统会释放这些
资源。但是如果是因为某些原因进程变为僵尸进程等，则会使资源无法被操作系自动
回收，则危害很大。 

但是在进程运行中，则会导致其他需要申请资源的地方，无法申请未主动释放，且使用
完毕的资源，也会拖节奏。 （即可用内存越来越少）

结论:
**所以长期运行，不能随便重启的程序（比如服务器程序），内存泄漏的危害巨大

2.如何解决内存泄漏相关问题？
	a.写c/c++代码时 小心谨慎
	b.复杂情况多使用智能指针进行管理（事前预防）
	c.如果怀疑存在内存泄漏，或者已经出现，可以使用内存泄露工具去检测（时候检查）

*/