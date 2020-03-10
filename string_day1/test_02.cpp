#include<iostream>
using namespace std;
void test1(){
  //string 类对象支持直接用cin和cout进行输入输出
 /*
  *测试一下string类对象的写入和输出
  * string s1;
  cin>>s1;
  cout<<s1<<endl;*/ 

  string s("hello world!");
  cout<<"s字符串的有效字符长度："<<s.size()<<endl;
  cout<<"s字符串占用空间总大小："<<s.capacity()<<endl;
  cout<<s<<endl;
  cout<<endl;
  //将s中的字符串清空，注意清空时只是将size清0，不改变第层空间
  //大小
/*  s.clear();
  cout<<"执行完清空操作后："<<endl;
  cout<<"s字符串的有效字符长度："<<s.size()<<endl;
  cout<<"s字符串占用空间总大小："<<s.capacity()<<endl;
  cout<<endl;*/
  //将s中有效字符数增加到20个，多余位置用'a'进行填充
  s.resize(20,'a');
  cout<<"有效字符扩容到20个"<<endl;
  cout<<"长度："<<s.size()<<endl;
  cout<<"空间："<<s.capacity()<<endl;
  cout<<s<<endl;
  cout<<endl;
  //将有效字符缩小到5个
  s.resize(5);
  cout<<"有效字符缩小到5个"<<endl;
  cout<<"长度: "<<s.size()<<endl;
  cout<<"空间："<<s.capacity()<<endl;
  cout<<s<<endl;
 
  cout<<"---------------------------------------------"<<endl;
  
}

void test2(){

  string s;

  //测试reserve是否会改变string中有效元素的个数
  //结果：会
  s.reserve(100);
  cout<<s.size()<<endl;
  cout<<s.capacity()<<endl;
  cout<<endl;
  //测试reserve参数小于string的底层空间大小时，是否会将空间缩小
  //结果：会
  s.reserve(50);
  cout<<s.size()<<endl;
  cout<<s.capacity()<<endl;

  //可以利用reserve提高插入数据的效率，避免增容带来的开销
}

int main(){
 // test1();
 test2();
  return 0;
}
