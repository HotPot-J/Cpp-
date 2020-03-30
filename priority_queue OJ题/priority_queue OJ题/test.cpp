#define _CRT_SECURE_NO_WARNINGS 1
#include<queue>
#include <functional> 
#include<iostream>
using namespace std;

/*
215. 数组中的第K个最大元素
在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，
而不是第 k 个不同的元素。
示例 1:
输入: [3,2,1,5,6,4] 和 k = 2
输出: 5
示例 2:
输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4
*/
//思路：建立大堆 取topk
class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		//建大堆
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