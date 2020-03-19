#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;
/*
917. ������ת��ĸ
����һ���ַ��� S������ ����ת��ġ� �ַ��������в�����ĸ���ַ���������ԭ�أ���������ĸ��λ�÷�����ת��
ʾ�� 1��
���룺"ab-cd"
�����"dc-ba"
ʾ�� 2��
���룺"a-bC-dEf-ghIj"
�����"j-Ih-gfE-dCba"
ʾ�� 3��
���룺"Test1ng-Leet=code-Q!"
�����"Qedo1ct-eeLg=ntse-T!"
��ʾ��
S.length <= 100
33 <= S[i].ASCIIcode <= 122
S �в����� \ or "
*/

/*
˼·�� ˫ָ��  �ж��Ƿ�Ϊ��ĸ

֪ʶ��չ�����о�Ϊ�궨�� ���Ǻ��� ����iostream�� 
 1.isalpha() �����ж�һ���ַ��Ƿ�Ϊ��ĸ���������ĸ���ط�0 ���򷵻�0
 2.isalnum() �����ж�һ���ַ��Ƿ��������ֻ���ĸ�����ж�һ��
 �ַ��Ƿ�����a-z||A-Z||0-9
 3.islower() �����ж�һ���ַ��Ƿ�����Сд��ĸ��Ҳ�����Ƿ�����a-z
 4.isupper() �����ж�һ���ַ��Ƿ�Ϊ��д��ĸ

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
387. �ַ����еĵ�һ��Ψһ�ַ�
����һ���ַ������ҵ����ĵ�һ�����ظ����ַ���������������������������ڣ��򷵻� -1��
����:
s = "leetcode"
���� 0.
s = "loveleetcode",
���� 2.
*/
//˼·������һ��map �������map['�ַ�']�ĸ��� �ҳ�mapֵΪ1�ĵ�һ���ַ����������� ʱ�临�Ӷ�O��2n��
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
��Ŀ����
�����ַ������һ�����ʵĳ��ȣ������Կո������
��������:
һ���ַ������ǿգ�����С��5000��
�������:
����N�����һ�����ʵĳ��ȡ�
ʾ��1
����
hello world
���
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
		//ֻ��һ������
		cout << s.size() << endl;
	}
	else{
		cout << s.size() - pos - 1 << endl;
	}
	return 0;
}

/*
125. ��֤���Ĵ�
����һ���ַ�������֤���Ƿ��ǻ��Ĵ���ֻ������ĸ�������ַ������Ժ�����ĸ�Ĵ�Сд��
˵���������У����ǽ����ַ�������Ϊ��Ч�Ļ��Ĵ���
ʾ�� 1:
����: "A man, a plan, a canal: Panama"
���: true
ʾ�� 2:
����: "race a car"
���: false
*/
//˼·���Ƚ���д��ת��ΪСд���ڽ��бȶ�
class Solution {
public:
	bool isPalindrome(string s) {
		for (auto &ch : s){
			//����д��ת��ΪСд
			if (ch >= 'A'&&ch <= 'Z'){
				ch += 32;
			}
		}
		char* top = (char*)s.c_str();
		char* tail = top + s.size() - 1;
		while (top < tail){
			while (top < tail){
				if (isalnum(*top)){//�����ֻ�����ĸ
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