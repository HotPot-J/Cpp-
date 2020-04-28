#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<assert.h>
using namespace std;

//namespace HotPot{
//	class _string{
//		friend ostream& operator<<(ostream& out, const HotPot::_string& s);
//	public:
//		//构造函数
//		//_string(char* str = nullptr) 不能给nullptr 因为会导致strlen崩溃
//		_string(char* str = "")
//			:_str(new char[strlen(str) + 1])
//		{
//			strcpy(_str, str);
//		}
//		//析构函数
//		~_string(){
//			delete[] _str;
//			_str = nullptr;
//		}
//		//拷贝构造  这里需要深拷贝 浅拷贝会导致两个对象指向同一块地址空间 析构两次则会造成崩溃
//		//_string copy(s); copy即是参数列表中的this  
//		_string(const _string& s)
//			:_str(new char[strlen(s._str)+1])
//		{
//			strcpy(_str, s._str);
//		}
//
//		//copy = s
//		_string& operator=(const _string& s){
//			if (this != &s){ //该条件语句防止自己赋值给自己 
//				delete[] _str; //防止_str的空间小于s._str 所以将其释放掉 重新开辟与s.str一样大小的空间
//				_str = new char[strlen(s._str) + 1];
//				strcpy(_str, s._str);
//			}
//			return *this;
//		}
//	    //重载[]
//		char& operator[](size_t pos){
//			return _str[pos];
//		}
//		const char& operator[](size_t pos) const
//		{
//			return _str[pos];
//		}
//		//计算string长度
//		size_t size() 
//		{
//			return strlen(_str);
//		}
//		const size_t size() const//这个const是修饰*this的 
//		{
//			return strlen(_str);
//		}
//	private:
//		 char* _str;
//	}; 
//
//} 
////重载输出 之所以定义成全局的，就是因为再public中 函数会默认第一个参数为this 由于这里
////需要第一个参数为ostream& out 
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

//增删查改的string类模拟实现

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
		//构造函数
		_string(const char* str = "")
			:_size(strlen(str))
		{
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		//析构
		~_string(){
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		//拷贝构造
		_string(const _string& s){
			_str = new char[s._size + 1];
			strcpy(_str, s._str);
			_size = s._size;
			_capacity = s._size;
		}
		//赋值重载
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
		//[]重载

		//可读可写
		char& operator[](size_t pos){
			assert(pos < _size);
			return _str[pos];
		}
		//只读
		const char& operator[](size_t pos) const{
			assert(pos < _size);
			return _str[pos];
		}
		void _reserve(size_t n){
			//增容
			if (n>_capacity){
				_capacity *= 2;
				char *newstr = new char[n + 1];
				strcpy(newstr, _str);
				delete[] _str;
				_str = newstr ;
				_capacity = n;
			}
		}
		//增
		void _push_back(char ch){
			//尾插一个字符
			_reserve(_capacity * 2);//需要增容
			_str[_size] = ch;
			++_size;
			_str[_size] = '\0';
		}

		void _append(const char* str){
			//尾插一个字符串
			size_t len = strlen(str);
			_reserve(_size + len);	//需要增容
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
				//删除数据
				_size = n;
				_str[_size] = '\0';
			}
			else{
				//插入数据
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

		//获取有效长度
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
   //用迭代器遍历
	HotPot::_string::iterator it = s2.begin();
	while (it != s2.end()){
		cout << *it;
		++it;
	}
	cout << endl;
	cout << s2.size()<<endl;
	s2._resize(10);
	//范围for是有迭代器支持的，这里会被编译器自动转换成迭代器遍历
	for (auto& ch : s2){
		cout << ch ;
	}
	cout << endl;
	s2._resize(13, '7');
	cout << s2 << endl;
	return 0;
}
