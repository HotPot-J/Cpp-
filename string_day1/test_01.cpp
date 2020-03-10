#include<iostream>

using namespace std;
void Teststring(){
  string s1; //构造空的string类的对象
  string s2("hello world!");//用c格式字符串构造string类对象s2
  cout<<s2<<endl;
  string s3(s2);//拷贝构造s3
  cout<<s3<<endl;
  string s4(10,'a');
  cout<<s4<<endl;
}

int main(){
    Teststring();
	return 0;
}
