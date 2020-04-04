#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
/*
һ��unordered_map���ܣ�
  1.unordered_map�Ǵ洢<key��value>��ֵ�ԵĹ���ʽ������������ͨ��keys��
  �ٵ������������Ӧ��value��
  2.��unordered_map�У���ֵͨ������Ψһ�ı�ʶԪ�أ���ӳ��ֵ��һ������
  ��������˼�����������ӳ��ֵ�����Ϳ��ܲ�ͬ��
  3.���ڲ���unordered_mapû�ж�<key��value>�����κ��ض���˳������Ϊ��
  ���ڳ�����Χ���ҵ�key����Ӧ��value��unordered_map����ͬ��ϣֵ�ļ�ֵ��
  ������ͬ��Ͱ�С�
  4.unordered_map����ͨ��key���ʵ���Ԫ�ر�map�죬����ͨ���ڱ���Ԫ���Ӽ�
  �ķ�Χ��������Ч�ʽϵ͡�
  5.unordered_mapʵ����ֱ�ӷ��ʲ�����(operator[])��������ʹ��key��Ϊ����
  ֱ�ӷ���value��
  6.���ĵ�������ǰ�������
*/

/*
����unordered_map�Ľӿ�˵��
1.���죺
unordered_map ���첻ͬ��ʽ��unordered_map����
2.������
 bool empty()const ���unordered_map�Ƿ�Ϊ��
 size_t size()const ��ȡunordered_map����ЧԪ�ظ���
3.��������
  begin
  end
  cbegin
  cend
4.Ԫ�ط��ʣ�
 operator[] ����key��Ӧ��value��û��һ��Ĭ��ֵ
5.unordered_map�Ĳ�ѯ
iterator find(const K& key)  ����key�ڹ�ϣͰ�е�λ��
size_t count(const K& key) ���ع�ϣͰ�йؼ���Ϊkey�ļ�ֵ�Եĸ���
6.�޸Ĳ���
 insert �������в����ֵ��
 erase ɾ�������еļ�ֵ��
 void clear() ��������е���ЧԪ�ظ���
 void swap(unordered_map&) �������������е�Ԫ��
7.unoedered_map��Ͱ����
 size_t bucket count()const ���ع�ϣͰ�е��ܸ���
 size_t bucket size(size_t n)const ����n��Ͱ����ЧԪ�ص��ܸ���
 size_t bucket(const K& key) ����Ԫ��key���ڵ�Ͱ��
*/
 //OJСѵ��
/*
961. �ظ� N �ε�Ԫ��
�ڴ�СΪ 2N ������ A ���� N+1 ����ͬ��Ԫ�أ�������һ��Ԫ���ظ��� N �Ρ�
�����ظ��� N �ε��Ǹ�Ԫ�ء�
ʾ�� 1��
���룺[1,2,3,3]
�����3
ʾ�� 2��
���룺[2,1,2,5,3,2]
�����2
ʾ�� 3��
���룺[5,1,5,2,5,3,5,4]
�����5
*/
class Solution {
public:
	int repeatedNTimes(vector<int>& A) {
		int N = A.size() / 2;
		//��unordered_map��ͳ��ÿ��Ԫ�س��ֵĸ���
		unordered_map<int, int> m;
		for (auto a : A){
			m[a]++;
		}
		//��������
		/*for (auto a : A){
			if (m[a] == N){
				return a;
			}
		}*/
		//������ϣ��
		for (auto a : m){
			if (a.second == N){
				return a.first;
			}
		}
		return 0;
	}
};
/*
2.������52. ��������ĵ�һ�������ڵ�
˼·�����ݽṹ�������˿���ָ���˼�룬ʱ�临�Ӷ�O��n�� �ռ�O��1��
������ù�ϣ�� ʱ�临�Ӷ�O��n���ռ临�Ӷ�O��n��
keyΪ��㣬valueΪboolֵ �ȱ�����һ�������ֵ�Դ����ϣ�� �ٷ��ʵڶ���
��ĳ���ڵ��boolΪtrue ��Ϊ�������
*/
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
	
};

class Solution {
public:
	ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
		unordered_map<ListNode*, bool> m;
		ListNode* a = headA;
		ListNode* b = headB;
		while (a){
			m[a] = true;
			a = a->next;
		}
		unordered_map<ListNode*, bool>::iterator it;
		while (b){
			it = m.find(b);
			if (it == m.end()){
				;
			}
			else{
				return b;
			}
			b = b->next;
		}
		return NULL;
	}
};

/*
������35. ��������ĸ���
��ʵ�� copyRandomList ����������һ�����������ڸ��������У�
ÿ���ڵ������һ�� next ָ��ָ����һ���ڵ㣬����һ�� random ָ��
ָ�������е�����ڵ���� null��
��ʾ��
-10000 <= Node.val <= 10000
Node.random Ϊ�գ�null����ָ�������еĽڵ㡣
�ڵ���Ŀ������ 1000 ��
*/
//˼·����ϣ�� ����һ��û��randomָ����������ʱ��ԭ������ڵı���Ķ�Ӧ
//��ϵ�Ѿ����ڣ��ù�ϣ���¼һ�� �ٱ���һ�飬ÿ��λ�ö�ȡrandomָ���ԭ����
//���ݹ�ϣ��鵽���ƺ��Ӧ�Ľ�㣬��������
class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};
class Solution {
public:
	Node* copyRandomList(Node* head) {
		if (head == NULL){
			return head;
		}
		//����һ����ϣ��
		unordered_map<Node*, Node*> m;
		//Ϊ�µ�ͷ�ڵ㿪�ٿռ�
		Node* newhead = new Node(head->val);
		//������һ�� ���Ʋ���random���� ��ʹ�¾�����������
		Node* n = newhead;
		Node* o = head;
		while (o){
			m[o] = n;
			o = o->next; //һ��ʼ����һ������Ϊ��һ��Ϊ�˽�����������ͷ�ڵ�Ĺ�ϣ��ϵ ����ǰ�Ѿ����ƹ�ͷ�ڵ��� ����Ҫ����һ����㿪ʼ����
			if (o == NULL){
				n->next = NULL;
			}
			else{
				Node* next = new Node(o->val);
				n->next = next;
			}
			n = n->next;
		}
		//����old��new����Ĺ�ϣ��ϵΪnew��random��ֵ
		n = newhead;
		o = head;
		while (o){
			n->random = m[o->random];//m[o->random]�� o->random�ĵ�ַ��m�ж�Ӧ���������е�ĳ����ַ
			//���õ�ַ��ֵ����ǰ��n->random �������˸ýڵ�ĸ������� 
			o = o->next;
			n = n->next;
		}
		return newhead;
	}
};