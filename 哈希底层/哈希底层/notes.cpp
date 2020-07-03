#define _CRT_SECURE_NO_WARNINGS 1

/*
一、哈希概念:
	一种映射的对应关系
	通过哈希函数使得元素的存储位置与它的关键码之间建立一一映射的关系

	
二、哈希冲突：
    通常使用除留余数法来作为哈希函数 但是
	对于两个不同数据元素的关键字，通过哈希函数计算出相同的哈希地址，即不同
	的值，映射到了相同的位置，该现象称为哈希冲突或哈希碰撞

三、如何解决哈希冲突？
	两种常见的方式是：闭散列和开散列

	1.闭散列:
		也叫开放定地址法，当发生哈希冲突时，如果哈希表未被装满，说明在哈希
		表中必然还有空位置，Mamet可以把key存放到冲突位置中的"下一个"空位置中去

		a.如何寻找下一个空位置呢？
		 (1) 闭散列--开放定制法(冲突以后重新找个位置存放)
			 线性探测:从发生冲突的位置开始，依次向后探测，直到寻找到下一个空位置为止
			 二次探测:按2次方往后找空位置
**当线性表的可用容量逐渐不够，出现哈希冲突的概率就越大，需要控制这种现象：
所以引入负载因子的概念:
		//负载因子= 表中数据/表的大小 衡量哈希表满的程度

		//表接近满，插入数据越容易冲突，冲突越多，效率越低

		//哈希表并不是满了才增容，开放定址法中，一般负载因子到了0.7左右就要增容
			 
		//负载因子越小，冲突概率越低，整体效率越高，但是负载因子越小，浪费空间越大
		//所以负载因子一般都取一个折中值
	
	2.开散列--开链法(哈希桶):
		将具有相同地址的关键码归于同一子集合，每一个子集和称为一个桶，
	各个桶中的元素通过一个单链表连接起来，各链表的头节节点存在哈希表中。

**但是当大量数据冲突，这些哈希冲突的数据就会挂在同一个链式桶中，查找的效率
就会降低，所以开散列-哈希桶也是需要控制哈希冲突:
	
	如何尽量的避免这种情况呢？
		通过控制负载因子，负载因子可以更大一点，
		一半开散列把负载因子控制在1，这里就可以把空间利用率提高一点
	
	假设总是有一些桶的数据很多，冲突很厉害如何解决？
		一个桶链长度超过一定值，就将挂链表改成挂红黑树

*/
