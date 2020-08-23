#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<mutex>
using namespace std;
/*
智能指针是一种采用RAII思想，借助一个对象的生命周期去实现的。由于一个对象的生命周期结束，会自动调用其析构函数，
那么在指针中应用这样的思想，防止由于执行流跳跃或者遗忘进行内存释放，造成资源泄露，所以智能指针应运而生，其中
较为完善的是share_ptr
同理，在多线程中，可能会有多个执行流同时访问临界资源的情况，造成线程安全问题，但是加锁后如果忘记解锁，或者由于
执行流的跳跃（抛异常可能会造成该情况），从而造成死锁的问题，所以，互斥锁也采用RAII的思想，设计了unique_mutex
，unique_mutex构造出来的对象，可以调用lock对其加锁，unlock对其解锁（即使没调用解锁，也会在生命周期结束时自动
调用其析构函数解锁），更加的灵活。
*/

//采用RAII思想设计一个简易的share_ptr
//具体的思路细节在对应代码行的注释中体现
namespace jxy{
	template<class T>
	class share_ptr{
		typedef share_ptr<T> Self;
	public:
		//构造函数
		share_ptr(T* ptr)
			:_ptr(ptr),
			_count(new int(1)),
			_mutex(new mutex)
		{}
		//拷贝构造
		share_ptr(Self& sp){
			_mutex = sp._mutex;
			_ptr = sp._ptr;
			_count = sp._count;//让计数器指向同一块地址
			unique_lock<mutex> ul(*_mutex);
			++(*_count);//计数器++
		}
		//赋值重载
		Self& operator=(const Self& sp){
			if (this != &sp){
				//自己给自己赋值没意义
				if (_ptr!=nullptr && --(*_count)==0){
					//万一自己也在管理着一块内存 如果恰好自己还是最后一个管理的 那就释放了
					delete _ptr;
					delete _count;
				}
				_mutex = sp._mutex;
				_ptr = sp._ptr;
				_count = sp._count;//让计数器指向同一块地址
				unique_lock<mutex> ul(*_mutex);
				++(*_count);//计数器++
			}
			return *this;
		}
	 //析构函数
		~share_ptr(){
			unique_lock<mutex> ul(*_mutex);
			if (_ptr!=nullptr && --(*_count) == 0){
				cout << _ptr << endl;
				delete _ptr;
				delete _count;
				_ptr = nullptr;
			}
		}
		//重载*
		T& operator*(){
			return *_ptr;
		}
		//重载->
		T* operator->(){
			return _ptr;
		}
	private:
		T* _ptr; //指针
		int* _count; //计数器，记录当前有多少个share_ptr对象在管理_ptr指向的内存 
		mutex* _mutex; //互斥锁 之所以需要该互斥锁，是由于计数器是在堆上开辟的临界资源，如果在多线程中
					  //多个执行流同时管理_ptr所指向的内存，势必需要对_count进行++ -- ，造成线程安全问题
 /*之所以计数器、互斥所都使用指针，就是为了在不同对象中对其进行计数时、加锁时是同步的*/
	};
}

int main(){
	jxy::share_ptr<int> a(new int);
	jxy::share_ptr<int> b = a;
	jxy::share_ptr<int> c = b;
	jxy::share_ptr<int> d(new int);
	c = d;
	return 0;
}