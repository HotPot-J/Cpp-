#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<queue>
using namespace std;

/*
queue的介绍：
   1.队列是一种容器适配器，专门用于（先进先出）的操作，其从容器的一段插入
   元素，另一端提取元素。
   2.队列作为容器适配器实现，容器适配器即将特定容器类封装，作为其底层容
   器类，queue提供一组特定的成员函数来访问其元素。元素从队尾入队列，从队
   头出队列。
   3.底层容器是标准类模板之一，也可以是专门设计的容器类。该底层容器应至
   少支持以下操作：
     empty：判空
	 size：返回有效个数
	 front：返回队头元素的引用
	 back：返回队列尾元素的引用
	 push_back:在队尾部入队列
	 pop_front：在队列头部出队列
	4.标准类容器deque和list满足这些要求。默认情况下，如果没有queue实例化
	指定容器类，则使用deque
*/
/*
queue的使用：
  queue()构造空的队列
  empty()检测队列是否为空，是返回true 否则返回false
  size() 返回队列中有效元素的个数
  front() 返回对头元素的引用
  back() 返回队尾元素的引用
  push() 在队尾将元素val入队列
  pop() 将队头元素出队列
*/