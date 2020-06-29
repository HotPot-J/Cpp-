#pragma once
#include<iostream>
#include<string>
using namespace std;
enum Colour
{
	BLACK,
	RED,
};
template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	T _data;

	Colour _col;
	RBTreeNode(const T& data)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _col(RED)
	{}

}; 
template<class T>
struct _TreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef _TreeIterator<T> Self;
	Node* _node;
	
	_TreeIterator(Node* node)
		:_node(node)
	{}
	//对于set
	T& operator*(){
		return _node->_data;
	}
	
	//对于map
	T* operator->(){
		return &_node->_data;
	}

	Self& operator++(){
		//右不为空 中序的下一个就是其右子树的最左节点
		//右为空 表示_node所在的子树访问完成，下一个节点在其祖先中找,沿着路径往上找孩子是他的左的那个祖先
		if (_node->_right){
			Node* subLeft = _node->_right;
			while (subLeft->_left){
				subLeft = subLeft->_left;
			}
			_node = subLeft;
		}
		else{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent&&cur==parent->_right){
				cur = cur->_parent;
				parent = parent->_parent;
			}
			_node = parent;
		}
		return *this;
	}

	Self& operator--(){
		return *this;
	}

	bool operator!=(const Self& s){
		return _node != s._node;
	}
};
template < class K, class T, class K_T>
//K_T 是仿函数 用来取出map/set中用来比较大小的值
//set用K比较，而map使用pair中的K来比较 具体实现见MyMap.h MySet.h
class RBTree{
	typedef RBTreeNode<T> Node;
public:
	typedef _TreeIterator<T>  iterator;
	iterator begin(){
		Node* cur = _root;
		while (cur&&cur->_left){
			cur = cur->_left;
		}
		return iterator(cur);
	}
	iterator end(){
		return iterator(nullptr);
	}
	pair<iterator,bool> Insert(const T& data){
		//1.先按照搜索树的规则进行插入
		if (_root == nullptr){
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(iterator(_root),true);
		}
		K_T koft;
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur){
			if (koft(cur->_data) < koft(data)){
				parent = cur;
				cur = cur->_right;
			}
			else if (koft(cur->_data)>koft(data)){
				parent = cur;
				cur = cur->_left;
			}
			else{
				return make_pair(iterator(cur), false);
			}
		}
		cur = new Node(data);
		Node* newnode = cur; //由于接下来的调整 cur不再指向新增节点 所以这里需要做记录
		if (koft(parent->_data) < koft(data)){
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
		return make_pair(iterator(newnode), true);
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

		if (parent  == _root){
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
		//cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	void InOrder(){
		_InOrder(_root);
	}

	//查找
	iterator* Find(const K& key){
		K_T koft;
		Node* cur = _root;
		while (cur){
			if (koft(cur->_data) < koft(data)){
				cur = cur->_right; 
			}
			else if (koft(cur->_data) > koft(data)){
				cur = cur->_left;
			}
			else{
				return iterator(cur);
			}
		}
		return iterator(nullptr);
	}
private:
	Node* _root = nullptr;
};
