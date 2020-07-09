/*
λͼ��ʵ��
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
			//һ��int���Ϳ��Ա�ʾ32������ +1Ϊ�˱�֤/��������λ��
			_bits.resize(n / 32 + 1, 0);
		}

		void set(size_t x){
			//Ѱ��x��Ӧ�ľ���λ���ǵڼ������ݵĵڼ�λ
			size_t index = x / 32;
			size_t pos = x % 32;

			//����Ӧλ��1 
			_bits[index] |= (1 << pos);
		}

		void reset(size_t x){
			size_t index = x / 32;
			size_t pos = x % 32;
			if (have(x)){
				//����Ӧλ����0
				_bits[index] ^= (1 << pos);
			}

		}

		bool have(size_t x){
			//�ж�x�Ƿ����
			size_t index = x / 32;
			size_t pos = x % 32;

			return _bits[index]&(1 << pos) ;	
		}
	
	private:
		vector<int> _bits;
		size_t _num;  //��¼���˶��ٸ�����
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
			cout << "�� 96" << endl << "ɾ��96" << endl;
		}
		a.reset(96);
		if (!a.have(96)){
			cout << "�� 96" << endl;
		}
	}
}
