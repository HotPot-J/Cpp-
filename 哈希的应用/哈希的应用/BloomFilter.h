#pragma once
#include"BitSet.h"
using namespace jxy;
using namespace std;

namespace jxy{
	struct BKDR_Hash{
		size_t operator()(const string& str){
			size_t hash = 0;
			size_t len = str.size();
			for (size_t i = 0; i < len; ++i){
				hash *= 131;
				hash += str[i];
			}
			return hash;
		}
	};

	struct RS_Hash{
		size_t operator()(const string& str){
			size_t hash = 0;
			size_t len = str.size();
			size_t magic = 63689;
			for (size_t i = 0; i < len; ++i){
				hash *= magic;
				hash += str[i];
				magic *= 378551;
			}
			return hash;
		}
	};

	struct SDBM_Hash{
		size_t operator()(const string& str){
			size_t hash = 0;
			size_t len = str.size();
			for (size_t i = 0; i < len; ++i){
				hash *= 65599;
				hash += str[i];
			}
			return hash;
		}
	};

	template<class K = string, class Hash1 = BKDR_Hash, class Hash2 = RS_Hash, class Hash3 = SDBM_Hash>
	class Bloomfilter{
	public:
		Bloomfilter(size_t num)
			:_bs(num * 5)
			, _N(num * 5)
		{}

		void set(const K& key){
			
			size_t index1 = Hash1()(key)%_N;
			size_t index2 = Hash2()(key)%_N;
			size_t index3 = Hash3()(key) % _N;

			_bs.set(index1);
			_bs.set(index2);
			_bs.set(index3);
		}

		bool test(const K& key){
			size_t index1 = Hash1()(key) % _N;
			if (!_bs.have(index1)){
				return false;
			}
			size_t index2 = Hash2()(key) % _N;
			if (!_bs.have(index2)){
				return false;
			}
			size_t index3 = Hash3()(key) % _N;
			if (!_bs.have(index3)){
				return false;
			}
			return true;  //仍然存在误判 （无法避免冲突）
			//但是如果key不在，返回的false一定是正确的判断
		}

	private:
		Bitset _bs; //位图
		size_t _N;
	};

	void _testBlommFilter(){
		Bloomfilter<string> bf(100);
		bf.set("abcd");
		bf.set("acbd");
		bf.set("cdab");

		cout << bf.test("abcd") << endl;
		cout << bf.test("acbd") << endl;
		cout << bf.test("accd") << endl;
		
	}
}