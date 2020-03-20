#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include <algorithm>
using namespace std;

/*
415. �ַ������
���������ַ�����ʽ�ķǸ����� num1 ��num2 ���������ǵĺ͡�
ע�⣺
num1 ��num2 �ĳ��ȶ�С�� 5100.
num1 ��num2 ��ֻ�������� 0-9.
num1 ��num2 ���������κ�ǰ���㡣
�㲻��ʹ���κ΃Ƚ� BigInteger �⣬ Ҳ����ֱ�ӽ�������ַ���ת��Ϊ������ʽ��
*/
//˼·�� ���ý���λ  ��ͬʱ�������ַ���ĩβ��ǰ����  
//1.���Խ����ֱ��׷����addret�� ��reverse�������䷭ת�õ����
//2.Ҳ����ÿ�ζ�ʹ��insert����ͷ���addret��ֱ�����ɽ�� ���Ǹ÷������ڳ��ַ�����˵ʱ�临�Ӷ��е��                 
class Solution {
public:
	string addStrings(string num1, string num2) {
		int flag = 0;//��ʼ������λΪ0
		int ret = 0;
		string addret;
		int i = num1.size() - 1, j = num2.size() - 1;
		int size1 = i + 1, size2 = j + 1;
		while (size1&&size2){
			ret = (((num1[i] - '0') + (num2[j] - '0') + flag) % 10);
			addret += (ret + '0');
			//addret.insert(addret.begin(), ret+'0');//ͷ���ȥ �Ͳ��÷�ת��
			flag = (((num1[i--] - '0') + (num2[j--] - '0') + flag) / 10);
			size1--;
			size2--;
		}
		while (size1){
			//��num1����ʣ���λ��
			ret = (((num1[i] - '0') + flag) % 10);
			addret += (ret + '0');
			//addret.insert(addret.begin(), ret + '0');
			flag = (((num1[i--] - '0') + flag) / 10);
			size1--;
		}
		while (size2){
			//��num2����ʣ���λ��
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
541. ��ת�ַ��� II
����һ���ַ�����һ������ k������Ҫ�Դ��ַ�����ͷ�����ÿ�� 2k ���ַ���ǰk���ַ����з�ת�����ʣ������ k ���ַ���
��ʣ�������ȫ����ת�������С�� 2k �����ڻ���� k ���ַ�����תǰ k ���ַ�������ʣ����ַ�����ԭ����
ʾ��:
����: s = "abcdefg", k = 2
���: "bacdfeg"
Ҫ��:
���ַ���ֻ����Сд��Ӣ����ĸ��
�����ַ����ĳ��Ⱥ� k ��[1, 10000]��Χ�ڡ�
*/
//˼·���ж�>2k  k>&&<2k  <k������������д��� ��reverse�������
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
557. ��ת�ַ����еĵ��� III
����һ���ַ���������Ҫ��ת�ַ�����ÿ�����ʵ��ַ�˳��ͬʱ�Ա����ո�͵��ʵĳ�ʼ˳��
ʾ�� 1:
����: "Let's take LeetCode contest"
���: "s'teL ekat edoCteeL tsetnoc"
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
		reverse(top, it);//��ת���һ���ַ�
		return s;
	}
};
