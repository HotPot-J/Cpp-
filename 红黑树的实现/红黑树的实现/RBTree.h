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
		//1.�Ȱ����������Ĺ�����в���
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
		return true;
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

	//�������
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
	//����
	Node* Find(const K& key){
		return _Find(key, _root);
	}
private:
	Node* _root = nullptr;
};