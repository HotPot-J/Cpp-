#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

//namespace HotPot{
//	class _string{
//		friend ostream& operator<<(ostream& out, const HotPot::_string& s);
//	public:
//		//���캯��
//		//_string(char* str = nullptr) ���ܸ�nullptr ��Ϊ�ᵼ��strlen����
//		_string(char* str = "")
//			:_str(new char[strlen(str) + 1])
//		{
//			strcpy(_str, str);
//		}
//		//��������
//		~_string(){
//			delete[] _str;
//			_str = nullptr;
//		}
//		//��������  ������Ҫ��� ǳ�����ᵼ����������ָ��ͬһ���ַ�ռ� �������������ɱ���
//		//_string copy(s); copy���ǲ����б��е�this  
//		_string(const _string& s)
//			:_str(new char[strlen(s._str)+1])
//		{
//			strcpy(_str, s._str);
//		}
//
//		//copy = s
//		_string& operator=(const _string& s){
//			if (this != &s){ //����������ֹ�Լ���ֵ���Լ� 
//				delete[] _str; //��ֹ_str�Ŀռ�С��s._str ���Խ����ͷŵ� ���¿�����s.strһ����С�Ŀռ�
//				_str = new char[strlen(s._str) + 1];
//				strcpy(_str, s._str);
//			}
//			return *this;
//		}
//	    //����[]
//		char& operator[](size_t pos){
//			return _str[pos];
//		}
//		const char& operator[](size_t pos) const
//		{
//			return _str[pos];
//		}
//		//����string����
//		size_t size() 
//		{
//			return strlen(_str);
//		}
//		const size_t size() const//���const������*this�� 
//		{
//			return strlen(_str);
//		}
//	private:
//		 char* _str;
//	}; 
//
//} 
////������� ֮���Զ����ȫ�ֵģ�������Ϊ��public�� ������Ĭ�ϵ�һ������Ϊthis ��������
////��Ҫ��һ������Ϊostream& out 
//ostream& HotPot::operator<<(ostream& out, const HotPot::_string& s){
//	for (size_t i = 0; i < s.size(); ++i){
//		out << s[i];
//	}
//	return out;
//}
//int main(){
//	HotPot::_string s1;
//	HotPot::_string s2("hello");
//	HotPot::_string s3(s2);
//	HotPot::_string s4 = s3;
//	s2[1] = 'x';
//	cout<< s1 << endl;
//	cout<< s2 << endl;
//	cout<< s3 << endl;
//	cout << s4 << endl;
//} 

//��ɾ��ĵ�string��ģ��ʵ��

namespace HotPot{
	class _string{
	friend ostream& operator<<(ostream& out, const HotPot::_string& s);
	public:
		typedef char* iterator;
		iterator begin(){
			return _str;
		}
		iterator end(){
			return _str + _size;
		}
		//���캯��
		_string(const char* str = "")
			:_size(strlen(str))
		{
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		//����
		~_string(){
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		//��������
		_string(const _string& s){
			_str = new char[s._size + 1];
			strcpy(_str, s._str);
			_size = s._size;
			_capacity = s._size;
		}
		//��ֵ����
		_string& operator=(const _string& s){
			if (this != &s){
				delete[] _str;
				_str = new char[s._size + 1];
				strcpy(_str, s._str);
				_size = s._size;
				_capacity = s._size;
			}
			return *this; 
		}
		//[]����

		//�ɶ���д
		char& operator[](size_t pos){
			assert(pos < _size);
			return _str[pos];
		}
		//ֻ��
		const char& operator[](size_t pos) const{
			assert(pos < _size);
			return _str[pos];
		}
		void _reserve(size_t n){
			//����
			if (n>_capacity){
				_capacity *= 2;
				char *newstr = new char[n + 1];
				strcpy(newstr, _str);
				delete[] _str;
				_str = newstr ;
				_capacity = n;
			}
		}
		//��
		void _push_back(char ch){
			//β��һ���ַ�
			_reserve(_capacity * 2);//��Ҫ����
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}

		void _append(const char* str){
			//β��һ���ַ���
			size_t len = strlen(str);
			_reserve(_size + len);	//��Ҫ����
			strcpy(_str + _size, str);
			_size += len;
		}

		//s1+='x'
		_string& operator+=(char ch){
			this->_push_back(ch);
			return *this;
		}
		_string& operator+=(const char* str){
			this->_append(str);
			return *this;
		}

		//resize
		void _resize(size_t n, char ch = '\0'){
			if (n < _size){
				//ɾ������
				_size = n;
				_str[_size] = '\0';
			}
			else{
				//��������
				if (n>_capacity){
					_reserve(n);
				}
				for (size_t i = _size; i < n; ++i){
					_str[i] = ch;
				}
				_size = n;
				_str[_size] = '\0';
			}
		}

		//��ȡ��Ч����
		size_t size(){
			return _size;
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}
ostream& HotPot::operator<<(ostream& out, const HotPot::_string& s){
	for (size_t i = 0; i < s._size; ++i){
		out << s[i];
	}
	return out;
}
int main(){
	HotPot::_string s1("hello");
	cout << s1 << endl;
	HotPot::_string s2 = s1;
	cout << s2 << endl;
	s2._push_back('x');
	cout << s2 << endl;
	s2._append("123");
	cout << s2 << endl;
	s2 += '4';
	s2 += "56";
	//cout << s2 << endl;
   //�õ���������
	HotPot::_string::iterator it = s2.begin();
	while (it != s2.end()){
		cout << *it;
		++it;
	}
	cout << endl;
	cout << s2.size()<<endl;
	s2._resize(10);
	//��Χfor���е�����֧�ֵģ�����ᱻ�������Զ�ת���ɵ���������
	for (auto& ch : s2){
		cout << ch ;
	}
	cout << endl;
	s2._resize(13, '7');
	cout << s2 << endl;
	return 0;
}
