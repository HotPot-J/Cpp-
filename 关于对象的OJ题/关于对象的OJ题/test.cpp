#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;

/*
��Ŀ����
��1+2+3+...+n��Ҫ����ʹ�ó˳�����for��while��if��else��switch��case�ȹؼ��ּ������ж���䣨A?B:C����
*/

//�ⷨһ��
//˼· �Զ���һ����A  ʹ��������̬����a��b  ��ʼ��a = 1 b = 0 ��A�Ĺ��캯����ʵ�� b+=a; ++a;  
//��ʱֻ��Ҫd����n��A����� ����ʵ��1-n����ӽ��

class assist{
public:
	assist() { N++; sum += N; }
	static void reset(){ 
		N = 0; sum = 0;
	}//��set����ÿ�ζ���N��sum�޸�Ϊ0 �� 0 ��ֹ����
	static unsigned int GetSum(){ return sum; }
private:
	static int N;
	static int sum;
};
int assist::N = 0;
int assist::sum = 0;
//����һ����̬����N��sum���ڹ��캯���н����ۼ����㣻
//Ȼ����һ���Ը�����Ϊ���͡���СΪn�����飬�ظ����ô˹��캯��n����ʵ��n�ε��ۼ�����
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

//�ⷨ���� �ݹ�

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