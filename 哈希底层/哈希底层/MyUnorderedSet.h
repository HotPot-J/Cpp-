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
		//����
	 pair<iterator, bool>  insert(const K& k){
			return _ht.Insert(k);
		}

	private:
		HashTable<K, K, SetKOfT,Hash> _ht;
	};

	void Test_unordered_set()
	{
		//�ػ�_Hashstringǰ
		//HashTable<string, string, SetKeyOfT<string>, _Hashstring<string>> ht;
		//�ػ���
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