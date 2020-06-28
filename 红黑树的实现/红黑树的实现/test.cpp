#define _CRT_SECURE_NO_WARNINGS 1
#include"RBTree.h"
void TestRBTree(){
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	RBTree<int, int> t;
	for (auto e : a){
		t.Insert(make_pair(e, e));
	}
	t.InOrder();
	if (t.Find(4)){
		cout << 1 << endl;
	}
	if (!t.Find(18)){
		cout << 2 << endl;
	}
}
int main(){
	TestRBTree();
	return 0;
}