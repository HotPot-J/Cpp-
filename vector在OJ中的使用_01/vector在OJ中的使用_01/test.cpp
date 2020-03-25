#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;
/*
136. ֻ����һ�ε�����
����һ���ǿ��������飬����ĳ��Ԫ��ֻ����һ�����⣬����ÿ��Ԫ�ؾ��������Ρ��ҳ��Ǹ�ֻ������һ�ε�Ԫ��
˵����
����㷨Ӧ�þ�������ʱ�临�Ӷȡ� ����Բ�ʹ�ö���ռ���ʵ����
ʾ�� 1:
����: [2,2,1]
���: 1
ʾ�� 2:
����: [4,1,2,1,2]
���: 4
*/
//�Ҳ�ͬ ����������Ϊ�Ҳ�ͬ�� �������е����ֶ�������� ����ʣ��˭ ���ҵ���Ԫ��
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
118. �������(ѵ������vector����������ά����)
����һ���Ǹ����� numRows������������ǵ�ǰ numRows �С�
����������У�ÿ�����������Ϸ������Ϸ������ĺ͡�
ʾ��:
����: 5
���:
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
		vector<vector<int>> vv;//��ά
		//������Ч�ռ�
		vv.resize(numRows);
		for (int i = 0; i < numRows; ++i){
			//����ÿһ��Ϊi����С ����ʼ��
			vv[i].resize(i+1, 0);
			//ÿһ�е�һ�������һ����Ϊ1
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
26. ɾ�����������е��ظ���
����һ���������飬����Ҫ�� ԭ�� ɾ���ظ����ֵ�Ԫ�أ�ʹ��ÿ��Ԫ��ֻ����һ�Σ������Ƴ���������³��ȡ�

��Ҫʹ�ö��������ռ䣬������� ԭ�� �޸��������� ����ʹ�� O(1) ����ռ����������ɡ�
ʾ�� 1:
�������� nums = [1, 1, 2],
����Ӧ�÷����µĳ��� 2, ����ԭ���� nums ��ǰ����Ԫ�ر��޸�Ϊ 1, 2��
�㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�
ʾ�� 2:
���� nums = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4],
����Ӧ�÷����µĳ��� 5, ����ԭ���� nums ��ǰ���Ԫ�ر��޸�Ϊ 0, 1, 2, 3, 4��
�㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�
*/
//˼·��ǰ��ָ�� (�ҵ�д����ʹ���˵�����ȥ��� ��ʵ���±����Ҳ���Դ�������)
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
������39. �����г��ִ�������һ�������
��������һ�����ֳ��ֵĴ����������鳤�ȵ�һ�룬���ҳ�������֡�
����Լ��������Ƿǿյģ����Ҹ������������Ǵ��ڶ���Ԫ�ء�
ʾ�� 1:
����: [1, 2, 3, 2, 2, 2, 5, 4, 2]
���: 2
���ƣ�
1 <= ���鳤�� <= 50000
*/
//˼·������+����
/*
C++��algorithmͷ�ļ�������������㷨 sort(begin��end��cmp);
begin:��ʼ��ַ 
end:������ַ�ĺ�һλ��ַ 
cmp��Ĭ������ ����Ҫ�������Լ�дһ��cmp�������ɣ���c����д��һ�£�
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
����һ���������� nums?���ҵ�һ���������͵����������飨���������ٰ���һ��Ԫ�أ������������͡�
ʾ�� :
���� : [-2, 1, -3, 4, -1, 2, 1, -5, 4],
��� : 6
���� : ����������?[4, -1, 2, 1] �ĺ����Ϊ?6��
��Դ�����ۣ�LeetCode��
���ӣ�https ://leetcode-cn.com/problems/maximum-subarray
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������
*/
//˼·����̬�滮 nums[i]��������ǰ�±�i��λ���������к� ÿ�κ�֮ǰ�ĶԱ� ���Ƿ�Ӧ����ӻ���������Ϊ��
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

