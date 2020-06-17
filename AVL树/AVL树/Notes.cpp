#define _CRT_SECURE_NO_WARNINGS 1

/*
AVL树
	二叉搜索树虽然可以缩短查找效率，但如果数据有序或接近有序二叉搜索树退化为单支
树，查找元素相当于在顺序表中搜索元素，效率低下。
	所以AVL树的概念应运而生：当向二叉搜索树插入新的节点后，如果能够保证每个节点
的左右子树高度之差的绝对值不超过1，即可降低树的高度，从而减少平均搜索长度。

AVL树或者是空树，或者是具有一下性质的二叉搜索树：
	1.它的左右子树都是AVL树
	2.左右子树高度之差(简称平衡因子)的绝对值不超过1（-1，0，1）
AVL树具有高度平衡的特点，如果其有N个节点，其高度可保持在O(logN),搜索时间复杂度为O(logN)
	平衡因子 = 右子树高度-左子树高度

**当AVL树插入新节点，会影响新插入节点的祖先的平衡因子
1.右子树的高度变化，则父亲的平衡因子+1，左子树的高度变化，则父亲的平衡因子-1
2.父亲的平衡因子更新完成后变成1/-1，则说明父亲所在子树的高度已经发生了变化，则需要继续
往上更新。
3.父亲的平衡因子更新完成后变为2/-2，则说明父亲所在的子树已经不平衡，那么需要
旋转处理。
4.父亲的平衡因子更新完成后变成0，则说明父亲所在的子树高度没变，对上一层没影响，则更新完成

AVL树的旋转：
	1.新节点插入较高左子树的左侧---右右：右单旋
	2.新节点插入较高右子树的右侧---左左：左单旋
	3.新节点插入较高左子树的右侧---左右：先左单旋转 再右单旋转
	4.新节点插入较高右子树的左侧---右左：先右单旋转 再左单旋转
*/