#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;
/*
917. 仅仅反转字母
给定一个字符串 S，返回 “反转后的” 字符串，其中不是字母的字符都保留在原地，而所有字母的位置发生反转。
示例 1：
输入："ab-cd"
输出："dc-ba"
示例 2：
输入："a-bC-dEf-ghIj"
输出："j-Ih-gfE-dCba"
示例 3：
输入："Test1ng-Leet=code-Q!"
输出："Qedo1ct-eeLg=ntse-T!"
提示：
S.length <= 100
33 <= S[i].ASCIIcode <= 122
S 中不包含 \ or "
*/

/*
思路： 双指针  判断是否为字母

知识拓展：下列均为宏定义 并非函数 都在iostream中 
 1.isalpha() 用来判断一个字符是否为字母，如果是字母返回非0 否则返回0
 2.isalnum() 用来判断一个字符是否属于数字或字母，即判断一个
 字符是否属于a-z||A-Z||0-9
 3.islower() 用来判断一个字符是否属于小写字母，也就是是否属于a-z
 4.isupper() 用来判断一个字符是否为大写字母

*/
class Solution {
public:
	string reverseOnlyLetters(string S) {
		char* top = (char*)S.c_str();
		char* tail = top + S.size() - 1;
		char tmp = '0';
		while (top < tail){
			while (top<tail){
				if (isalpha(*top)){
					break;
				}
				top++;
			}
			while (top<tail){
				if (isalpha(*tail)){
					break;
				}
				tail--;
			}
			if (top < tail){
				swap(*top, *tail);
				top++;
				tail--;
			}
		}
		return S;
	}
};

/*
387. 字符串中的第一个唯一字符
给定一个字符串，找到它的第一个不重复的字符，并返回它的索引。如果不存在，则返回 -1。
案例:
s = "leetcode"
返回 0.
s = "loveleetcode",
返回 2.
*/
//思路：定义一个map 用来存放map['字符']的个数 找出map值为1的第一个字符返回其索引 时间复杂度O（2n）
class Solution1 {
public:
	int firstUniqChar(string s) {
		int map[256] = { 0 };
		char tmp = 0;
		for (int i = 0; i<s.size(); i++){
			tmp = s[i];
			map[tmp]++;
		}
		for (int i = 0; i<s.size(); i++){
			tmp = s[i];
			if (map[tmp] == 1){
				return i;
			}
		}
		return -1;
	}
};
/*
题目描述
计算字符串最后一个单词的长度，单词以空格隔开。
输入描述:
一行字符串，非空，长度小于5000。
输出描述:
整数N，最后一个单词的长度。
示例1
输入
hello world
输出
5
*/
#include<iostream>
#include<string>
using namespace std;
int main(){
	string s;
	int pos = -1;
	getline(cin, s);
	for (int i = 0; i < s.size(); i++){
		if (s[i] == ' '){
			pos = i;
		}
	}
	if (pos == -1){
		//只有一个单词
		cout << s.size() << endl;
	}
	else{
		cout << s.size() - pos - 1 << endl;
	}
	return 0;
}

/*
125. 验证回文串
给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。
说明：本题中，我们将空字符串定义为有效的回文串。
示例 1:
输入: "A man, a plan, a canal: Panama"
输出: true
示例 2:
输入: "race a car"
输出: false
*/
//思路：先将大写都转换为小写，在进行比对
class Solution {
public:
	bool isPalindrome(string s) {
		for (auto &ch : s){
			//将大写都转化为小写
			if (ch >= 'A'&&ch <= 'Z'){
				ch += 32;
			}
		}
		char* top = (char*)s.c_str();
		char* tail = top + s.size() - 1;
		while (top < tail){
			while (top < tail){
				if (isalnum(*top)){//是数字或者字母
					break;
				}
				top++;
			}
			while (top < tail){
				if (isalnum(*tail)){
					break;
				}
				tail--;
			}
			if (*top != *tail){
				return false;
			}
			top++;
			tail--;
		}
		return true;
	}
};

/*

*/