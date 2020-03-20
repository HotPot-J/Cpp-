#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include <algorithm>
using namespace std;

/*
415. 字符串相加
给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和。
注意：
num1 和num2 的长度都小于 5100.
num1 和num2 都只包含数字 0-9.
num1 和num2 都不包含任何前导零。
你不能使用任何內建 BigInteger 库， 也不能直接将输入的字符串转换为整数形式。
*/
//思路： 设置进制位  从同时从两个字符串末尾往前遍历  
//1.可以将结果直接追加在addret中 用reverse函数将其翻转得到结果
//2.也可以每次都使用insert函数头插进addret中直接生成结果 但是该方法对于长字符串来说时间复杂度有点高                 
class Solution {
public:
	string addStrings(string num1, string num2) {
		int flag = 0;//初始化进制位为0
		int ret = 0;
		string addret;
		int i = num1.size() - 1, j = num2.size() - 1;
		int size1 = i + 1, size2 = j + 1;
		while (size1&&size2){
			ret = (((num1[i] - '0') + (num2[j] - '0') + flag) % 10);
			addret += (ret + '0');
			//addret.insert(addret.begin(), ret+'0');//头插进去 就不用翻转了
			flag = (((num1[i--] - '0') + (num2[j--] - '0') + flag) / 10);
			size1--;
			size2--;
		}
		while (size1){
			//当num1还有剩余高位数
			ret = (((num1[i] - '0') + flag) % 10);
			addret += (ret + '0');
			//addret.insert(addret.begin(), ret + '0');
			flag = (((num1[i--] - '0') + flag) / 10);
			size1--;
		}
		while (size2){
			//当num2还有剩余高位数
			ret = (((num2[j] - '0') + flag) % 10);
			addret += (ret + '0');
			//addret.insert(addret.begin(), ret + '0');
			flag = (((num2[j--] - '0') + flag) / 10);
			size2--;
		}
		if (flag){

			addret += (flag + '0');
			//addret.insert(addret.begin(), flag+ '0');
		}
		reverse(addret.begin(), addret.end());
		return addret;
	}
};

/*
541. 反转字符串 II
给定一个字符串和一个整数 k，你需要对从字符串开头算起的每个 2k 个字符的前k个字符进行反转。如果剩余少于 k 个字符，
则将剩余的所有全部反转。如果有小于 2k 但大于或等于 k 个字符，则反转前 k 个字符，并将剩余的字符保持原样。
示例:
输入: s = "abcdefg", k = 2
输出: "bacdfeg"
要求:
该字符串只包含小写的英文字母。
给定字符串的长度和 k 在[1, 10000]范围内。
*/
//思路：判断>2k  k>&&<2k  <k的三种情况进行处理 用reverse函数解决
class Solution {
public:
	string reverseStr(string s, int k) {
		int len = s.size();
		int i = 0;
		while (len >= 2 * k){
			reverse(s.begin() + i, s.begin() + i + k);
			i += (2 * k);
			len -= 2 * k;
		}
		if (len >= k&&len < 2 * k){
			reverse(s.begin() + i, s.begin() + i + k);
		}
		else{
			reverse(s.begin() + i, s.end());
		}
		return s;
	}
};

/*
557. 反转字符串中的单词 III
给定一个字符串，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。
示例 1:
输入: "Let's take LeetCode contest"
输出: "s'teL ekat edoCteeL tsetnoc"
*/
class Solution {
public:
	string reverseWords(string s) {
		string::iterator it = s.begin(), top = it;
		for (it; it < s.end(); it++){
			if (*it == ' '){
				reverse(top, it);
				top = it + 1;
			}
		}
		reverse(top, it);//翻转最后一个字符
		return s;
	}
};
