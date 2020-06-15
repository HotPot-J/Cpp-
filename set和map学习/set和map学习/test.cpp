#define _CRT_SECURE_NO_WARNINGS 1

/*
一、相关概念：
1、关联式容器
	序列式容器:vector、list、deque等，其底层为线性序列的数据结构，里面存储的
是元素本身。
	关联式容器：也是用来存储数据的，不同点在于，其里面存储的是<key，value>结构
	的键值对，再数据检索时比序列式容器效率更高。

2、键值对：
	用来表示具有一一对应关系的一种结构，该结构中一般只包含两个成员变量key和
	value，key代表键值，value表示与key对应的信息。

3、树形结构的关联式容器
	根据应用场景的不同，STL总共实现了两种不同结构的管理式容器:树形结构与哈希
	结构。树形结构主要为:map,set,multimap、multiset。
	该四种容器的共同点：使用平衡搜索树(即红黑树)作为其底层结果，容器中的元素
	是一个有序的序列。

4.STL中关于键对值的定义:
template <class T1, class T2>
struct pair
{
 typedef T1 first_type;
 typedef T2 second_type;
 T1 first;  //Key
 T2 second; //Value
 pair(): first(T1()), second(T2())
 {}
 
 pair(const T1& a, const T2& b): first(a), second(b)
 {}
};
*/


/*
二、set
	1.set是按照一定次序存储元素的容器
	2.在set中，元素的value即为key，并且每个value都是唯一的，set中的元素不能在
	容器中修改，但是可以从容器中插入或者删除它们。
	3.在内部，set中的元素总是按照其内部比较对象(类型比较)所指示的严格排序准则进行排序
	4.set容器通过key访问单个元素的速度通常比unordered_set容器慢，但它们允许根据顺序对
	子集进行直接迭代。
	5.set在底层使用二叉搜索树(红黑树)实现的。

值得注意的点:
	1.set中只放value，但在底层实际存放的是由<value,value>构成的键值对
	2.set中插入元素时，只要插入value即可，不需要构造键值对
	3.set中的元素不可以重复（关于去重的问题使用set就美滋滋）
	4.使用set中的迭代器遍历set中的元素，可以得到有序序列
	5.set中的元素默认按照小于来比较
	6.set中查找某个元素，时间复杂度为 logN
	7.set中的元素不允许修改 （如果修改就会破坏其的结构顺序）

常用的接口：
	set<int> a;
	迭代器:
		a.begin()  a.end()
	容量:
		bool empty() const  
		size_type size() const //返回set中有效元素的个数
	增删：
		pair<iterator,bool>insert(const value_type& x) 
			在set中插入元素x，实际插入的是<x,x>构成的键值对
			如果插入成功，返回<该元素在set中的位置,true>，如果
			插入失败，说明x在set中已经存在，返回<该元素在set中的位置,false>
		a.insert（1）;

		void erase（iterator position） 删除set中在position位置上的元素
		size_type erase（const key_type& x） 删除set中值为x的元素，返回删除的元素的个数

		void clear() 将set中的元素清空

*/

/*
三、map
	1.map是关联容器，他按照特定的次序(按照key来比较)存储由键值key和值value组合而成的元素
	2.在map中，键值key通常用于排序和唯一地标识元素，而值value中存储与此键值key关联的内容。
	键值和值value的类型可能不同，并且在map的内部，key与value通过成员类型value_type绑定在
	一起，取其别名称为pair
	3.在内部，map中的元素总是按照键值key进行比较排序的
	4.map中通过键值访问单个元素的速度通常比unordered_map容器慢，但是map允许根据顺序对元素
	直接迭代(即，对map中的元素进行迭代时，可以得到一个有序的序列)
	5.map支持下标访问符，即[]中放入key，就可以找到与key对应的value
	6.map通常被实现为平衡二叉搜索树

常用接口：
	例子:map<string,string> m;

	迭代器：
		m.begin() m.end() 返回的是一个pair结构体 需要用pair->first/->second 去访问key/value 

    容量：
		bool empty() const
		size_type size() const 返回有效个数

    ****元素访问:
		mapped_type& operator[]（const key_type& k） 返回key对应的value
			底层： 
			mapped_type& operator[]（const key_type& k）{
			   return（*（（this->insert（make_pair(k,mapped_type())））.first））.second;
			}
			(insert函数：若存在k则返回该位置迭代器，若不存在则插入以后，使用mapped_type（）默认
			构造函数初始化value，并返回该位置pair的迭代器：this->insert（make_pair(k,mapped_type())））.first
			在经过*和.second即返回了  所以达到[]函数可以返回v的引用的目的)
	
		 operator[]功能:
			1.如果k在容器中已经存在，则返回对应v的引用，可以借助其修改v
			2.如果k在容器中不存在，则会先插入pair<k,V()>,反回v的引用。不过
		注意这里的v是调用V类型的默认构造函数生成默认值。
	
	map中元素的修改
		pair<iterator,bool>insert（const value_type& x） 在map中插入键值对x
		void earse(iterator position) 删除pos位置上的元素
		size_type erase(const key_type& x) 删除键值对为x的元素
		void erase(iterator first,iterator last）删除[first，last]区间中的元素
		void clear（） 将map中元素清空
		iterator find(const key_type& x) 在map中插入key为x的元素，找到返回该元素的const迭代器,否则返回end
		
	**insert（）用法  
		map<int,double> a;
		a.insert(pair<int,double>(1,2.0));  //也可以写成:a.insert(make_pair(1,2.0));
        a.insert(pair<int,double>(2,3.0));
        a.insert(pair<int,double>(1,4.0));
		//遍历
		map<int,double>::iterator it = a.begin();
		while(it!=a.end()){
			//cout<<*it<<" ";   //会报错 由于其返回的是一个pair
			cout<<it->first<<" ："<<it->second; //依次返回其key和value
			++it;
		}
		


总结：
		1.map中的元素是键值对
		2.map中的key是唯一的，并不能修改
		3.默认按照小于的方式对key进行比较
		4.map中元素如果用迭代器去遍历，可以得到一个有序的序列
		5.查找效率：O（logN）
		6.支持[]操作符，在operator[]中进行插入查找
*/


/*
OJ题的应用:

692. 前K个高频单词
给一非空的单词列表，返回前 k 个出现次数最多的单词。

返回的答案应该按单词出现频率由高到低排序。如果不同的单词有相同出现频率，按字母顺序排序。

示例 1：

输入: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
输出: ["i", "love"]
解析: "i" 和 "love" 为出现次数最多的两个单词，均为2次。
    注意，按字母顺序 "i" 在 "love" 之前。
 

示例 2：

输入: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
输出: ["the", "is", "sunny", "day"]
解析: "the", "is", "sunny" 和 "day" 是出现次数最多的四个单词，
    出现次数依次为 4, 3, 2 和 1 次。
 

注意：

假定 k 总为有效值， 1 ≤ k ≤ 集合元素数。
输入的单词均由小写字母组成。
*/
#include<iostream>
#include<vector>
#include<map> 
#include <functional>
using namespace std;
class Solution {
public:
	vector<string> topKFrequent(vector<string>& words, int k) {
		map<string, int> countmap;
		for (auto& e : words){
			countmap[e]++;   //此时统计出了各个字符串出现次数，且按照string的排序顺序进行了排序
		}

		//接下来由于map不允许数据冗余 使用multimap来进行个数排序
		multimap<int, string, greater<int>> countSort;
		//countSort 定义int为key string为value 再加上仿函数greater<int> 
		//是的countSort在底层按照key值从大到小的顺序排列 则实现了高频词汇先输出
		for (auto& e : countmap){
			countSort.insert(make_pair(e.second, e.first));
		}
		vector<string> res;
		for (auto e : countSort){
			res.push_back(e.second);
			if (--k==0){
				break;
			}
		}
		return res;
	}
};