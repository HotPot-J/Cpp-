#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
using namespace std;


 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };


 /*
 606. 根据二叉树创建字符串
 你需要采用前序遍历的方式，将一个二叉树转换成一个由括号和整数组成的字符串。

 空节点则用一对空括号 "()" 表示。而且你需要省略所有不影响字符串与原始二叉树之间的一对一映射关系的空括号对。

 示例 1:

 输入: 二叉树: [1,2,3,4]
 1
 /   \
 2     3
 /
 4

 输出: "1(2(4))(3)"

 解释: 原本将是“1(2(4)())(3())”，
 在你省略所有不必要的空括号对之后，
 它将是“1(2(4))(3)”。
 示例 2:

 输入: 二叉树: [1,2,3,null,4]
 1
 /   \
 2     3
 \
 4

 输出: "1(2()(4))(3)"

 解释: 和第一个示例相似，
 除了我们不能省略第一个对括号来中断输入和输出之间的一对一映射关系。
 */

 //思路：递归
class Solution {
public:
	void dfs(TreeNode* t, string& str){
		if (t == nullptr){
			return ;
		}
		str += to_string(t->val); //to_string 是将也给int类型的数值转化为char型
		if (t->left != nullptr){
			str += '(';
			//str继续+=其左子树
			dfs(t->left, str);
			str += ')';
		}
		//分析题目可得 当左子树为空 右子树不为空 不能去掉左子树的() 会影响映射关系
		if (t->left == nullptr&&t->right != nullptr){
			str += "()";
		}

		if (t->right){
			str += '(';
			dfs(t->right,str);
			str += ')';
		}
	}
	string tree2str(TreeNode* t) {
		string str;
		dfs(t, str);
		return str;
	}
};

/*
102. 二叉树的层序遍历
给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。
示例：
二叉树：[3,9,20,null,null,15,7],

3
/ \
9  20
/  \
15   7
返回其层次遍历结果：

[
[3],
[9,20],
[15,7]
]
*/
/*
思路：层序遍历 需要一个queue<Node*> q的队列来保存二叉树节点 当前层入队后需要把其下一层
节点根据左 右的顺序入队 依次类推即可层序遍历完二叉树
*/
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		queue<TreeNode*> q;
		vector<vector<int>> res;
		if (root){
			q.push(root);
		}
		while (!q.empty()){
			vector<int> tmp;
			size_t len = q.size();//每一层的长度
			for (size_t i = 0; i < len; ++i){
				//当一层的出完队列，则下一层的长度自然右q.size()可知
				TreeNode* front_ = q.front();
				q.pop();
				//让front_节点的数据入tmp数组
				tmp.push_back(front_->val);
				if (front_->left){
					q.push(front_->left);
				}
				if (front_->right){
					q.push(front_->right);
				}
			}
			res.push_back(tmp);
		}
		return res;
	}
};

/*
236. 二叉树的最近公共祖先
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

例如，给定如下二叉树:  root = [3,5,1,6,2,0,8,null,null,7,4]

示例 1:

输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出: 3
解释: 节点 5 和节点 1 的最近公共祖先是节点 3。
示例 2:

输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出: 5
解释: 节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。


说明:

所有节点的值都是唯一的。
p、q 为不同节点且均存在于给定的二叉树中
*/

/*
思路：递归  
根据题意 当一个节点为另外两个节点的祖先，那么必定满足这两个节点一个在祖先的左 一个在祖先的右
所以 可以递归寻找这两个节点的位置判断其左右
*/

class Solution {
public:
	bool find_(TreeNode* root,TreeNode* p){
		//	寻找该节点
		if (root == NULL){
			return false;
		}
		return root == p //找到
			|| find_(root->left,p) 
			|| find_(root->right,p);//去右边找
	}
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == p || root == q){
			//说明p和q某一个就是祖先
			return root;
		}

		bool ispleft = find_(root->left, p);
		bool isqleft = find_(root->left, q);
		bool ispright = !ispleft;
		bool isqright = !isqleft;

		if ((ispleft&&isqright) || (ispright&&isqleft)){
			//p q分别在该节点的左右 返回即可
			return root;
		}
		if (ispleft&&isqleft){
			//如果左边有两个节点 就接着向左递归寻找 ，直到找到最近的
			return lowestCommonAncestor(root->left, p, q);
		}
		if (ispright&&isqright){
			return lowestCommonAncestor(root->right, p, q);
		}
		return NULL;
	}
};


/*
3、输入一颗二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的
结点，只能调整树种结点指针的指向
*/


struct TreeNode {
int val;
struct TreeNode *left;
struct TreeNode *right;
TreeNode(int x) :
val(x), left(NULL), right(NULL) {
}
};
typedef struct TreeNode TreeNode;

class Solution {
public:
	void func(TreeNode* cur, TreeNode*& prev){
		//中序遍历
		if (cur == NULL){
			return;
		}
		func(cur->left, prev);

		//left充当前驱指针。cur的前驱就死prev
		cur->left = prev;

		//left充当后继 cur不知道自己的后继是谁
		//但是prev的后继就死cur
		if (prev){
			//程序第一次走到这里prev为空 所以判断一下
			prev->right = cur;
		}
		prev = cur;
		func(cur->right, prev);
	}
	TreeNode* Convert(TreeNode* pRootOfTree)
	{
		TreeNode* prev = NULL;
		func(pRootOfTree, prev);
		TreeNode* head = pRootOfTree;
		while (head&&head->left){
			head = head->left;
		}
		return head;
	}
};


/*
105. 从前序与中序遍历序列构造二叉树
根据一棵树的前序遍历与中序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

例如，给出

前序遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
返回如下的二叉树：

3
/ \
9  20
/  \
15   7
*/

class Solution {
public:

	TreeNode* _buildTree( vector<int>pre, vector<int> in, int& i, int inbegin, int inend){
		//i 代表指向pre的指针 inbegin和inend代表in的区间
		if (inbegin > inend){
			//无法构建
			return NULL;
		}
		TreeNode* root = new TreeNode(pre[i]);

		int rooti = inbegin;
		while (rooti<=inend){
			if (in[rooti] == pre[i]){
				break;
			}
			++rooti;
		}
		if (inbegin <= rooti - 1){
			root->left = _buildTree(pre, in, ++i, inbegin, rooti-1);//左区间
		}
		else{
			root->left = NULL;
		}

		if (inend >= rooti + 1){
			root->right = _buildTree(pre, in, ++i, rooti+1, inend);
		}
		else{
			root->right = NULL;
		}
		return root;
	}
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		int i = 0;
		return _buildTree(preorder,inorder, i, 0, inorder.size() - 1);
	}
};


/*
144. 二叉树的前序遍历
给定一个二叉树，返回它的 前序 遍历。

示例:

输入: [1,null,2,3]
1
\
2
/
3
输出: [1,2,3]
进阶: 递归算法很简单，你可以通过迭代算法完成吗？
*/

/*
思路： 非递归 栈 前序遍历：根左右
模拟递归的过程 从根结点开始，让每个左子树入栈，当左子树的left为空 再判断右子树 即为递归
的过程
*/

class Solution {
public:
	vector<int> preorderTraversal(TreeNode* root) {
		TreeNode* cur = root;
		stack<TreeNode*> s;
		vector<int> res;
		while (cur || !s.empty()){
			while (cur){
				//访问左路结点 左路结点入栈
				res.push_back(cur->val);
				s.push(cur);
				cur = cur->left;
			}
			//取栈中的节点 访问其右子树
			TreeNode* Top = s.top();
			s.pop();
			cur = Top->right;
		}
		return res;
	}
};


/*
94. 二叉树的中序遍历
给定一个二叉树，返回它的中序 遍历。

示例:

输入: [1,null,2,3]
1
\
2
/
3

输出: [1,3,2]
进阶: 递归算法很简单，你可以通过迭代算法完成吗？
*/

/*
思路: 栈 模拟递归过程  中序遍历：左根右
*/

class Solution {
public:
	vector<int> inorderTraversal(TreeNode* root) {
		TreeNode* cur = root;
		stack<TreeNode*> s;
		vector<int> res;
		while (cur || !s.empty()){
			//左
			while (cur){
				s.push(cur);
				cur = cur->left;
			}
			//根 此时访问当前栈顶元素的val  
			TreeNode* Top = s.top();
			s.pop();
			res.push_back(Top->val);
			//右 此时访问该栈顶元素的右子树
			cur = Top->right;
		}
		return res;
	}
};

/*
145. 二叉树的后序遍历
给定一个二叉树，返回它的 后序 遍历。

示例:

输入: [1,null,2,3]
1
\
2
/
3

输出: [3,2,1]
进阶: 递归算法很简单，你可以通过迭代算法完成吗？
*/

//思路：非递归 栈  左右根   这里需要注意：当访问一个节点的右子树时 将其right置空 不然当其右子树访问并出栈完成
//重新判断该节点时又会访问该节点的right，则造成无限循环


class Solution {
public:
	vector<int> postorderTraversal(TreeNode* root) {
		TreeNode* cur = root;
		stack<TreeNode*> s;
		vector<int> res;
		while (cur || !s.empty()){
			//左
			while (cur){
				s.push(cur);
				cur = cur->left;
			}
			TreeNode* Top = s.top();
			if (!(Top->right)){
				//如果该节点右为空则访问该节点
				s.pop();
				res.push_back(Top->val);
			}
			else{
				//访问其右子树
				cur = Top->right;
				Top->right = NULL;
			}
		}
		return res;
	}
};