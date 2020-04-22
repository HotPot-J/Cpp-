#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

/*
题目描述
求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。
*/

//解法一：
//思路 自定义一个类A  使用两个静态变量a，b  初始化a = 1 b = 0 在A的构造函数中实现 b+=a; ++a;  
//此时只需要d创建n个A类对象 即可实现1-n的相加结果

class assist{
public:
	assist() { N++; sum += N; }
	static void reset(){ 
		N = 0; sum = 0;
	}//用set方法每次都将N，sum修改为0 和 0 防止出错
	static unsigned int GetSum(){ return sum; }
private:
	static int N;
	static int sum;
};
int assist::N = 0;
int assist::sum = 0;
//设置一个静态变量N和sum，在构造函数中进行累加运算；
//然后构造一个以辅助类为类型、大小为n的数组，重复调用此构造函数n次来实现n次的累加运算
class Solution {
public:
	int Sum_Solution(int n) {
		assist::reset();
		assist * p = new assist[n];
		delete[]p;
		p = nullptr;
		return assist::GetSum();
	}
};

//解法二： 递归

class Solution {
public:
	int Sum_Solution(int n) {
		if (n == 1){
			return 1;
		}
		return Sum_Solution(n - 1) + n;
	}
};
int main(){
	Solution t;
	t.Sum_Solution(5);
	return 0;
}