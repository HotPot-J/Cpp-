#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
using namespace std;

/*
225. 用队列实现栈
使用队列实现栈的下列操作：
push(x) -- 元素 x 入栈
pop() -- 移除栈顶元素
top() -- 获取栈顶元素
empty() -- 返回栈是否为空
注意:
你只能使用队列的基本操作-- 也就是 push to back, peek/pop from front, size, 和 is empty 这些操作是合法的。
你所使用的语言也许不支持队列。 你可以使用 list 或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。
你可以假设所有操作都是有效的（例如, 对一个空的栈不会调用 pop 或者 top 操作）。
*/
class MyStack {
public:
	/** Push element x onto stack. */
	void push(int x) {
		if (a.empty()){
			//如果a为空就入b
			b.push(x);
		}
		else{
			//否则入a
			a.push(x);
		}
	}

	/** Removes the element on top of the stack and returns that element. */
	int pop() {
			int tmp = 0;
			if (a.empty()){
				//a为空就将b中的元素的n-1个元素放进a中 将第n个元素pop
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
				//b为空就将a中的元素的n-1个元素放进b中 将第n个元素pop
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
