#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<mutex>
using namespace std;
/*
����ָ����һ�ֲ���RAII˼�룬����һ���������������ȥʵ�ֵġ�����һ��������������ڽ��������Զ�����������������
��ô��ָ����Ӧ��������˼�룬��ֹ����ִ������Ծ�������������ڴ��ͷţ������Դй¶����������ָ��Ӧ�˶���������
��Ϊ���Ƶ���share_ptr
ͬ���ڶ��߳��У����ܻ��ж��ִ����ͬʱ�����ٽ���Դ�����������̰߳�ȫ���⣬���Ǽ�����������ǽ�������������
ִ��������Ծ�����쳣���ܻ���ɸ���������Ӷ�������������⣬���ԣ�������Ҳ����RAII��˼�룬�����unique_mutex
��unique_mutex��������Ķ��󣬿��Ե���lock���������unlock�����������ʹû���ý�����Ҳ�����������ڽ���ʱ�Զ�
�������������������������ӵ���
*/

//����RAII˼�����һ�����׵�share_ptr
//�����˼·ϸ���ڶ�Ӧ�����е�ע��������
namespace jxy{
	template<class T>
	class share_ptr{
		typedef share_ptr<T> Self;
	public:
		//���캯��
		share_ptr(T* ptr)
			:_ptr(ptr),
			_count(new int(1)),
			_mutex(new mutex)
		{}
		//��������
		share_ptr(Self& sp){
			_mutex = sp._mutex;
			_ptr = sp._ptr;
			_count = sp._count;//�ü�����ָ��ͬһ���ַ
			unique_lock<mutex> ul(*_mutex);
			++(*_count);//������++
		}
		//��ֵ����
		Self& operator=(const Self& sp){
			if (this != &sp){
				//�Լ����Լ���ֵû����
				if (_ptr!=nullptr && --(*_count)==0){
					//��һ�Լ�Ҳ�ڹ�����һ���ڴ� ���ǡ���Լ��������һ������� �Ǿ��ͷ���
					delete _ptr;
					delete _count;
				}
				_mutex = sp._mutex;
				_ptr = sp._ptr;
				_count = sp._count;//�ü�����ָ��ͬһ���ַ
				unique_lock<mutex> ul(*_mutex);
				++(*_count);//������++
			}
			return *this;
		}
	 //��������
		~share_ptr(){
			unique_lock<mutex> ul(*_mutex);
			if (_ptr!=nullptr && --(*_count) == 0){
				cout << _ptr << endl;
				delete _ptr;
				delete _count;
				_ptr = nullptr;
			}
		}
		//����*
		T& operator*(){
			return *_ptr;
		}
		//����->
		T* operator->(){
			return _ptr;
		}
	private:
		T* _ptr; //ָ��
		int* _count; //����������¼��ǰ�ж��ٸ�share_ptr�����ڹ���_ptrָ����ڴ� 
		mutex* _mutex; //������ ֮������Ҫ�û������������ڼ��������ڶ��Ͽ��ٵ��ٽ���Դ������ڶ��߳���
					  //���ִ����ͬʱ����_ptr��ָ����ڴ棬�Ʊ���Ҫ��_count����++ -- ������̰߳�ȫ����
 /*֮���Լ���������������ʹ��ָ�룬����Ϊ���ڲ�ͬ�����ж�����м���ʱ������ʱ��ͬ����*/
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