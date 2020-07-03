#pragma once
#include<vector>
#include<iostream>
#include<string>
using namespace std;

//��ɢ�з� �����ϣ��ͻ
//namespace Close_Hash{
//	//set ->HashTable<k,k>
//	//map ->HashTable<k,pair<k,v>>
//	enum State{
//		EMPTY, //�����λ��Ϊ��
//		EXITS,//�����λ�ô���ֵ
//		DELETE,//�����λ��ɾ����һ��ֵ
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
//			//��������= ��������/��Ĵ�С ������ϣ�����ĳ̶�
//
//			//��ӽ�������������Խ���׳�ͻ����ͻԽ�࣬Ч��Խ��
//
//			//��ϣ���������˲����ݣ����Ŷ�ַ���У�һ�㸺�����ӵ���0.7���Ҿ�Ҫ����
//			 
//			//��������ԽС����ͻ����Խ�ͣ�����Ч��Խ�ߣ����Ǹ�������ԽС���˷ѿռ�Խ��
//			//���Ը�������һ�㶼ȡһ������ֵ
//			if (_tables.size() == 0 || _num * 10 / _tables.size() >= 7){
//				//����
//				//���ݻ�Ӱ��ӳ���ϵ �������ǿ��µĿռ�󣬽��ɱ��е���������ӳ�䵽�±�
//				//�ͷžɱ�ռ�
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
//			//����d�ڱ��е�λ��
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
//		size_t _num = 0; //���˼�������
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


//��ɢ�з� �����ϣ��ͻ
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
	
	//����һ��
	template < class K, class T, class KeyOfT, class Hash>
	class HashTable;
	//������
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

		//����set
		T& operator*(){
			return _node->_data;
		}

		//����map
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
				// ���һ��Ͱ�����ˣ��ҵ���һ��Ͱ��������
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

	//���Ĭ�Ͽ���ȡģ������
	template<class K>
	struct _Hash
	{
		const K& operator()(const K& key){
			return key;
		}
	};
	//��Բ�����ȡģ������ 

	/*template<class K>
	struct _Hashstring
	{
	*/
	//����string��Ϊkey�Ƚϳ��� �����ػ�
	template<>
	struct _Hash<string>
	{
		size_t operator()(const string& key){
			//�������BKDR Hash�㷨ȥ��stringת��Ϊ��ȡģ����
			//���㷨�ɼ�����ײ ���Ч��
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

			//����
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
				//��������ȡģ������ת��Ϊ����ȥ��������
				Hash hash; //Hash�ǽ�data������ת��Ϊ���͵ķº���;
				return hash(data);
			}

			pair<iterator,bool> Insert(const T& data){
				KeyOfT koft;

				//����������ӵ���1�������ݣ����������ϣ��ͻ
				if (_tables.size() == _num){
					vector<Node*> newtables;
					size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
					newtables.resize(newsize);
					for (size_t i = 0; i < _tables.size(); ++i){
						//���ɱ��еĽڵ�ȡ�������¼������±��е�λ�� ���в���
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
						//�Ѿ������ֵ��
						return make_pair(iterator(cur, this), false);
					}
					else{
						cur = cur->_next;
					}
				}
				//ͷ�嵽�ҵ�������(β��Ҳ����)
				Node* newnode = new Node(data);
				newnode->_next = _tables[index];
				_tables[index] = newnode;

				++_num;
				return make_pair(iterator(newnode, this), true);
			}

			//Ѱ��
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

			//ɾ��
			bool Erase(const K& x){
				KeyOfT koft;
				size_t index = HashFunc(x) % _tables.size();
				Node* cur = _tables[index];
				Node* prev = nullptr;
				while (cur){
					if (koft(cur->_data) == x){
						if (prev == nullptr){
							//���ɾ������ͷ�ڵ�
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
			size_t _num = 0; //��¼���д洢�����ݸ���
		};	
}

