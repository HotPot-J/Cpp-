#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
#include<vector>
using namespace std;

/*
һ��stack�Ľ��ܣ�#include<stack>
   1.stack��һ��������������ר���ھ��к���ȳ������������Ļ����У���
ɾ��ֻ�ܴ�������һ�˽���Ԫ�صĲ�������ȡ������
   2.stack����Ϊ������������ʵ�ֵģ��������������Ƕ��ض������װ��Ϊ
��ײ�����������ṩһ���ض��ĳ�Ա������������Ԫ�أ����ض�����Ϊ���
��ģ�Ԫ���ض�������β��(��ջ��)��ѹ��͵�����
   3.stack�ĵײ������������κα�׼��������ģ�����һЩ�����ض�������
�࣬��Щ������Ӧ��֧�����²�����
  empty���п�
  back����ȡβ��Ԫ��
  push_back: β��
  pop_back��βɾ
4.��׼����vector��list��deque�����ϣ�Ĭ������£����ûΪstackָ����
���ײ�������Ĭ����deque
*/

/*
�����ӿڣ�
  stack() ����յ�ջ
  empty() ���stack�Ƿ�Ϊ��
  size() ����stack��Ԫ�صĸ���
  top() ����ջ��Ԫ�ص�����
  push() ��Ԫ��valѹ��stack��
  pop() ��stack��β��Ԫ�ص���
*/

//OJ��
/*
155. ��Сջ
���һ��֧�� push��pop��top �����������ڳ���ʱ���ڼ�������СԪ�ص�ջ��
push(x) -- ��Ԫ�� x ����ջ�С�
pop() -- ɾ��ջ����Ԫ�ء�
top() -- ��ȡջ��Ԫ�ء�
getMin() -- ����ջ�е���СԪ�ء�
ʾ��:
inStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> ���� -3.
minStack.pop();
minStack.top();      --> ���� 0.
minStack.getMin();   --> ���� -2.
*/
class MinStack {
public:
	void push(int x) {
		//��ѹջ
		_elem.push(x);
		//���ж� ��_minΪ�ջ���xС�ڵ�ǰ_minջ��Ԫ�� ����ջ
		if (_min.empty() || x < _min.top()){
			_min.push(x);
		}
	}

	void pop() {
		//���_minջ��Ԫ�ص���_elem����Ҫ��ջ��Ԫ�� ��ô_min�е�ջ����Ҫ����
		if (_min.top() == _elem.top()){
			_min.pop();
			_elem.pop();
		}
	}
	int top() {
		return _elem.top();
	}
	int getMin() {
		return _min.top();
	}
private:
	 //����ջ�е�Ԫ��
	stack<int> _elem;
	//����ջ����Сֵ
	stack<int> _min;
};

/*
��Ŀ����
���������������У���һ�����б�ʾջ��ѹ��˳�����жϵڶ��������Ƿ�
����Ϊ��ջ�ĵ���˳�򡣼���ѹ��ջ���������־�����ȡ�
��������1,2,3,4,5��ĳջ��ѹ��˳������4,5,3,2,1�Ǹ�ѹջ���ж�Ӧ��
һ���������У���4,3,5,1,2�Ͳ������Ǹ�ѹջ���еĵ������С�
��ע�⣺���������еĳ�������ȵģ�
*/
class Solution {
public:
	bool IsPopOrder(vector<int> pushV, vector<int> popV) {
		if (pushV.size() != popV.size()){
			return false;
		}
	   //ģ����ջ��ջ�Ĺ���
		int in = 0;//��ջԪ���±�
		int out = 0;//��ջԪ���±�
		stack<int> a; //ջ
		while (out < popV.size()){ 
			//��ջ
			while (a.empty() || a.top() != popV[out]){
				if (in < pushV.size()){
					a.push(pushV[in++]);
				}
				else{
					return false;//˵��ջ���� ��û��ջ����������
				}
			}
			//ջ��Ԫ�����ջ��Ԫ����ȣ���ջ
			a.pop();
			out++;
		}
		return true;
	}
};