#pragma once
#include"RBTree_.h"

namespace Jxy
{
	template < class K>
	class set
	{
	public:
		struct SetKeyOfT{
			const K& operator()(const K& k){
				return k;
			}
		};

		typedef typename RBTree<K, K, SetKeyOfT>::iterator iterator;
		iterator begin(){
			return _t.begin();
		}

		iterator end(){
			return _t.end();
		}

		pair<iterator, bool> Insert(const K& k){
			return _t.Insert(k);
		}
	private:
		RBTree<K, K,SetKeyOfT> _t;
	};
	void test_set(){
		set<int> s;
		s.Insert(1);
		s.Insert(3);
		s.Insert(5);
		s.Insert(4);
		s.Insert(2);

		set<int>::iterator it = s.begin();
		while (it != s.end()){
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
}