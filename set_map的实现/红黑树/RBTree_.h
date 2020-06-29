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
	//����set
	T& operator*(){
		return _node->_data;
	}
	
	//����map
	T* operator->(){
		return &_node->_data;
	}

	Self& operator++(){
		//�Ҳ�Ϊ�� �������һ��������������������ڵ�
		//��Ϊ�� ��ʾ_node���ڵ�����������ɣ���һ���ڵ�������������,����·�������Һ�������������Ǹ�����
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
//K_T �Ƿº��� ����ȡ��map/set�������Ƚϴ�С��ֵ
//set��K�Ƚϣ���mapʹ��pair�е�K���Ƚ� ����ʵ�ּ�MyMap.h MySet.h
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
		//1.�Ȱ����������Ĺ�����в���
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
		Node* newnode = cur; //���ڽ������ĵ��� cur����ָ�������ڵ� ����������Ҫ����¼
		if (koft(parent->_data) < koft(data)){
			parent->_right = cur;
			cur->_parent = parent;
		}
		else{
			parent->_left = cur;
			cur->_parent = parent;
		}
		//������ڵ�
		cur->_col = RED;

		//������ɫ
		while (parent&&parent->_col == RED){
			//������������ؼ�������
			Node* grandfather = parent->_parent;
			if (grandfather->_left == parent){
				Node* uncle = grandfather->_right;
				//���һ uncle������Ϊ��
				if (uncle&&uncle->_col == RED){
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;
					//�������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else{
					//���2/3 :uncle������ ����Ϊ��
					//��ת������/˫����+��ɫ
					if (cur == parent->_right){
						//˫�� -����Ϊ����
						RotateL(parent);
						//����ָ��
						swap(parent, cur);
					}
					//�ڶ������(ps:�п����ǵ����ֱ������)
					RotateR(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
					//����֮���Կ���ֱ��break ����Ϊ���Ƶ����̽�
					//parentָ��ָ��Ľڵ�������ת����ԭ��grandfatherָ��Ľڵ��λ�����ҽ�parent
					//��Ϊblack �Ը�·���ĺ�������ʲ���Ӱ�죬���Բ��ؼ������ϵ�������ʹ��break while��parent->_col==RED��ѭ��Ҳ����ȥ��
					break;
				}
			}
			else{
				//grandfather->_right == parent
				Node* uncle = grandfather->_left;
				if (uncle&&uncle->_col == RED){
					//���һ
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfather->_col = RED;
					//�������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				else{
					if (cur == parent->_left){
						//�ҵ���
						RotateR(parent);
						//����ָ��
						swap(cur, parent);
					}
					RotateL(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
					break;
				}
			}
		}
		_root->_col = BLACK;//��֤��һ��Ϊ��ɫ
		return make_pair(iterator(newnode), true);
	}

	//���� 
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

	//�ҵ���
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
	
	//�������
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

	//����
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
