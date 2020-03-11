#include<iostream>
using namespace std;
//遍历字符串
void Test(){

   string s("hello world!");

   //1.for+operator[]的方式(常用)
   for(size_t i = 0;i<s.size();i++){
       cout<<s[i];
   }
  
   //2.迭代器
   string::iterator it = s.begin();
   while(it!=s.end()){
    cout<<*it;
	it++;
   }

   //3.范围for
  /* for(auto ch : s){
     cout<<ch;
   }*/
}

int main(){
  Test();
  return 0;
}
