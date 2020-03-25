#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;
/*
136. 只出现一次的数字
给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素
说明：
你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？
示例 1:
输入: [2,2,1]
输出: 1
示例 2:
输入: [4,1,2,1,2]
输出: 4
*/
//找不同 异或运算符即为找不同的 让数组中的数字都进行异或 最终剩下谁 即找到该元素
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		int ret = 0;
		for (auto x : nums){
			ret ^= x;
		}
		return ret;
	}
};

/*
118. 杨辉三角(训练了用vector怎样操作二维数组)
给定一个非负整数 numRows，生成杨辉三角的前 numRows 行。
在杨辉三角中，每个数是它左上方和右上方的数的和。
示例:
输入: 5
输出:
[
[1],
[1,1],
[1,2,1],
[1,3,3,1],
[1,4,6,4,1]
]
*/
class Solution1 {
public:
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> vv;//二维
		//开辟有效空间
		vv.resize(numRows);
		for (int i = 0; i < numRows; ++i){
			//开辟每一行为i个大小 并初始化
			vv[i].resize(i+1, 0);
			//每一行第一个和最后一个都为1
			vv[i][0] = 1;
			vv[i][i] = 1;
		}
		for (int i = 0; i < numRows; ++i){
			for (int j = 0; j < vv[i].size(); ++j){
				if (vv[i][j] == 0){
					vv[i][j] = vv[i - 1][j - 1] + vv[i - 1][j];
				}
			}
		}
		return vv;
	}
};

/*
26. 删除排序数组中的重复项
给定一个排序数组，你需要在 原地 删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。

不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
示例 1:
给定数组 nums = [1, 1, 2],
函数应该返回新的长度 2, 并且原数组 nums 的前两个元素被修改为 1, 2。
你不需要考虑数组中超出新长度后面的元素。
示例 2:
给定 nums = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4],
函数应该返回新的长度 5, 并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4。
你不需要考虑数组中超出新长度后面的元素。
*/
//思路：前后指针 (我的写法是使用了迭代器去解决 其实用下标操作也可以代码更简洁)
class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() < 1){
			return 0;
		}
		vector<int>::iterator top = nums.begin();
		vector<int>::iterator tail = top + 1;
		int ret = 1;
		while (tail != nums.end()){
			if (*top == *tail){
				tail++;
			}
			else{
				*(top + 1) = *tail;
				top++;
				ret++;
			}
		}
		return ret;
	}
};


/*
面试题39. 数组中出现次数超过一半的数字
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
你可以假设数组是非空的，并且给定的数组总是存在多数元素。
示例 1:
输入: [1, 2, 3, 2, 2, 2, 5, 4, 2]
输出: 2
限制：
1 <= 数组长度 <= 50000
*/
//思路：排序+遍历
/*
C++的algorithm头文件里包含了排序算法 sort(begin，end，cmp);
begin:起始地址 
end:结束地址的后一位地址 
cmp：默认升序 若需要降序则自己写一个cmp函数即可（和c语言写法一致）
*/
#include<algorithm>
class Solution1 {
public:
	int majorityElement(vector<int>& nums) {
		int flag = 0;
		sort(nums.begin(), nums.end());
		vector<int>::iterator top = nums.begin();
		while (top != nums.end()){
			flag++;
			top++;
			if (flag > (nums.size() / 2)){
				break;
			}
			if (top != nums.end()){
				if (*top != *(top - 1)){
					flag = 0;
				}
			}
		}
		return *(top - 1);
	}   
};

/*
给定一个整数数组 nums?，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
示例 :
输入 : [-2, 1, -3, 4, -1, 2, 1, -5, 4],
输出 : 6
解释 : 连续子数组?[4, -1, 2, 1] 的和最大，为?6。
来源：力扣（LeetCode）
链接：https ://leetcode-cn.com/problems/maximum-subarray
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
//思路：动态规划 nums[i]保存至当前下标i的位置最大的序列和 每次和之前的对比 看是否应该添加或者是自立为王
class Solution {
public:
	int max(int a, int b){
		return a > b ? a : b;
	}
	int maxSubArray(vector<int>& nums) {
		if (nums.size() == 1){
			return nums[0];
		}
		int max = nums[0];
		for (int i = 1; i < nums.size(); ++i){
			int a = nums[i] + nums[i - 1];
			int b = nums[i];
			nums[i] = a>b ? a : b;
			if (nums[i] > max){
				max = nums[i];
			}
		}
		return max;
	}
};

