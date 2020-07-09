/*
位图的实现
*/

#pragma once;
#include<iostream>
#include<vector>
#include<string>
using namespace std;

namespace jxy{

	class Bitset{
	public:
		Bitset(size_t n){
			//一个int类型可以表示32个数字 +1为了保证/后被舍弃的位数
			_bits.resize(n / 32 + 1, 0);
		}

		void set(size_t x){
			//寻找x对应的具体位数是第几个数据的第几位
			size_t index = x / 32;
			size_t pos = x % 32;

			//将对应位置1 
			_bits[index] |= (1 << pos);
		}

		void reset(size_t x){
			size_t index = x / 32;
			size_t pos = x % 32;
			if (have(x)){
				//将对应位置置0
				_bits[index] ^= (1 << pos);
			}

		}

		bool have(size_t x){
			//判断x是否存在
			size_t index = x / 32;
			size_t pos = x % 32;

			return _bits[index]&(1 << pos) ;	
		}
	
	private:
		vector<int> _bits;
		size_t _num;  //记录存了多少个数字
	};

	void _testBitSit(){
		Bitset a(100);
		a.set(99);
		a.set(100);
		a.set(98);
		a.set(96);
		a.set(97);
		a.set(95);
		if (a.have(96)){
			cout << "有 96" << endl << "删除96" << endl;
		}
		a.reset(96);
		if (!a.have(96)){
			cout << "无 96" << endl;
		}
	}
}
