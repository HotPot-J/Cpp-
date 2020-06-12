#define _CRT_SECURE_NO_WARNINGS 1

/*
һ���������ĸ���ṹ��
 �������
 1.һ�ö������ǽ���һ�����޼��ϣ��ü��ϻ���Ϊ�գ���������һ�����ڵ��
 �����ñ��Ϊ���������������Ķ��������
 2.ÿ���������������������������������ڶȴ���2�Ľ��
 3.������������������֮�֣��������Ĵ����ܵߵ���

 ����Ķ�������
 1.��������:һ�������������ÿһ��Ľ�������ﵽ���ֵ���������������������������
 Ҳ����˵�����һ���������Ĳ���Ϊk���ҽ������Ϊ��2^k��-1,����Ϊ��������
 2.��ȫ����������ȫ��������Ч�ʺܸߵ����ݽṹ����ȫ����������������������
 �����ġ��������Ϊk�ģ���n�����Ķ����������ҽ�����ÿһ����㶼�����Ϊ
 K�����������б�Ŵ�1��n�Ľ��--��Ӧʱ���֮Ϊ��ȫ��������Ҫע�������������
 ��һ���������ȫ��������

 �������ı�����
 1.ǰ�������������
 2.��������������
 3.������������Ҹ�
 4.�����������������ĸ��ڵ����ڲ���Ϊ1������������Ǵ����ڶ������ĸ���
 ����������ȷ��ʵ�һ������ڵ㣬Ȼ������ҷ��ʵڶ����ϵĽ�㣬������
 ������Ľ�㣬�Դ����ƣ����϶��£������������������Ľ��Ĺ��̾��ǲ�
 �������
 ���ӣ�  A
      B     C
	D   E       ǰ��:ABDEC ����BDEAC ����DEBCA ����:ABCDE
*/

/*
��������������:
 �����������ĸ��
 �����������ֳ�Ϊ��������������������һ�ſ����������Ǿ����������ʵĶ�������
 1.��������������Ϊ�գ��������������н���ֵ��С�ڸ�����ֵ��
 2.��������������Ϊ�գ��������������н���ֵ�����ڸ�����ֵ��
 3.������������Ҳ�ֱ�Ϊ����������
 ����:int a[] = {5,3,4,1,7,8,2,6,0,9}
           5
	 3           7
  1    4       6    8
 0 2                  9
 
 �����������Ĳ��ң�
   �����ڵ㲻Ϊ�գ�
      1.������ڵ�key==key ����true
	  2.������ڵ�key>����key ��������������
	  3.������ڵ�key<����key ��������������
	  ���򷵻�false

 �����������Ĳ��룺
    a����Ϊ�գ�ֱ�Ӳ��� Ȼ�󷵻�true
	b�������գ����ն��������������ʲ��Ҳ���λ�ã������½ڵ�

 ������������ɾ����
   ���Ȳ���Ԫ���Ƿ��ڶ�������������������ڣ��򷵻أ�����Ҫɾ���Ľ�����
  ��Ϊ�������������
   a.Ҫɾ���Ľ���޺��ӽ��
   b.Ҫɾ���Ľ��ֻ�����ӽ��
   c.Ҫɾ���Ľ��ֻ���Һ��ӽ��
   d.Ҫɾ���Ľ�������Һ��ӽ��
   ɾ����������:
    ���b: ɾ���ýڵ���ʹ��ɾ������˫�׽��ָ��ɾ���������ӽ��
	���c: ɾ���ýڵ���ʹ��ɾ������˫�׽��ָ��ɾ�������Һ��ӽ��
	���d: ��������������Ѱ�������µĵ�һ����㣨�ؼ�����С����������ֵ��
	������ɾ������У���������ý���ɾ�����⡣
 */

//����������������ʵ��
#include<iostream>
using namespace std;
template<class K>
struct BSTNode{
	BSTNode<K>* pleft;
	BSTNode<K>* pright;
	K _key;

	BSTNode(const K& key)
		:_key(key)
		, pleft(nullptr)
		, pright(nullptr)
	{}
};

template<class K>
class BSTree
{
	typedef BSTNode<K> Node;
public:

	//�ǵݹ����
	bool Insert(const K& key){
		if (_root == nullptr){
			//���Ϊ���� ֱ�Ӳ���
			_root = new Node(key);
			return true;
		}
		Node* cur = _root;
		Node*parent = nullptr;
		while (cur){
			if (key > cur->_key){
				//������λ��
				parent = cur;
				cur = cur->pright;
			}
			else if (key < cur->_key){
				//������λ��
				parent = cur;
				cur = cur->pleft;
			}
			else{
				//���ڶ����������������������� ���Ե����ʱ������
				return false;
			}
		}
		cur = new Node(key);
		if (cur->_key>parent->_key){
			parent->pright = cur;
		}
		else{
			parent->pleft = cur;
		}
		return true;
	}

	//�ݹ����

//�÷����ɶ��Խϲ� 
	//bool _InsertR(const K& key,Node* cur,Node* parent){
	//	if (_root == nullptr){
	//		_root = new Node(key);
	//		return true;
	//	}
	//	if (cur == nullptr){
	//		cur = new Node(key);
	//		if (cur->_key>parent->_key){
	//			parent->pright = cur;
	//		}
	//		else{
	//			parent->pleft = cur;
	//		}
	//		return true;
	//	}
	//	if (key > cur->_key){
	//		return _InsertR(key, cur->pright, cur);
	//	}
	//	else if (key<cur->_key){
	//		return _InsertR(key, cur->pleft, cur);
	//	}
	//	else{
	//		return false;
	//	}
	//}

	//void InsertR(const K& key){
	//	//����_rootΪ˽�� �������޷���ֵ ���Բ��������ķ������_root�Ĵ�ֵ
	//	Node* parent = nullptr;
	//	_InsertR(key, _root, parent);
	//}

//�Ż��ĵݹ����
	bool _InsertR(Node*& root, const K& key){
		//Nide*& root  �����&ʮ�ֹؼ� ֻ�д�����ı��� ���ܲ���Ҫ���ϱߺ����ֵ�parentȥ���Ӽ�������Ľ��
		/*
		 ���һ��
			 ����Ϊ�� rootΪ�������¿��Ľ���root �ȼ�Ϊֱ�Ӹ���_root
		 �����:
			 ������Ϊ��  root�ߵ��գ����µĽ�㣬����rootͬʱΪ��һ�㸸����/�Һ��ӵı�����
			 �¿��Ľ��root�ͺ͸�������������
		*/
		if (root == nullptr){
			root = new Node(key);
			return true;
		}
 		if (root->_key < key){
			return _InsertR(root->pright, key);
		}
		else if (root->_key>key){
			return _InsertR(root->pleft, key);
		}
		else {
			return false;
		}
	}
	void InsertR(const K& key){
		//����_rootΪ˽�� �������޷���ֵ ���Բ��������ķ������_root�Ĵ�ֵ
		Node* parent = nullptr;
		_InsertR(_root,key);
	}

	//���ҽ�� 
	Node* Find(const K& x){
		Node* cur = _root;
		while (cur){
			if (x > cur->_key){
				cur->pright;
			}
			else if (x < cur->_key){
				cur->pleft;
			}
			else{
				return cur;
			}
		}
		return nullptr;
	}

	//���ҽ��ݹ��
	Node* _FindR(const K& x,Node* root){
		if (root == nullptr){
			//û�ҵ�
			return nullptr;
		}
		if (x > root->_key){
			return _FindR(x, root->pright);
		}
		if (x < root->_key){
			return _FindR(x, root->pleft);
		}
		else{
			return root;
		}
	}

	Node* FindR(const K& x){
		_FindR(x,_root);
	}

	/*
	ɾ���������������
		1.Ҷ�ӽ�� ֱ��ɾ��
		2.ɾ��������/��Ϊ�� ʹ�ýڵ�ĸ��׽��ָ������/�Ҽ���
		3.ɾ��������Ҷ���Ϊ�գ� 
			�滻��ɾ������������������������С��㣬������ֵ���� Ȼ��ɾ�������/��С���
	*/
	bool Erase(const K& key){
		//�ҵ�key��� ��ɾ��
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur){
			if (key > cur->_key){
				parent = cur;
				cur = cur->pright;
			}
			else if (key < cur->_key){
				parent = cur;
				cur = cur->pleft;
			}
			else{
				//�ҵ��ý��
			   
				//��Ϊ��
				if (cur->pleft == nullptr){
					if (parent == nullptr){
						//˵��ɾ����
						_root = cur->pright;
					}
					else{
						if (cur == parent->pleft){
							parent->pleft = cur->pright;
						}
						else{
							parent->pright = cur->pright;
						}
					}
					delete cur;
				}
				//��Ϊ��
				else if (cur->pright == nullptr){
					if (parent == nullptr){
						//˵��ɾ����
						_root = cur->pleft;
					}
					else{
						if (cur == parent->pleft){
							parent->pleft = cur->pleft;
						}
						else{
							parent->pright = cur->pleft;
						}
					}
					delete cur;
				}
				//����Ϊ��
				else{

					//�滻ɾ��  �����������ڵ�/��������С���
					Node* minNodeParent = cur;
					Node* minNode = cur->pright;//�����������ұߵ���С���
					while (minNode->pleft){
						minNodeParent = minNode;
						minNode = minNode->pleft;
					}
					//����minNode��cur��ֵ
					swap(cur->_key, minNode->_key);

					//��ʱת��Ϊɾ��minNode
					if (minNodeParent->pright == minNode){
						minNodeParent->pright = minNode->pright;
					}
					else{
						minNodeParent->pleft = minNode->pright;
					}
					delete minNode;
				}
				return true;
			}
		}
		return false;
	}
	//�������
	void _InOrder(Node* root){
		if (root == nullptr){
			return;
		}
		_InOrder(root->pleft);
		cout << root->_key << " ";
		_InOrder(root->pright);
	}
	void InOrder(){
		_InOrder(_root);
	}
private:
	Node* _root = nullptr;
};

void TestBSTree(){
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int> b;
	for (auto e : a){
		b.InsertR(e);
	}
	b.InOrder();
	cout << endl;
	b.Erase(2);
	b.InOrder(); cout << endl;
	b.Erase(8);
	b.InOrder(); cout << endl;
	b.Erase(1);
	b.InOrder(); cout << endl;
	b.Erase(5);
	b.InOrder(); cout << endl;
}
int main(){
	TestBSTree();
	return 0;
}