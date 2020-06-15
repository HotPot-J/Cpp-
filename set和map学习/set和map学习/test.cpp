#define _CRT_SECURE_NO_WARNINGS 1

/*
һ����ظ��
1������ʽ����
	����ʽ����:vector��list��deque�ȣ���ײ�Ϊ�������е����ݽṹ������洢��
��Ԫ�ر���
	����ʽ������Ҳ�������洢���ݵģ���ͬ�����ڣ�������洢����<key��value>�ṹ
	�ļ�ֵ�ԣ������ݼ���ʱ������ʽ����Ч�ʸ��ߡ�

2����ֵ�ԣ�
	������ʾ����һһ��Ӧ��ϵ��һ�ֽṹ���ýṹ��һ��ֻ����������Ա����key��
	value��key�����ֵ��value��ʾ��key��Ӧ����Ϣ��

3�����νṹ�Ĺ���ʽ����
	����Ӧ�ó����Ĳ�ͬ��STL�ܹ�ʵ�������ֲ�ͬ�ṹ�Ĺ���ʽ����:���νṹ���ϣ
	�ṹ�����νṹ��ҪΪ:map,set,multimap��multiset��
	�����������Ĺ�ͬ�㣺ʹ��ƽ��������(�������)��Ϊ��ײ����������е�Ԫ��
	��һ����������С�

4.STL�й��ڼ���ֵ�Ķ���:
template <class T1, class T2>
struct pair
{
 typedef T1 first_type;
 typedef T2 second_type;
 T1 first;  //Key
 T2 second; //Value
 pair(): first(T1()), second(T2())
 {}
 
 pair(const T1& a, const T2& b): first(a), second(b)
 {}
};
*/


/*
����set
	1.set�ǰ���һ������洢Ԫ�ص�����
	2.��set�У�Ԫ�ص�value��Ϊkey������ÿ��value����Ψһ�ģ�set�е�Ԫ�ز�����
	�������޸ģ����ǿ��Դ������в������ɾ�����ǡ�
	3.���ڲ���set�е�Ԫ�����ǰ������ڲ��Ƚ϶���(���ͱȽ�)��ָʾ���ϸ�����׼���������
	4.set����ͨ��key���ʵ���Ԫ�ص��ٶ�ͨ����unordered_set���������������������˳���
	�Ӽ�����ֱ�ӵ�����
	5.set�ڵײ�ʹ�ö���������(�����)ʵ�ֵġ�

ֵ��ע��ĵ�:
	1.set��ֻ��value�����ڵײ�ʵ�ʴ�ŵ�����<value,value>���ɵļ�ֵ��
	2.set�в���Ԫ��ʱ��ֻҪ����value���ɣ�����Ҫ�����ֵ��
	3.set�е�Ԫ�ز������ظ�������ȥ�ص�����ʹ��set�������̣�
	4.ʹ��set�еĵ���������set�е�Ԫ�أ����Եõ���������
	5.set�е�Ԫ��Ĭ�ϰ���С�����Ƚ�
	6.set�в���ĳ��Ԫ�أ�ʱ�临�Ӷ�Ϊ logN
	7.set�е�Ԫ�ز������޸� ������޸ľͻ��ƻ���Ľṹ˳��

���õĽӿڣ�
	set<int> a;
	������:
		a.begin()  a.end()
	����:
		bool empty() const  
		size_type size() const //����set����ЧԪ�صĸ���
	��ɾ��
		pair<iterator,bool>insert(const value_type& x) 
			��set�в���Ԫ��x��ʵ�ʲ������<x,x>���ɵļ�ֵ��
			�������ɹ�������<��Ԫ����set�е�λ��,true>�����
			����ʧ�ܣ�˵��x��set���Ѿ����ڣ�����<��Ԫ����set�е�λ��,false>
		a.insert��1��;

		void erase��iterator position�� ɾ��set����positionλ���ϵ�Ԫ��
		size_type erase��const key_type& x�� ɾ��set��ֵΪx��Ԫ�أ�����ɾ����Ԫ�صĸ���

		void clear() ��set�е�Ԫ�����

*/

/*
����map
	1.map�ǹ����������������ض��Ĵ���(����key���Ƚ�)�洢�ɼ�ֵkey��ֵvalue��϶��ɵ�Ԫ��
	2.��map�У���ֵkeyͨ�����������Ψһ�ر�ʶԪ�أ���ֵvalue�д洢��˼�ֵkey���������ݡ�
	��ֵ��ֵvalue�����Ϳ��ܲ�ͬ��������map���ڲ���key��valueͨ����Ա����value_type����
	һ��ȡ�������Ϊpair
	3.���ڲ���map�е�Ԫ�����ǰ��ռ�ֵkey���бȽ������
	4.map��ͨ����ֵ���ʵ���Ԫ�ص��ٶ�ͨ����unordered_map������������map�������˳���Ԫ��
	ֱ�ӵ���(������map�е�Ԫ�ؽ��е���ʱ�����Եõ�һ�����������)
	5.map֧���±���ʷ�����[]�з���key���Ϳ����ҵ���key��Ӧ��value
	6.mapͨ����ʵ��Ϊƽ�����������

���ýӿڣ�
	����:map<string,string> m;

	��������
		m.begin() m.end() ���ص���һ��pair�ṹ�� ��Ҫ��pair->first/->second ȥ����key/value 

    ������
		bool empty() const
		size_type size() const ������Ч����

    ****Ԫ�ط���:
		mapped_type& operator[]��const key_type& k�� ����key��Ӧ��value
			�ײ㣺 
			mapped_type& operator[]��const key_type& k��{
			   return��*����this->insert��make_pair(k,mapped_type())����.first����.second;
			}
			(insert������������k�򷵻ظ�λ�õ���������������������Ժ�ʹ��mapped_type����Ĭ��
			���캯����ʼ��value�������ظ�λ��pair�ĵ�������this->insert��make_pair(k,mapped_type())����.first
			�ھ���*��.second��������  ���Դﵽ[]�������Է���v�����õ�Ŀ��)
	
		 operator[]����:
			1.���k���������Ѿ����ڣ��򷵻ض�Ӧv�����ã����Խ������޸�v
			2.���k�������в����ڣ�����Ȳ���pair<k,V()>,����v�����á�����
		ע�������v�ǵ���V���͵�Ĭ�Ϲ��캯������Ĭ��ֵ��
	
	map��Ԫ�ص��޸�
		pair<iterator,bool>insert��const value_type& x�� ��map�в����ֵ��x
		void earse(iterator position) ɾ��posλ���ϵ�Ԫ��
		size_type erase(const key_type& x) ɾ����ֵ��Ϊx��Ԫ��
		void erase(iterator first,iterator last��ɾ��[first��last]�����е�Ԫ��
		void clear���� ��map��Ԫ�����
		iterator find(const key_type& x) ��map�в���keyΪx��Ԫ�أ��ҵ����ظ�Ԫ�ص�const������,���򷵻�end
		
	**insert�����÷�  
		map<int,double> a;
		a.insert(pair<int,double>(1,2.0));  //Ҳ����д��:a.insert(make_pair(1,2.0));
        a.insert(pair<int,double>(2,3.0));
        a.insert(pair<int,double>(1,4.0));
		//����
		map<int,double>::iterator it = a.begin();
		while(it!=a.end()){
			//cout<<*it<<" ";   //�ᱨ�� �����䷵�ص���һ��pair
			cout<<it->first<<" ��"<<it->second; //���η�����key��value
			++it;
		}
		


�ܽ᣺
		1.map�е�Ԫ���Ǽ�ֵ��
		2.map�е�key��Ψһ�ģ��������޸�
		3.Ĭ�ϰ���С�ڵķ�ʽ��key���бȽ�
		4.map��Ԫ������õ�����ȥ���������Եõ�һ�����������
		5.����Ч�ʣ�O��logN��
		6.֧��[]����������operator[]�н��в������
*/


/*
OJ���Ӧ��:

692. ǰK����Ƶ����
��һ�ǿյĵ����б�����ǰ k �����ִ������ĵ��ʡ�

���صĴ�Ӧ�ð����ʳ���Ƶ���ɸߵ������������ͬ�ĵ�������ͬ����Ƶ�ʣ�����ĸ˳������

ʾ�� 1��

����: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
���: ["i", "love"]
����: "i" �� "love" Ϊ���ִ��������������ʣ���Ϊ2�Ρ�
    ע�⣬����ĸ˳�� "i" �� "love" ֮ǰ��
 

ʾ�� 2��

����: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
���: ["the", "is", "sunny", "day"]
����: "the", "is", "sunny" �� "day" �ǳ��ִ��������ĸ����ʣ�
    ���ִ�������Ϊ 4, 3, 2 �� 1 �Ρ�
 

ע�⣺

�ٶ� k ��Ϊ��Чֵ�� 1 �� k �� ����Ԫ������
����ĵ��ʾ���Сд��ĸ��ɡ�
*/
#include<iostream>
#include<vector>
#include<map> 
#include <functional>
using namespace std;
class Solution {
public:
	vector<string> topKFrequent(vector<string>& words, int k) {
		map<string, int> countmap;
		for (auto& e : words){
			countmap[e]++;   //��ʱͳ�Ƴ��˸����ַ������ִ������Ұ���string������˳�����������
		}

		//����������map�������������� ʹ��multimap�����и�������
		multimap<int, string, greater<int>> countSort;
		//countSort ����intΪkey stringΪvalue �ټ��Ϸº���greater<int> 
		//�ǵ�countSort�ڵײ㰴��keyֵ�Ӵ�С��˳������ ��ʵ���˸�Ƶ�ʻ������
		for (auto& e : countmap){
			countSort.insert(make_pair(e.second, e.first));
		}
		vector<string> res;
		for (auto e : countSort){
			res.push_back(e.second);
			if (--k==0){
				break;
			}
		}
		return res;
	}
};