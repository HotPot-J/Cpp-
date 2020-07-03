#pragma once
#include"HashTable.h"
using namespace Opeon_Hash;
using namespace std;
namespace JXY{

	template < class K, class V, class Hash = _Hash<K>>
	class unordered_map
	{
	public:
		struct MapKOfT{
			const K& operator()(const pair<K,V>& kv){
				return kv.first;
			}
		};
		typedef typename HashTable<K, pair<K, V>, MapKOfT, Hash>::iterator iterator;
		typedef typename HashTable<K, pair<K, V>, MapKOfT, Hash>::Node Node;
		iterator begin(){
			return _ht.begin();
		}

		iterator end(){
			return _ht.end();
		}
		
		Node* find(const K& key){
			return _ht.Find(key);
		}

	pair<iterator, bool>  insert(const pair<K, V>& kv){
			return _ht.Insert(kv);
		}

	V& operator[](const K& key){
		pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
		return ret.first->second;
	}

	private:
		HashTable<K, pair<K, V>, MapKOfT, Hash> _ht;
	};

	void Test_unordered_map()
	{
		//特化_Hashstring前
		//HashTable<string, string, SetKeyOfT<string>, _Hashstring<string>> ht;
		//特化后：
		unordered_map<string, string> ht;
		ht.insert(make_pair("left", "左"));
		ht.insert(make_pair("right", "右"));
		ht.insert(make_pair("prve", "前"));
		ht.insert(make_pair("rear", "后"));

		unordered_map<string, string>::iterator it = ht.begin();
		ht["rear"] = "tail";
		while (it != ht.end()){
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		
		if (ht.find("left")){
			cout << 1 << endl;
		}
	}
}
