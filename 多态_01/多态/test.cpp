#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

/*
��̬

	һ�����ͨ�׽���̬��������̬�����彲��ȥ���ĳ����Ϊ������ͬ�Ķ���ȥ
	���ʱ���������ͬ��״̬

	������̬���ɵ�����
		����̬���ڲ�ͬ�̳й�ϵ�������ȥ����ͬһ�����������˲�ͬ����Ϊ������
	   student�̳�person��person��Ʊȫ�ۣ�student������Ʊ��ۣ�
	   1.����ͨ�������ָ��������õ����麯��
	   2.�����õĺ����������麯���������������Ի�����麯��������д
			�麯��:
		      ��virtual���ε����Ա������Ϊ�麯��
			�麯������д:
			  ����������һ����������ȫ��ͬ���麯��(���������麯��������麯���ķ���ֵ��
			  �͡��������֡������б���ȫ��ͬ)����������麯����д�˻�����麯��
		 ��:��person��������student��д����BuyTicket������
		class person{
			public:
			    virtual void BuyTicket(){
					printf("ȫ��Ʊ\n");
				}
		};
		class student:public person{
			public:
				virtual void BuyTicket(){
					printf("���Ʊ\n");
				}
		};
		
		//**����ͨ�������ָ��������õ����麯���ľ���ʵ��
			void Fun(person& a){
				a.BuyTicket();
			}

			int main(){
				person p;
				student s;
				p.Fun(p); //���ΪȫƱ
				s.Fun(s); //���Ϊ��Ʊ
				return 0;
			}
		//��ͬ�Ķ�����ɣ����ã�ͬһ����ΪЧ���ǲ�һ����


		�麯����д�����⣺
			Э�䣨�������������麯������ֵ���Ͳ�ͬ��
			��������д�����麯��ʱ������ຯ��ָ�뷵��ֵ���Ͳ�ͬ��������ֵ
			���ͱ���Ϊ����Ķ����ָ���������

			���ӣ�
		class person{
			public:
			    virtual person* BuyTicket(){
					printf("ȫ��Ʊ\n");
					return this;
				}
		};
		class student:public Person{
			public:
				virtual student* BuyTicket(){
					printf("���Ʊ\n");
					return this;
				}
		};
	
*/

//������������д���������������������������ֲ�ͬ��

//�����̬�� ���������������麯����д��������������
//class person{
//public:
//	 ~person(){
//		printf("ȫ��Ʊ\n");
//	}
//};
//class student :public person{
//public:
//		~student(){
//		printf("���Ʊ\n");
//	}
//};
//
//int main(){
//	person* p1 = new person();
//	person* p2 = new student();
//	delete p1;
//	delete p2;
//	return 0;
//	/*
//	ȫ��Ʊ   
//    ȫ��Ʊ����һ��student���� ȴ������person������������p1Ϊ����ָ�룬ָ��
//			�����࣬����������ᵼ���ڴ�й©��δ������������������
//      �밴���������. . .
//	*/
//}

//ʹ�ö�̬���ƣ���д��������ʲô�������ô�������������������  �����������+�������Լ���������

class person{
public:
	virtual ~person(){
		printf("ȫ��Ʊ\n");
	}
};
class student :public person{
public:
	virtual ~student(){
		printf("���Ʊ\n");
	}
};

int main(){
	person* p1 = new person();
	person* p2 = new student();
	delete p1;
	delete p2;
	return 0;
	/*
	ȫ��Ʊ
    ���Ʊ
    ȫ��Ʊ
�밴���������. . .
	*/
}