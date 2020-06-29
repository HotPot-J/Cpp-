#pragma once
#include"RBTree_.h"

namespace Jxy
{
	template < class K,class V >
	class map
	{
	public:
		//仿函数
		struct MapKeyOfT{
			const K& operator()(const pair<K, V>& kv){
				return kv.first;
			}
		};

		typedef typename RBTree<K, pair<K, V>, MapKeyOfT > ::iterator iterator;
		iterator begin(){
			return _t.begin();
		} 

		iterator end(){
			return _t.end();
		} 

		pair<iterator, bool> Insert(const pair<K, V>& kv){
			return _t.Insert(kv);
		}

		V& operator[](const K& key){
			//借助插入去实现[]  底层插入返回值：pair<iterator,bool> 再加上无则插入 有则返回那个位置的迭代器的性质
			pair<iterator,bool> ret= _t.Insert(make_pair(key, V()));
			return (ret.first)->second;
		}
	private:
		RBTree<K, pair<K, V>,MapKeyOfT> _t;
	};
	void test_map(){
		map<int, int> m;
		m.Insert(make_pair(1, 1));
		m.Insert(make_pair(3, 3));
		m.Insert(make_pair(10, 10));
		m.Insert(make_pair(5, 5));
		m.Insert(make_pair(6, 6));
		map<int,int>::iterator it = m.begin();
		while (it != m.end()){
			cout << it->first << ": " << it->second << endl;
			++it;
		}

		string strs[] = { "黄瓜", "香蕉", "葡萄", "黄瓜", "黄瓜" };
		map<string, int> countMap;
		for (auto& str : strs){ 
			countMap[str]++;
		}

		for (auto e : countMap){
			cout << e.first << ": " << e.second << endl;
		}
	}  
}