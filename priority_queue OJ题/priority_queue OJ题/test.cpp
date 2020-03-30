#define _CRT_SECURE_NO_WARNINGS 1
#include<queue>
#include <functional> 
#include<iostream>
using namespace std;

/*
215. �����еĵ�K�����Ԫ��
��δ������������ҵ��� k ������Ԫ�ء���ע�⣬����Ҫ�ҵ������������ĵ� k ������Ԫ�أ�
�����ǵ� k ����ͬ��Ԫ�ء�
ʾ�� 1:
����: [3,2,1,5,6,4] �� k = 2
���: 5
ʾ�� 2:
����: [3,2,3,1,2,4,5,5,6] �� k = 4
���: 4
*/
//˼·��������� ȡtopk
class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		//�����
		priority_queue<int> v(nums.begin(), nums.end());
		for (int i = 0; i < k-1; ++i){
			v.pop();
		}
		return v.top();
	}
};


int main(){
	vector<int> a{ 3, 2, 3, 1, 2, 4, 5, 5, 6 };
	Solution c;
	int t = c.findKthLargest(a, 4);
	return 0;
}