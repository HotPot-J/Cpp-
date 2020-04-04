#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
/*
一、unordered_map介绍：
  1.unordered_map是存储<key，value>键值对的关联式容器，其允许通过keys快
  速的索引到与其对应的value。
  2.在unordered_map中，键值通常用于唯一的标识元素，而映射值是一个对象，
  其内容与此键关联。键和映射值的类型可能不同。
  3.在内部，unordered_map没有对<key，value>按照任何特定的顺序排序，为了
  能在常数范围内找到key所对应的value，unordered_map将相同哈希值的键值对
  放在相同的桶中。
  4.unordered_map容器通过key访问单个元素比map快，但它通常在遍历元素子集
  的范围迭代方面效率较低。
  5.unordered_map实现了直接访问操作符(operator[])，它允许使用key作为参数
  直接访问value。
  6.它的迭代器是前向迭代器
*/

/*
二、unordered_map的接口说明
1.构造：
unordered_map 构造不同格式的unordered_map对像
2.容量：
 bool empty()const 检测unordered_map是否为空
 size_t size()const 获取unordered_map的有效元素个数
3.迭代器：
  begin
  end
  cbegin
  cend
4.元素访问：
 operator[] 返回key对应的value，没有一个默认值
5.unordered_map的查询
iterator find(const K& key)  返回key在哈希桶中的位置
size_t count(const K& key) 返回哈希桶中关键码为key的键值对的个数
6.修改操作
 insert 向容器中插入键值对
 erase 删除容器中的键值对
 void clear() 清空容器中的有效元素个数
 void swap(unordered_map&) 交换两个容器中的元素
7.unoedered_map的桶操作
 size_t bucket count()const 返回哈希桶中的总个数
 size_t bucket size(size_t n)const 返回n号桶中有效元素的总个数
 size_t bucket(const K& key) 返回元素key所在的桶号
*/
 //OJ小训练
/*
961. 重复 N 次的元素
在大小为 2N 的数组 A 中有 N+1 个不同的元素，其中有一个元素重复了 N 次。
返回重复了 N 次的那个元素。
示例 1：
输入：[1,2,3,3]
输出：3
示例 2：
输入：[2,1,2,5,3,2]
输出：2
示例 3：
输入：[5,1,5,2,5,3,5,4]
输出：5
*/
class Solution {
public:
	int repeatedNTimes(vector<int>& A) {
		int N = A.size() / 2;
		//用unordered_map来统计每个元素出现的个数
		unordered_map<int, int> m;
		for (auto a : A){
			m[a]++;
		}
		//遍历数组
		/*for (auto a : A){
			if (m[a] == N){
				return a;
			}
		}*/
		//遍历哈希表
		for (auto a : m){
			if (a.second == N){
				return a.first;
			}
		}
		return 0;
	}
};
/*
2.面试题52. 两个链表的第一个公共节点
思路：数据结构中运用了快慢指针的思想，时间复杂度O（n） 空间O（1）
这次运用哈希表 时间复杂度O（n）空间复杂度O（n）
key为结点，value为bool值 先遍历第一条链表键值对存入哈希表 再访问第二条
若某个节点的bool为true 则为公共结点
*/
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
	
};

class Solution {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		unordered_map<ListNode*, bool> m;
		ListNode* a = headA;
		ListNode* b = headB;
		while (a){
			m[a] = true;
			a = a->next;
		}
		unordered_map<ListNode*, bool>::iterator it;
		while (b){
			it = m.find(b);
			if (it == m.end()){
				;
			}
			else{
				return b;
			}
			b = b->next;
		}
		return NULL;
	}
};

/*
面试题35. 复杂链表的复制
请实现 copyRandomList 函数，复制一个复杂链表。在复杂链表中，
每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针
指向链表中的任意节点或者 null。
提示：
-10000 <= Node.val <= 10000
Node.random 为空（null）或指向链表中的节点。
节点数目不超过 1000 。
*/
//思路：哈希表 复制一遍没有random指针的链表，这个时候原表和现在的表结点的对应
//关系已经存在，用哈希表记录一下 再遍历一遍，每个位置读取random指向的原表结点
//根据哈希表查到复制后对应的结点，建立连接
class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};
class Solution {
public:
	Node* copyRandomList(Node* head) {
		if (head == NULL){
			return head;
		}
		//定义一个哈希表
		unordered_map<Node*, Node*> m;
		//为新的头节点开辟空间
		Node* newhead = new Node(head->val);
		//遍历第一遍 复制不带random链表 并使新旧链表建立关联
		Node* n = newhead;
		Node* o = head;
		while (o){
			m[o] = n;
			o = o->next; //一开始就走一步是因为上一行为了建立两个链表头节点的哈希关系 而先前已经复制过头节点了 所以要从下一个结点开始复制
			if (o == NULL){
				n->next = NULL;
			}
			else{
				Node* next = new Node(o->val);
				n->next = next;
			}
			n = n->next;
		}
		//根据old和new链表的哈希关系为new的random赋值
		n = newhead;
		o = head;
		while (o){
			n->random = m[o->random];//m[o->random]： o->random的地址在m中对应的新链表中的某结点地址
			//将该地址赋值给当前的n->random 则建立起了该节点的复杂连接 
			o = o->next;
			n = n->next;
		}
		return newhead;
	}
};