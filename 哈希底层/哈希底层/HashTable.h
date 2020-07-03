#pragma once
#include<vector>
#include<iostream>
#include<string>
using namespace std;

//闭散列法 解决哈希冲突
//namespace Close_Hash{
//	//set ->HashTable<k,k>
//	//map ->HashTable<k,pair<k,v>>
//	enum State{
//		EMPTY, //代表该位置为空
//		EXITS,//代表该位置存在值
//		DELETE,//代表该位置删除了一个值
//	};
//
//	template < class T>
//	struct HashData{
//		T _data;
//		State _state;
//	};
//
//	template < class K, class  T, class KeyofT>
//	class HashTable
//	{
//		typedef HashData<T> HashData;
//	public:
//		bool Insert(const T& d){
//			KeyofT koft;
//			//负载因子= 表中数据/表的大小 衡量哈希表满的程度
//
//			//表接近满，插入数据越容易冲突，冲突越多，效率越低
//
//			//哈希表并不是满了才增容，开放定址法中，一般负载因子到了0.7左右就要增容
//			 
//			//负载因子越小，冲突概率越低，整体效率越高，但是负载因子越小，浪费空间越大
//			//所以负载因子一般都取一个折中值
//			if (_tables.size() == 0 || _num * 10 / _tables.size() >= 7){
//				//增容
//				//增容会影响映射关系 所以我们开新的空间后，将旧表中的数据重新映射到新表
//				//释放旧表空间
//				HashTable<T,K,KeyofT> newht;
//				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
//				newht._tables.resize(newsize);
//				for (size_t i = 0; i < _tables.size(); ++i)
//				{
//					if (_tables[i]._state == EXITS){
//						newht.Insert(_tables[i]._data);
//					}	
//				}
//				_tables.swap(newht._tables);
//			}
//
//			//计算d在表当中的位置
//			size_t index = koft(d) % _tables.size();
//			while (_tables[index]._state == EXITS){
//				if (_tables[index]._data == koft(d)){
//					return false;
//				}
//				++index;
//				if (index == _tables.size()){
//					index = 0;
//				}
//			}
//			_tables[index]._data = d;
//			_tables[index]._state = EXITS;
//			_num++;
//			return true;
//		}
//
//		HashData* Find(const K& key){
//			KeyofT koft;
//			rsize_t index = key%_tables.size();
//			while (_tables[index]._state != EMPTY){
//				if (koft(_tables[index]._data) == key){
//					if (_tables[index]._state == EXITS){
//						return &_tables[index];
//					}
//					else if (_tables[index]._state == DELETE){
//						return nullptr;
//					}
//					++index;
//					if (index == _tables.size()){
//						index = 0;
//					}
//				}
//				return nullptr;
//			}
//		}
//
//		bool Erase(const K& key){
//			HashData* ret = Find(key);
//			if (ret){
//				ret->_state = DELETE;
//				--_num;
//				return true;
//			}
//			else{
//				return false;
//			}
//		}
//	private:
//		vector<HashData> _tables;
//		size_t _num = 0; //存了几个数据
//	};
//
//	template<class K>
//	struct SetKeyOfT
//	{
//		const K& operator()(const K& key){
//			return key;
//		}
//	};
//	void TestHashTable()
//	{
//		HashTable<int, int, SetKeyOfT<int>> ht;
//		ht.Insert(4);
//		ht.Insert(14);
//		ht.Insert(24);
//		ht.Insert(5);
//		ht.Insert(15);
//		ht.Insert(25);
//		ht.Insert(6);
//		ht.Insert(16);
//	}
//}


//开散列法 解决哈希冲突
namespace Opeon_Hash{
	
	template<class T>
	struct HashNode{
		T _data;
		HashNode<T>* _next;

		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};
	
	//声明一下
	template < class K, class T, class KeyOfT, class Hash>
	class HashTable;
	//迭代器
	template < class K, class T, class KeyOfT,class Hash>
	struct _HashTableIterator{
		typedef HashNode<T> Node;
		typedef _HashTableIterator<K, T, KeyOfT, Hash> Self;
		typedef HashTable<K, T, KeyOfT, Hash> HashTable;
		Node* _node;
		HashTable* _pht;

		_HashTableIterator(Node* node,HashTable* pht)
			:_node(node)
			, _pht(pht)
		{}

		//对于set
		T& operator*(){
			return _node->_data;
		}

		//对于map
		T* operator->(){
			return &_node->_data;
		}

		Self operator++()
		{
			if (_node->_next)
			{
				_node = _node->_next;
			}
			else
			{
				// 如果一个桶走完了，找到下一个桶继续遍历
				KeyOfT koft;
				size_t i = _pht->HashFunc(koft(_node->_data)) % _pht->_tables.size();
				++i;
				for (; i < _pht->_tables.size(); i++)
				{
					Node* cur = _pht->_tables[i];
					if (cur)
					{
						_node = cur;
						return *this;
					}
				}

				_node = nullptr;
			}
			return *this;
		}
		

		bool operator!=(const Self& s){
			return _node != s._node;
		}
	};

	//针对默认可以取模的类型
	template<class K>
	struct _Hash
	{
		const K& operator()(const K& key){
			return key;
		}
	};
	//针对不可以取模的类型 

	/*template<class K>
	struct _Hashstring
	{
	*/
	//由于string作为key比较常见 将其特化
	template<>
	struct _Hash<string>
	{
		size_t operator()(const string& key){
			//这里采用BKDR Hash算法去将string转换为可取模类型
			//该算法可减少碰撞 提高效率
			size_t hash = 0;
			for (size_t i = 0; i < key.size(); ++i){
				hash *= 131;
				hash += key[i];
			}
			return hash;
		}
	};

		template < class K, class T, class KeyOfT, class Hash>
		class HashTable
		{
		public:
			typedef _HashTableIterator<K, T, KeyOfT, Hash> iterator;
			typedef HashNode<T> Node;
			friend struct _HashTableIterator<K, T, KeyOfT, Hash>;
			iterator begin(){
				for (size_t i = 0; i < _tables.size(); ++i){
					if (_tables[i]){
						return iterator(_tables[i],this);
					}
				}
				return end();
			}

			iterator end(){
				return iterator(nullptr,this);
			}

			//析构
			~HashTable(){
				Clear();
			}
			void Clear(){
				for (size_t i = 0; i < _tables.size(); ++i){
					Node* cur = _tables[i];
					while (cur){
						Node* next = cur->_next;
						delete cur;
						cur = next;
					}
					_tables[i] = nullptr;
				}
			}

			size_t HashFunc(const K& data){
				//将不可以取模的类型转换为可以去摸的类型
				Hash hash; //Hash是将data的类型转换为整型的仿函数;
				return hash(data);
			}

			pair<iterator,bool> Insert(const T& data){
				KeyOfT koft;

				//如果负载因子等于1，则增容，避免大量哈希冲突
				if (_tables.size() == _num){
					vector<Node*> newtables;
					size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
					newtables.resize(newsize);
					for (size_t i = 0; i < _tables.size(); ++i){
						//将旧表中的节点取下来重新计算在新表中的位置 进行插入
						Node* cur = _tables[i];
						while (cur){
							Node* next = cur->_next;
							size_t index = HashFunc(koft(cur->_data)) % newtables.size();
							cur->_next = newtables[index];
							newtables[index] = cur;

							cur = next;
						}
						_tables[i] = nullptr;
					}
					_tables.swap(newtables);
				}

				size_t index = HashFunc(koft(data)) % _tables.size();
				Node* cur = _tables[index];
				while (cur){
					if (koft(cur->_data) == koft(data)){
						//已经有这个值了
						return make_pair(iterator(cur, this), false);
					}
					else{
						cur = cur->_next;
					}
				}
				//头插到挂的链表中(尾插也可以)
				Node* newnode = new Node(data);
				newnode->_next = _tables[index];
				_tables[index] = newnode;

				++_num;
				return make_pair(iterator(newnode, this), true);
			}

			//寻找
			Node* Find(const K& x){
				KeyOfT koft;
				size_t index = HashFunc(x) % _tables.size();
				Node* cur = _tables[index];
				while (cur){
					if (koft(cur->_data) == x){
						return cur;
					}
					cur = cur->_next;
				}
				return nullptr;
			}

			//删除
			bool Erase(const K& x){
				KeyOfT koft;
				size_t index = HashFunc(x) % _tables.size();
				Node* cur = _tables[index];
				Node* prev = nullptr;
				while (cur){
					if (koft(cur->_data) == x){
						if (prev == nullptr){
							//如果删除的是头节点
							_tables[index] = cur->_next;
						}
						else{
							prev->_next = cur->_next;
						}
						delete cur;

						return true;
					}
					prev = cur;
					cur = cur->_next;
				}
				return false;
			}
		private:
			vector<Node*> _tables;
			size_t _num = 0; //记录表中存储的数据个数
		};	
}

