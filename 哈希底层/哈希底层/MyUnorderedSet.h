#pragma once
#include"HashTable.h"
using namespace Opeon_Hash;
namespace JXY{

	template < class K, class Hash = _Hash<K>>
	class unordered_set
	{
	private:

		struct SetKOfT{
			const K& operator()(const K& k){
				return k;
			}
		};
	public:
		typedef typename HashTable<K, K, SetKOfT, Hash>::iterator iterator;
	
		iterator begin(){
			return _ht.begin();
		}

		iterator end(){
			return _ht.end();
		}
		//插入
	 pair<iterator, bool>  insert(const K& k){
			return _ht.Insert(k);
		}

	private:
		HashTable<K, K, SetKOfT,Hash> _ht;
	};

	void Test_unordered_set()
	{
		//特化_Hashstring前
		//HashTable<string, string, SetKeyOfT<string>, _Hashstring<string>> ht;
		//特化后：
		unordered_set<string> ht;
		ht.insert("4");
		ht.insert("14");
		ht.insert("24");
		ht.insert("5");
		ht.insert("15");
		ht.insert("25");
		ht.insert("6");
		ht.insert("16");
		ht.insert("17");
		ht.insert("26");
		ht.insert("7");
		ht.insert("19");
	}
}