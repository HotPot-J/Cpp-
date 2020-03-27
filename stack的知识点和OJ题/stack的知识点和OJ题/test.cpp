#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<stack>
#include<vector>
using namespace std;

/*
一、stack的介绍：#include<stack>
   1.stack是一种容器适配器，专门在具有后进先出操作的上下文环境中，其
删除只能从容器的一端进行元素的插入与提取操作。
   2.stack是作为容器适配器被实现的，容器适配器即是对特定的类封装作为
其底层的容器，并提供一组特定的成员函数来访问其元素，将特定类作为其底
层的，元素特定容器的尾部(即栈顶)被压入和弹出。
   3.stack的底层容器可以是任何标准的容器类模板或者一些其他特定的容器
类，这些容器类应该支持以下操作：
  empty：判空
  back：获取尾部元素
  push_back: 尾插
  pop_back：尾删
4.标准容器vector、list、deque均符合，默认情况下，如果没为stack指定特
定底层容器，默认用deque
*/

/*
二、接口：
  stack() 构造空的栈
  empty() 检测stack是否为空
  size() 返回stack中元素的个数
  top() 返回栈顶元素的引用
  push() 将元素val压入stack中
  pop() 将stack中尾部元素弹出
*/

//OJ题
/*
155. 最小栈
设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。
push(x) -- 将元素 x 推入栈中。
pop() -- 删除栈顶的元素。
top() -- 获取栈顶元素。
getMin() -- 检索栈中的最小元素。
示例:
inStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.
*/
class MinStack {
public:
	void push(int x) {
		//先压栈
		_elem.push(x);
		//再判断 当_min为空或者x小于当前_min栈顶元素 则入栈
		if (_min.empty() || x < _min.top()){
			_min.push(x);
		}
	}

	void pop() {
		//如果_min栈顶元素等于_elem中需要出栈的元素 那么_min中的栈顶需要弹出
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
	 //保存栈中的元素
	stack<int> _elem;
	//保存栈的最小值
	stack<int> _min;
};

/*
题目描述
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否
可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。
例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的
一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
（注意：这两个序列的长度是相等的）
*/
class Solution {
public:
	bool IsPopOrder(vector<int> pushV, vector<int> popV) {
		if (pushV.size() != popV.size()){
			return false;
		}
	   //模拟入栈出栈的过程
		int in = 0;//入栈元素下标
		int out = 0;//出栈元素下标
		stack<int> a; //栈
		while (out < popV.size()){ 
			//入栈
			while (a.empty() || a.top() != popV[out]){
				if (in < pushV.size()){
					a.push(pushV[in++]);
				}
				else{
					return false;//说明栈满了 还没出栈不符合条件
				}
			}
			//栈顶元素与出栈的元素相等，出栈
			a.pop();
			out++;
		}
		return true;
	}
};