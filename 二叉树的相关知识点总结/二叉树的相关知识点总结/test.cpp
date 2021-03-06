#define _CRT_SECURE_NO_WARNINGS 1

/*
一、二叉树的概念及结构：
 基本概念：
 1.一棵二叉树是结点的一个有限集合，该集合或者为空，或者是由一个根节点加
 上两棵别称为左子树和右子树的二叉树组成
 2.每个结点最多有两颗子树，即二叉树不存在度大于2的结点
 3.二叉树的子树有左右之分，其子树的次序不能颠倒。

 特殊的二叉树：
 1.满二叉树:一个二叉树，如果每一层的结点数都达到最大值，则这个二叉树就是满二叉树，
 也就是说，如果一个二叉树的层数为k，且结点总数为（2^k）-1,则其为满二叉树
 2.完全二叉树：完全二叉树的效率很高的数据结构，完全二叉树是由满二叉树而引
 出来的。对于深度为k的，有n个结点的二叉树，当且仅当其每一个结点都与深度为
 K的满二叉树中编号从1至n的结点--对应时因称之为完全二叉树。要注意的是满二叉树
 是一种特殊的完全二叉树。

 二叉树的遍历：
 1.前序遍历：根左右
 2.中序遍历：左根右
 3.后序遍历：左右根
 4.层序遍历：设二叉树的根节点所在层数为1，层序遍历就是从所在二叉树的根节
 点出发，首先访问第一层的树节点，然后从左到右访问第二层上的结点，接着是
 第三层的结点，以此类推，自上而下，自左至右逐层访问树的结点的过程就是层
 序遍历。
 例子：  A
      B     C
	D   E       前序:ABDEC 中序：BDEAC 后序：DEBCA 层序:ABCDE
*/

/*
二、二叉搜索树:
 二叉搜索树的概念：
 二叉搜索树又称为二叉排序树，它或者是一颗空树，或者是具有以下性质的二叉树：
 1.若它的左子树不为空，则左子树上所有结点的值都小于根结点的值。
 2.若它的右子树不为空，则右子树上所有结点的值都大于根结点的值。
 3.它的左右子树也分别为二叉搜索树
 例子:int a[] = {5,3,4,1,7,8,2,6,0,9}
           5
	 3           7
  1    4       6    8
 0 2                  9
 
 二叉搜索树的查找：
   若根节点不为空：
      1.如果根节点key==key 返回true
	  2.如果根节点key>查找key 在其左子树查找
	  3.如果根节点key<查找key 在其右子树查找
	  否则返回false

 二叉搜索树的插入：
    a、树为空，直接插入 然后返回true
	b、树不空，按照二叉搜索树的性质查找插入位置，插入新节点

 二叉搜索树的删除：
   首先查找元素是否在二叉搜索树，如果不存在，则返回，否则要删除的结点可能
  分为下面四种情况：
   a.要删除的结点无孩子结点
   b.要删除的结点只有左孩子结点
   c.要删除的结点只有右孩子结点
   d.要删除的结点有左、右孩子结点
   删除过程如下:
    情况b: 删除该节点且使被删除结点的双亲结点指向被删除结点的左孩子结点
	情况c: 删除该节点且使被删除结点的双亲结点指向被删除结点的右孩子结点
	情况d: 在它的右子树中寻找中序下的第一个结点（关键码最小），用它的值填
	补到被删除结点中，再来处理该结点的删除问题。
 */

//三、二叉搜索树的实现
#include<iostream>
using namespace std;
template<class T>
struct BSTNode{
	BSTNode(const T& data = T())
	:pleft(nullptr), pright(nullptr), data(data)
	{}
	BSTNode<T>* pleft;
	BSTNode<T>* pright;
	T data;
};

template<class T>
class BSTree
{
	typedef BSTNode<T> Node;
	typedef Node* PNode;
public:
	BSTree() :pRoot(nullptr)
	{}


private:
	PNode pRoot;
};
