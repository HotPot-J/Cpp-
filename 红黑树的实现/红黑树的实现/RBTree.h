#pragma once
#include<iostream>
using namespace std;
enum Colour
{
	BLACK,
	RED,
};
template < class K, class  V>

struct RBTreeNode
{
	RBTreeNode<K,V>* _left;
	RBTreeNode<K,V>* _right;
	RBTreeNode<K,V>* _parent;
	
	pair<K, V> _kv;

	Colour _col;
	RBTreeNode(const pair<K,V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _col(RED)
	{}

};

template < class K, class V>
class RBTree{
	typedef RBTreeNode<K,V> Node;
public:
	bool Insert(const pair<K,V>& kv){
		//1.先按照搜索树的规则进行插入
		if (_root == nullptr){
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur){
			if (cur->_kv.first < kv.first){
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first>kv.first){
				parent = cur;
				cur = cur->_left;
			}
			else{
				return false;
			}
		}
		cur = new Node(kv);
		if (parent->_kv.first < kv.first){
			parent->_right = cur;
			cur->_parent = parent;
		}
		else{
			parent->_left = cur;
			cur->_parent = parent;
		}
		//新增红节点
		cur->_col = RED;

		//调整颜色
		while (parent&&parent->_col == RED){
			//红黑树的条件关键看叔叔
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent){
				Node* uncle = grandfather->_right;
				//情况一 uncle存在且为红
				if (uncle&&uncle->_col == RED){
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;
					//继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else{
					//情况2/3 :uncle不存在 或者为黑
					//旋转（单旋/双旋）+变色
					if (cur == parent->_right){
						//双旋 -》变为单旋
						RotateL(parent);
						//交换指针
						swap(parent, cur);
					}
					//第二种情况(ps:有可能是第三种变过来的)
					RotateR(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
					//这里之所以可以直接break 是因为该推导过程将
					//parent指针指向的节点最终旋转到了原先grandfather指向的节点的位置上且将parent
					//置为black 对该路径的红黑树性质并无影响，所以不必继续向上调整（即使不break while（parent->_col==RED）循环也进不去）
					break;
				}
			}
			else{
				//grandfather->_right == parent
				Node* uncle = grandfather->_left;
				if (uncle&&uncle->_col == RED){
					//情况一
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;
					//继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				else{
					if (cur == parent->_left){
						//右单旋
						RotateR(parent);
						//交换指针
						swap(cur, parent);
					}
					RotateL(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
					break;
				}
			}
		}
		_root->_col = BLACK;//保证根一定为黑色
		return true;
	}

	//左旋 
	void RotateL(Node* parent){
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL){
			subRL->_parent = parent;
		}
		subR->_left = parent;

		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (parent == _root){
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

		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (ppNode == _root){
			_root = subL;
			subL->_parent = nullptr;
		}
		else{
			if (parent == ppNode->_left){
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
	}

	//中序遍历
	void _InOrder(Node* root)
	{
		if (root == nullptr){
			return;
		}
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	void InOrder(){
		_InOrder(_root);
	}

	Node* _Find(const K& key, Node* root){
		if (root == nullptr){
			return nullptr;
		}
		if (root->_kv.first == key){
			return root;
		}
		if (key < root->_kv.first){
			return _Find(key, root->_left);
		}
		else{
			return _Find(key, root->_right);
		}
	}
	//查找
	Node* Find(const K& key){
		return _Find(key, _root);
	}
private:
	Node* _root = nullptr;
};