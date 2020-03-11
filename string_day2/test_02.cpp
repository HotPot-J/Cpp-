#include<iostream>
using namespace std;

void Test(){

   string str;
   str+="jxy";//在str后追加jxy字符串
   str.push_back(' ');//在str后插入空格
   str.append("hello");//在str后追加字符串
   str+='a';//在str后追加字符'a'
   cout<<str<<endl;
   cout<<"c语言方式打印："<<endl;
   cout<<str.c_str()<<endl;
   cout<<"------------------------------"<<endl;
  
   //利用find和substr获取file的后缀方法
    string file("jxy.cpp");
	size_t pos = file.find('.');
	string ret(file.substr(pos,file.size()-pos));
	cout<<ret<<endl;


	//去除url域名
	string url("http://www.cplusplus.com/find");
	cout<<endl<<url<<endl;
	size_t start = url.find("://");
	if(start == string::npos){
	  cout<<"invalid url(无效网址)"<<endl;
	  return;
	}
	start+=3;// "://"为三个字符 +=3得到的为其后一个字符位置
	size_t tail = url.find('/',start);//找到字符串中尾巴的‘/’位置
	//截取出有效字符串并赋值给address
	string address = url.substr(start,tail-start);
	cout<<"address: "<<address<<endl;
   
	//删除url的协议前缀
	pos = url.find("://");
	url.erase(0,pos+3);
	cout<<url<<endl;
}
int main(){
 Test();
 return 0;
}
