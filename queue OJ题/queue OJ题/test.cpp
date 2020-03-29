#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
using namespace std;

/*
225. �ö���ʵ��ջ
ʹ�ö���ʵ��ջ�����в�����
push(x) -- Ԫ�� x ��ջ
pop() -- �Ƴ�ջ��Ԫ��
top() -- ��ȡջ��Ԫ��
empty() -- ����ջ�Ƿ�Ϊ��
ע��:
��ֻ��ʹ�ö��еĻ�������-- Ҳ���� push to back, peek/pop from front, size, �� is empty ��Щ�����ǺϷ��ġ�
����ʹ�õ�����Ҳ��֧�ֶ��С� �����ʹ�� list ���� deque��˫�˶��У���ģ��һ������ , ֻҪ�Ǳ�׼�Ķ��в������ɡ�
����Լ������в���������Ч�ģ�����, ��һ���յ�ջ������� pop ���� top ��������
*/
class MyStack {
public:
	/** Push element x onto stack. */
	void push(int x) {
		if (a.empty()){
			//���aΪ�վ���b
			b.push(x);
		}
		else{
			//������a
			a.push(x);
		}
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {
			int tmp = 0;
			if (a.empty()){
				//aΪ�վͽ�b�е�Ԫ�ص�n-1��Ԫ�طŽ�a�� ����n��Ԫ��pop
				int bSize = b.size() - 1;
				while (bSize--){
					a.push(b.front());
					b.pop();
				}
				 tmp = b.front();
				b.pop();
				return tmp;
					
			}
			else{
				//bΪ�վͽ�a�е�Ԫ�ص�n-1��Ԫ�طŽ�b�� ����n��Ԫ��pop
				int aSize = a.size() - 1;
				while (aSize--){
					b.push(a.front());
					a.pop();
				}
				 tmp = a.front();
				a.pop();
				return tmp;
			}
	}

	/** Get the top element. */
	int top() {
			if (a.empty()){
				return b.back();
			}
			else{
				return a.back();
			}
	}

	/** Returns whether the stack is empty. */
	bool empty() {
		if (a.empty() && b.empty()){
			return true;
		}
		else{
			return false;
		}
	}
private:
	queue<int> a;
	queue<int> b;
};
int main(){
	MyStack c;
	c.empty();
	c.push(1);
	c.push(2);
	int a = c.top();
	int b = c.pop();
	int d = c.pop();
	c.empty();
	return 0;
}
