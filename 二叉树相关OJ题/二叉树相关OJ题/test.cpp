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
 606. ���ݶ����������ַ���
 ����Ҫ����ǰ������ķ�ʽ����һ��������ת����һ�������ź�������ɵ��ַ�����

 �սڵ�����һ�Կ����� "()" ��ʾ����������Ҫʡ�����в�Ӱ���ַ�����ԭʼ������֮���һ��һӳ���ϵ�Ŀ����Ŷԡ�

 ʾ�� 1:

 ����: ������: [1,2,3,4]
 1
 /   \
 2     3
 /
 4

 ���: "1(2(4))(3)"

 ����: ԭ�����ǡ�1(2(4)())(3())����
 ����ʡ�����в���Ҫ�Ŀ����Ŷ�֮��
 �����ǡ�1(2(4))(3)����
 ʾ�� 2:

 ����: ������: [1,2,3,null,4]
 1
 /   \
 2     3
 \
 4

 ���: "1(2()(4))(3)"

 ����: �͵�һ��ʾ�����ƣ�
 �������ǲ���ʡ�Ե�һ�����������ж���������֮���һ��һӳ���ϵ��
 */

 //˼·���ݹ�
class Solution {
public:
	void dfs(TreeNode* t, string& str){
		if (t == nullptr){
			return ;
		}
		str += to_string(t->val); //to_string �ǽ�Ҳ��int���͵���ֵת��Ϊchar��
		if (t->left != nullptr){
			str += '(';
			//str����+=��������
			dfs(t->left, str);
			str += ')';
		}
		//������Ŀ�ɵ� ��������Ϊ�� ��������Ϊ�� ����ȥ����������() ��Ӱ��ӳ���ϵ
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
102. �������Ĳ������
����һ�������������㷵���䰴 ������� �õ��Ľڵ�ֵ�� �������أ������ҷ������нڵ㣩��
ʾ����
��������[3,9,20,null,null,15,7],

3
/ \
9  20
/  \
15   7
�������α��������

[
[3],
[9,20],
[15,7]
]
*/
/*
˼·��������� ��Ҫһ��queue<Node*> q�Ķ���������������ڵ� ��ǰ����Ӻ���Ҫ������һ��
�ڵ������ �ҵ�˳����� �������Ƽ��ɲ�������������
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
			size_t len = q.size();//ÿһ��ĳ���
			for (size_t i = 0; i < len; ++i){
				//��һ��ĳ�����У�����һ��ĳ�����Ȼ��q.size()��֪
				TreeNode* front_ = q.front();
				q.pop();
				//��front_�ڵ��������tmp����
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
236. �������������������
����һ��������, �ҵ�����������ָ���ڵ������������ȡ�

�ٶȰٿ�������������ȵĶ���Ϊ���������и��� T ��������� p��q������������ȱ�ʾΪһ����� x������ x �� p��q �������� x ����Ⱦ����ܴ�һ���ڵ�Ҳ���������Լ������ȣ�����

���磬�������¶�����:  root = [3,5,1,6,2,0,8,null,null,7,4]

ʾ�� 1:

����: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
���: 3
����: �ڵ� 5 �ͽڵ� 1 ��������������ǽڵ� 3��
ʾ�� 2:

����: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
���: 5
����: �ڵ� 5 �ͽڵ� 4 ��������������ǽڵ� 5����Ϊ���ݶ�������������Ƚڵ����Ϊ�ڵ㱾��


˵��:

���нڵ��ֵ����Ψһ�ġ�
p��q Ϊ��ͬ�ڵ��Ҿ������ڸ����Ķ�������
*/

/*
˼·���ݹ�  
�������� ��һ���ڵ�Ϊ���������ڵ�����ȣ���ô�ض������������ڵ�һ�������ȵ��� һ�������ȵ���
���� ���Եݹ�Ѱ���������ڵ��λ���ж�������
*/

class Solution {
public:
	bool find_(TreeNode* root,TreeNode* p){
		//	Ѱ�Ҹýڵ�
		if (root == NULL){
			return false;
		}
		return root == p //�ҵ�
			|| find_(root->left,p) 
			|| find_(root->right,p);//ȥ�ұ���
	}
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == p || root == q){
			//˵��p��qĳһ����������
			return root;
		}

		bool ispleft = find_(root->left, p);
		bool isqleft = find_(root->left, q);
		bool ispright = !ispleft;
		bool isqright = !isqleft;

		if ((ispleft&&isqright) || (ispright&&isqleft)){
			//p q�ֱ��ڸýڵ������ ���ؼ���
			return root;
		}
		if (ispleft&&isqleft){
			//�������������ڵ� �ͽ�������ݹ�Ѱ�� ��ֱ���ҵ������
			return lowestCommonAncestor(root->left, p, q);
		}
		if (ispright&&isqright){
			return lowestCommonAncestor(root->right, p, q);
		}
		return NULL;
	}
};


/*
3������һ�Ŷ��������������ö���������ת����һ�������˫������Ҫ���ܴ����κ��µ�
��㣬ֻ�ܵ������ֽ��ָ���ָ��
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
		//�������
		if (cur == NULL){
			return;
		}
		func(cur->left, prev);

		//left�䵱ǰ��ָ�롣cur��ǰ������prev
		cur->left = prev;

		//left�䵱��� cur��֪���Լ��ĺ����˭
		//����prev�ĺ�̾���cur
		if (prev){
			//�����һ���ߵ�����prevΪ�� �����ж�һ��
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
105. ��ǰ��������������й��������
����һ������ǰ�������������������������

ע��:
����Լ�������û���ظ���Ԫ�ء�

���磬����

ǰ����� preorder = [3,9,20,15,7]
������� inorder = [9,3,15,20,7]
�������µĶ�������

3
/ \
9  20
/  \
15   7
*/

class Solution {
public:

	TreeNode* _buildTree( vector<int>pre, vector<int> in, int& i, int inbegin, int inend){
		//i ����ָ��pre��ָ�� inbegin��inend����in������
		if (inbegin > inend){
			//�޷�����
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
			root->left = _buildTree(pre, in, ++i, inbegin, rooti-1);//������
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
144. ��������ǰ�����
����һ������������������ ǰ�� ������

ʾ��:

����: [1,null,2,3]
1
\
2
/
3
���: [1,2,3]
����: �ݹ��㷨�ܼ򵥣������ͨ�������㷨�����
*/

/*
˼·�� �ǵݹ� ջ ǰ�������������
ģ��ݹ�Ĺ��� �Ӹ���㿪ʼ����ÿ����������ջ������������leftΪ�� ���ж������� ��Ϊ�ݹ�
�Ĺ���
*/

class Solution {
public:
	vector<int> preorderTraversal(TreeNode* root) {
		TreeNode* cur = root;
		stack<TreeNode*> s;
		vector<int> res;
		while (cur || !s.empty()){
			while (cur){
				//������·��� ��·�����ջ
				res.push_back(cur->val);
				s.push(cur);
				cur = cur->left;
			}
			//ȡջ�еĽڵ� ������������
			TreeNode* Top = s.top();
			s.pop();
			cur = Top->right;
		}
		return res;
	}
};


/*
94. ���������������
����һ���������������������� ������

ʾ��:

����: [1,null,2,3]
1
\
2
/
3

���: [1,3,2]
����: �ݹ��㷨�ܼ򵥣������ͨ�������㷨�����
*/

/*
˼·: ջ ģ��ݹ����  ��������������
*/

class Solution {
public:
	vector<int> inorderTraversal(TreeNode* root) {
		TreeNode* cur = root;
		stack<TreeNode*> s;
		vector<int> res;
		while (cur || !s.empty()){
			//��
			while (cur){
				s.push(cur);
				cur = cur->left;
			}
			//�� ��ʱ���ʵ�ǰջ��Ԫ�ص�val  
			TreeNode* Top = s.top();
			s.pop();
			res.push_back(Top->val);
			//�� ��ʱ���ʸ�ջ��Ԫ�ص�������
			cur = Top->right;
		}
		return res;
	}
};

/*
145. �������ĺ������
����һ������������������ ���� ������

ʾ��:

����: [1,null,2,3]
1
\
2
/
3

���: [3,2,1]
����: �ݹ��㷨�ܼ򵥣������ͨ�������㷨�����
*/

//˼·���ǵݹ� ջ  ���Ҹ�   ������Ҫע�⣺������һ���ڵ��������ʱ ����right�ÿ� ��Ȼ�������������ʲ���ջ���
//�����жϸýڵ�ʱ�ֻ���ʸýڵ��right�����������ѭ��


class Solution {
public:
	vector<int> postorderTraversal(TreeNode* root) {
		TreeNode* cur = root;
		stack<TreeNode*> s;
		vector<int> res;
		while (cur || !s.empty()){
			//��
			while (cur){
				s.push(cur);
				cur = cur->left;
			}
			TreeNode* Top = s.top();
			if (!(Top->right)){
				//����ýڵ���Ϊ������ʸýڵ�
				s.pop();
				res.push_back(Top->val);
			}
			else{
				//������������
				cur = Top->right;
				Top->right = NULL;
			}
		}
		return res;
	}
};