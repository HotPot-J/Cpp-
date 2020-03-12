#include<iostream>

using namespace std;

void test(){
  cout<<"请输入姓名：";
   string name;
   cin>>name;
   cout<<name<<endl;
   
   cout<<"请修改姓名：";
   getline(cin,name);
   cout<<name<<endl;
}

int main(){
  test();
  return 0;
}
