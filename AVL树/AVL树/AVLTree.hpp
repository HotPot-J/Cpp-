#pragma once
#include<iostream>
#include<cassert>
using namespace std;
template<class K,class V>
//定义AVLTree节点
struct AVLTreeNode{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;
	int _bf;//balance factor平衡因子
    pair<K, V> _kv;

	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
		, _kv(kv)
	{}
};

template<class K,class V>

class AVLTree{
	typedef  AVLTreeNode<const K,V> Node;
public:
	bool Insert(const pair<K, V>& kv){
		if (_root == nullptr){
			//为空直接插入
			_root = new Node(kv);
			_root->_bf = 0;
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur){
			if (cur->_kv.first > kv.first){
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_kv.first < kv.first){
				parent = cur;
				cur = cur->_right;
			}
			else{
				return false;
			}
		}
		cur = new Node(kv);
		if (parent->_kv.first>kv.first){
			parent->_left = cur;
			cur->_parent = parent;
		}
		else{
			parent->_right = cur;
			cur->_parent = parent;
		}
		//更新平衡因子 
		while (parent){
			if (cur == parent->_left){
				parent->_bf--;
			}
			else if (cur == parent->_right){
				parent->_bf++;
			}
			
			if (parent->_bf == 0){
				break;
			}
			else if (abs(parent->_bf) == 1){
				cur = parent;
				parent = parent->_parent;
			}
			else if (abs(parent->_bf) == 2){
				//说明不平衡 需要旋转调整
				if (parent->_bf == 2){
					if (cur->_bf == 1){
						//左单旋
						RotateL(parent);
					}
					else if (cur->_bf == -1){
						//右左双旋
						RotateRL(parent);
					}
				}
				else if (parent->_bf == -2){
					if (cur->_bf == -1){
						//右单旋
						RotateR(parent);
					}
					else if (cur->_bf == 1){
						//左右单旋
						RotateLR(parent);
					}
				}
			}
			else{
				assert(false);
			}
		}
		return true;
	}

	//左单旋
	void RotateL(Node* parent){ 
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		
		parent->_right = subRL;
		if (subRL){
			//防止subRL为空
			subRL->_parent = parent;
		}
		subR->_left = parent;
		
		//将parent的_parent保留下来
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (parent == _root){
			//如果parent是根
			_root = subR;
			subR->_parent = nullptr;
		}
		else{
			if (ppNode->_left == parent){
				ppNode->_left = subR;
			}
			else{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}

	}

	//右单旋
	void RotateR(Node* parent){
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		
		parent->_left = subLR;

		if (subLR){
			subLR->_parent = parent;
		}

		subL->_right = parent;

		Node* ppNode = parent;
		parent->_parent = subL;
		if (parent == _root){
			_root = subL;
			subL->_parent = nullptr;
		}
		else{
			if (ppNode->_left == parent){
				ppNode->_left = subL;
			}
			else{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
	}

	//左右双旋
	void RotateLR(Node* parent){
		RotateL(parent->_left);//先左单旋转
		RotateR(parent);//再右单旋
	}

	//右左双旋
	void RotateRL(Node* parent){
		RotateR(parent->_right);//先右单旋
		RotateR(parent);//再左单旋
	}
private:
	Node* _root = nullptr;

};