#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
/*
һ������ָ����Ҫ������ڴ�й©���⣬���ö����������������Ƴ�����Դ(���ڴ桢
�ļ�������������ӡ��������ȵ�)�ļ򵥼�����RALL һ�����ö����������ڿ�����Դ��
˼�룩��

�ڶ�����ʱ��ȡ��Դ�����ſ��ƶ���Դ�ķ��ʣ�ʹ֮�ڶ��������������ʼ�ձ�����Ч
������ڶ���������ʱ���ͷ���Դ����ˣ�ʵ���������ǰ�һ����Դ�����йܸ���һ��
�����������ĺô�:
	1.����Ҫ��ʽ���ͷ���Դ��
	2.�������ַ�ʽ�������������Դ��������������ʼ�ձ�����Ч��
*/

/*
1��std::auto_ptr :����Ȩ��ת��˼�� ������ֵ���߸�ֵ��ǰ��Ķ���ͱ�����
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
		/*һ�������������ͽ�a����Դת�Ƶ�b�����У�Ȼ����a�����������
		��Դ�Ͽ���ϵ�������ͽ����һ��ռ䱻����ͷŵ�����
		*/
		auto_ptr(auto_ptr<T>&a)
			:_ptr(a._ptr)
		{
			a._ptr = NULL;
		}

		auto_ptr& operator=(auto_ptr<T>& a){
			//�ж��Ƿ�Ϊ�Լ���ֵ
			if (a._ptr != _ptr){
				//�ͷŵ�ǰ�����е���Դ
				if (_ptr){ delete _ptr; }
				_ptr = a._ptr;
				a._ptr = NULL;
			}
			return *this;
		}
	  //��auto_ptr������ԭ��ָ��Ĺ���
		T& operator*(){ return *_ptr; }
		T* operator->(){ return _ptr; }
	private:
		T* _ptr;
	};
}

//int main(){
//	jxy::auto_ptr<int> a(new int);
//	/*
//	ִ������һ�� ��//a{_ptr=0x012654e8 {-842150451} 
//			         b{_ptr=0xcccccccc {???} }	
//
//	*/
//	jxy::auto_ptr<int> b(a);
//	/*
//	��ִ������һ�� ��a{_ptr=0xcccccccc {???} }
//			         b{_ptr=0x012654e8 {-842150451}
//	*/
//	//��ʱ����a��ֵ������Ǹ�*NULL��ֵ ��������
//	*a = 1;
//	return 0;
//}

/*
��auto_ptr�ܽ�:���ù���Ȩ��ת��˼��������ָ����ڵĶ���������⣬�ᵼ��
ԭ����ָ��ʧЧ�����ڽ������Ĵ�����ʹ�û�����bug��
*/

/*
2.std::unique_ptr �� ������ �����������͸�ֵ

��unique_ptr���ڲ��������͸�ֵ��������£�
 unique_ptr(unique_ptr<T> const &) = delete;
 unique_ptr& operator=(unique_ptr<T>const &) = delete;

 ��unique_ptr�ܽ᣺�򵥴ֱ������� �����������������Ҫ�����ĳ��������޷�ʹ��
 ������ָ���ˡ�
*/

/*
3.std::shared_ptr ����ͨ�����ü����ķ�ʽ��ʵ�ֶ��shared_ptr����֮�乲����Դ
  ��1��shared_ptr�����ڲ�����ÿ����Դ��ά����һ�ݼ�����������¼�÷���Դ��
  ������Դ����
  ��2���ڶ�������ʱ(Ҳ����������������)��˵���Լ���ʹ�ø���Դ�ˣ������
  ���ü�һ��
  ��3�������һ�����ü�����Ϊ0����˵���Լ������һ��ʹ�ø���Դ�Ķ��󣬴�ʱ
  ���ͷŸ���Դ��
  ��4���������0����˵�������Լ���������������ʹ�ø÷���Դ�������ͷŸ���Դ��

  **�̰߳�ȫ���⣺
		����������ִ����ȥ���м������ļӼ����� �������� �ᵼ���̰߳�ȫ����
  ��������ʹ�û���������������⡣

  **ѭ���������⣺
		����һ���ṹ�壺
			struct list{
				shared_ptr<list> perv;
				shared_ptr<list> rear;
			}
			shared_ptr<list> a(new list);
			shared_ptr<L=list> b(new list);
			a->rear = b;
			b->perv = a;
	����һ�����룬a������lista�ṹ�� b�е�perv������lista
				  b������listb�ṹ�� a�е�rear������listb
				��a�������ڵ��ˣ�������-- ��������lista��b->perv������ lista�޷��ͷ�
				  b�������ڵ��ˣ�������-- ��������listb��a->rear������ listb�޷��ͷ�
			�����������ѭ�����õ����⡣
	*��ν��ѭ����������?
		c++����ʵ����weak_ptr����������⡣����ָ���ڲ�ʵ�ָ�ֵ�Ϳ�������
		ʱ��ֱ�Ӵ��ݵľ���shared_ptr,���Լ���֤��������ȫ���ֽ����ѭ�����õ����⣩
				struct list{
				weak_ptr<list> perv;
				weak_ptr<list> rear;
			}
	//ע�� weak_ptr��ԭ���ǣ��ڸö�����ȡ���˼�������ʹ������������һ����
	�ṹ�壨lista/listb������ʱ�����Լ�����++�����Ե�lista/listb�������ڽ���
	��Ҷ����Ը����ͷŸ��Ե�
	��weak_ptr��ָ���ڲ�ʵ�ָ�ֵ�Ϳ�������
	ʱ��ֱ�Ӵ��ݵľ���shared_ptr,���Լ���֤��������ȫ���ֽ����ѭ�����õ����⣩

  *�º���ɾ��������һЩnew[]���� melloc ����һЩ��������Ĺرգ���Ҫ�����Щ���
  �Զ���һ��ɾ���� ����:
	1.���new[]
	template<class T>
	struct DeleteArrayFunc{
		void operator()(T* ptr){
			delete[] ptr;
		}
	};
	2.���malloc
	template<class T>
	struct FreeFunc{
		void operator()(void* ptr){
			free(ptr);
		}
	};
	3.����ļ�
	struct Fclose{
		void operator()(FILE* pa){
			fclose(pa); 
		}
	}��
	����shared_ptrָ�봫�ݲ���ʱ:
	shared_ptr<int> sp1(new A[4], DeleteFunc<T>());
	shared_ptr<int> sp2((int*)malloc(4), freeFunc());
	shared_ptr<int> sp3(fopen("test.txt","w"), Fclose());
 */

//ģ��ʵ��shared_ptr�����̰߳�ȫ�� ���Լӻ���������չ��

namespace Jxy{
	template<class T>
	class shared_ptr{
	public:
		shared_ptr(T* ptr=NULL)
			:_ptr(ptr),
			_pcount(new int(1))
		{}

		//��������
		shared_ptr(shared_ptr<T>& ptr){
				_pcount = ptr._pcount;
				++(*_pcount);
				_ptr = ptr._ptr;
		}

		//��ֵ
		shared_ptr<T>& operator=(shared_ptr<T>& ptr){
			if (ptr._ptr != _ptr){
					if (--*(_pcount) == 0){
						//�������_pcount���ڹ���һ��ռ� �Ȱ��Լ�������������ȥ
						//�������
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
		//����һ�������� ��¼��ǰ����ͬһ����Դ��ָ����� 
		int* _pcount;
	};
}

//int main(){
//	Jxy::shared_ptr<int> a(new int);
//	Jxy::shared_ptr<int>b(a);
//	Jxy::shared_ptr<int>c = b;
//
//	Jxy::shared_ptr<int>d(new int);
//	b = d; //��������a�ǿ���Դ��b���ں�dһ�����d��ָ�����Դ
//
//	/* �����ȷ ֻ���������οռ� Ҳֻ���������� 
//	delete: 00DAC478
//	delete: 00DAC7A8
//	�밴���������. . .
//	*/
//	return 0;
//}

/*
�ڴ�й©���֪ʶ��:
1.ʲô���ڴ�й©��
����:
�ڴ�й©һ����ָ������������Դ����ʹ����Ϻ������ͷţ�������Ϊִ�����ĸı�
δ�����ͷš�
 
��������������ڴ�û���ֶ��ͷţ�������ս���������������ô����ϵͳ���ͷ���Щ
��Դ�������������ΪĳЩԭ����̱�Ϊ��ʬ���̵ȣ����ʹ��Դ�޷�������ϵ�Զ�
���գ���Σ���ܴ� 

�����ڽ��������У���ᵼ��������Ҫ������Դ�ĵط����޷�����δ�����ͷţ���ʹ��
��ϵ���Դ��Ҳ���Ͻ��ࡣ ���������ڴ�Խ��Խ�٣�

����:
**���Գ������У�������������ĳ��򣨱�����������򣩣��ڴ�й©��Σ���޴�

2.��ν���ڴ�й©������⣿
	a.дc/c++����ʱ С�Ľ���
	b.���������ʹ������ָ����й�����ǰԤ����
	c.������ɴ����ڴ�й©�������Ѿ����֣�����ʹ���ڴ�й¶����ȥ��⣨ʱ���飩

*/