#include "SList.h"

//链表初始化
void SListInit(PNode* pHead)  //如果要改变外部实参的指向必须要用二级指针
{
	assert(pHead);
	*pHead = NULL;
}
//尾插
void SListPushBack(PNode* pHead, DataType data)
{
	PNode pNewNode = NULL;
	assert(pHead);  //pHead一定不会为空，因为pHead是一个二级指针
	//链表为空
	pNewNode = BuySListNode(data);
	if (NULL == *pHead)
		*pHead = pNewNode;
	//链表非空
	else
	{
		PNode pCur = *pHead;
		while (pCur->_pNext)
			pCur = pCur->_pNext;
		pCur->_pNext = pNewNode;
	}
}

//头插
void SListPushFront(PNode* pHead, DataType data)
{
	PNode pNewNode = NULL;
	assert(pHead);
	pNewNode = BuySListNode(data);
	if (NULL == pNewNode)
		return;
	pNewNode->_pNext = *pHead;
	*pHead = pNewNode;
}

//尾删
void SListPopBack(PNode* pHead)
{
	//assert 和 if 区别：
	//assert只在debug才会有，当括号里的条件非法才会触发，但是 if 是判断条件合法的情况下来判断需求
	assert(pHead);
	if (NULL == pHead)
		return;
	//非空
	else if (NULL == (*pHead)->_pNext)
	{
		//只有一个节点
		free(*pHead);
		(*pHead) = NULL;
	}
	else
	{
		//有多个节点
		PNode pCur = *pHead;
		while (pCur->_pNext->_pNext)
			pCur = pCur->_pNext;
		free(pCur->_pNext);
		pCur->_pNext = NULL;
	}
}

//头删
void SListPopFront(PNode* pHead)
{
	assert(pHead);
	//如果链表里面什么都没有直接返回
	if (NULL == *pHead)
		return;
	else
	{
		//可以处理只有一个节点和多个节点
		PNode pDel = NULL;
		pDel = *pHead;
		*pHead = pDel->_pNext;
		free(pDel);
	}
}
PNode SListFind(PNode pHead, DataType data)
{
	PNode pCur = pHead;
	while (pCur)
	{
		if (pCur->_data == data)
			return pCur;
		else
			pCur = pCur->_pNext;
	}
	return NULL;
}
//任意位置的插入
void SListInsert(PNode* pHead, DataType data, PNode pos)
{
	PNode pNewNode = NULL;
	assert(pHead);
	if (NULL == *pHead || NULL == pos)
		return;
	pNewNode = BuySListNode(data);
	if (NULL == pNewNode)
		return;
	else
	{
		pNewNode->_pNext = pos->_pNext;
		pos->_pNext = pNewNode;
	}
}
//任意位置的删除
void SListErease(PNode* pHead, PNode pos)
{
	assert(pHead);
	if (NULL == *pHead || NULL == pos)
		return;
	if (pos == *pHead)
		SListPopFront(pHead);
	else
	{
		PNode pCur = *pHead;
		while (pCur && pCur->_pNext != pos) //检测pCur有没有走到空
			pCur = pCur->_pNext;
		if (pCur)
		{
			pCur->_pNext = pos->_pNext;
			free(pos);
		}
	}
}
//链表的销毁，类似于头删。如果没有这个操作就存在内存泄漏
void SListDestory(PNode* pHead)
{
	SListClear(pHead);
}
//链表中节点个数
int SListSize(PNode* pHead)
{
	int count = 0;
	PNode pCur = NULL;
	pCur = *pHead;
	while (pCur)
	{
		count++;
		pCur = pCur->_pNext;
	}
	return count;
}
//清空链表，操作方法和销毁链表相同
void SListClear(PNode* pHead)
{
	PNode pDelNode = NULL;
	assert(pHead);
	while (*pHead)
	{
		pDelNode = *pHead;
		*pHead = pDelNode->_pNext;
		free(pDelNode);
	}
}
//查找尾节点
PNode SListBack(PNode pHead)
{
	PNode pCur = pHead;
	if (NULL == pHead)
		return NULL;
	while (pCur->_pNext)
		pCur = pCur->_pNext;
	return pCur;
}
///////////链表面试题//////////////////////
void PrintListFromTailToHead(PNode pHead)  //递归时间复杂度O(N) 空间复杂度O(N)
{
	if (pHead)
	{
		PrintListFromTailToHead(pHead->_pNext);
		printf("%d ", pHead->_data);
	}
	printf("\n");
}

//删除无头单链表的一个非尾节点（不能遍历链表）
//这里采用的方法是用pos->_pNext的data覆盖pos位置处的data，然后删掉pos->_pNext位置的data
void DeleteNotTailNode(PNode pos)
{
	PNode pDelNode = NULL;
	if (NULL == pos && NULL == pos->_pNext)
		return;
	pDelNode = pos->_pNext;
	pos->_data = pDelNode->_data;
	pos->_pNext = pDelNode->_pNext;
	free(pDelNode);
}
//在无头单链表的一个节点前插入一个节点（不能遍历链表）
void InsertPosFront(PNode pos, DataType data)
{
	PNode pNewNode = NULL;
	if (NULL == pos)
		return;
	pNewNode = BuySListNode(pos->_data);
	pNewNode->_pNext = pos->_pNext;
	pos->_pNext = pNewNode;
	pos->_data = data;
}
//单链表实现约瑟夫环
PNode JosephCircle(PNode* pHead, const int M)
{
	PNode pCur = NULL;
	PNode pDelNode = NULL;
	assert(pHead);
	if (NULL == *pHead)
		return NULL;
	pCur = *pHead;
	//报数
	while (pCur->_pNext != pCur)
	{
		int count = M;
		while (--count)
		{
			pCur = pCur->_pNext;//构环
		}
		//删节点,替换法删除	
		pDelNode = pCur->_pNext;
		pCur->_data = pDelNode->_data;
		pCur->_pNext = pDelNode->_pNext;
	}
	*pHead = pCur;  //最后可能把第一个节点删除了
	return *pHead;
}
//冒泡排序
void SListBubbleSort(PNode pHead)
{
	PNode pPre = NULL;
	PNode pCur = NULL;
	PNode pTail = NULL;
	if (NULL == pHead || NULL == pHead->_pNext)
		return;
	while (pHead != pTail)
	{
		int IsChange = 0;
		pPre = pHead;
		pCur = pPre->_pNext;
		while (pCur != pTail)
		{

			if (pPre->_data > pCur->_data)
			{
				int temp = pPre->_data;
				pPre->_data = pCur->_data;
				pCur->_data = temp;
				IsChange = 1;
			}
			pPre = pCur;
			pCur = pPre->_pNext;
		}
		if (!IsChange)
			return;
		pTail = pPre;
	}
}
//单链表的逆置,这里采用三个指针
void ReverseSList(PNode* pHead)
{
	PNode pPre = NULL;
	PNode pCur = NULL;
	PNode pNext = NULL;
	assert(pHead);
	if (NULL == *pHead || NULL == (*pHead)->_pNext)
		return;
	pCur = *pHead;
	while (pCur)
	{
		pNext = pCur->_pNext;
		pCur->_pNext = pPre;
		pPre = pCur;
		pCur = pNext;
	}
	*pHead = pPre;
}
//法二,.头插法，解决不了链表带环问题？可以考虑先将环断开然后逆序最后在连接起来
PNode ReverseSListOP(PNode pHead)
{
	PNode pNewHead = NULL;
	PNode pCur = NULL;
	PNode pNext = NULL;
	if (NULL == pHead)
		return NULL;
	pCur = pHead;
	while (pCur)
	{
		pNext = pCur->_pNext;
		pCur->_pNext = pNewHead;
		pNewHead = pCur;
		pCur = pNext;
	}
	return pNewHead;
}

//合并两个有序链表，合并之后依然有序
PNode MergeSList(PNode pHead1, PNode pHead2)
{
	PNode pNewHead = NULL;
	PNode pTailNode = NULL;
	PNode pL1 = pHead1;
	PNode pL2 = pHead2;
	//法一
	if (NULL == pHead1)
		return pHead2;
	if (NULL == pHead2)
		return pHead1;
	if (NULL == pHead1 && NULL == pHead2)
		return pHead1;
	//法二
	/*if (NULL == pHead1 || NULL == pHead2)
		return pHead1 ? pHead2 : pHead1;*/

		//两个链表都不为空
	if (pL1->_data < pL2->_data)
	{
		pNewHead = pL1;
		pL1 = pL1->_pNext;
	}
	else
	{
		pNewHead = pL2;
		pL2 = pL2->_pNext;
	}
	pTailNode = pNewHead;
	while (pL1 && pL2)
	{
		if (pL1->_data < pL2->_data)
		{
			pTailNode->_pNext = pL1;
			pL1 = pL1->_pNext;
		}
		else
		{
			pTailNode->_pNext = pL2;
			pL2 = pL2->_pNext;
		}
		pTailNode = pTailNode->_pNext;
	}
	if (pL1)
	{
		pTailNode->_pNext = pL1;
	}
	else
	{
		pTailNode->_pNext = pL2;
	}
	return pNewHead;
}
//查找链表的中间结点，要求只能遍历一次
//思路：快慢指针
PNode FindMidNode(PNode pHead)
{
	PNode pSlow = NULL;
	PNode pFast = NULL;
	if (NULL == pHead)
		return NULL;
	pSlow = pHead;
	pFast = pHead;
	while (pFast && pFast->_pNext)   //pFast走得快，可以只用这个指针来作为循环条件
	{
		pFast = pFast->_pNext->_pNext;
		pSlow = pSlow->_pNext;
	}
	return pSlow;
}

//查找链表倒数的第K个节点，要求只能遍历一次链表
PNode FindLastKNode(PNode pHead, int K)
{
	PNode pFast = pHead;
	PNode pSlow = pHead;
	if (NULL == pHead || K <= 0)
		return NULL;
	//先让pFast走K步，
	while (K--)
	{
		//首先保证pFast不为空
		if (pFast)
			return NULL;
		pFast = pFast->_pNext;
	}
	//然后快慢指针一起走
	while (pFast)
	{
		pFast = pFast->_pNext;
		pSlow = pSlow->_pNext;
	}
	return pSlow;
}
//判断两个无环单链表是否相交
int IsCrossWithoutCircle(PNode pHead1, PNode pHead2)
{
	PNode pTail1 = pHead1;
	PNode pTail2 = pHead2;
	if (NULL == pHead1 || NULL == pHead2)
		return 0;
	//找第一个链表的尾节点
	while (pTail1->_pNext)
	{
		pTail1 = pTail1->_pNext;
	}
	//找第二个链表的尾节点
	while (pTail2->_pNext)
	{
		pTail2 = pTail2->_pNext;
	}
	return pTail1 == pTail2;
}
//判断两个无环单链表是否相交,若相交，求交点
PNode GetCrossNode(PNode pHead1, PNode pHead2)
{
	int size1 = 0, size2 = 0;
	int gap = 0;
	PNode pCur1 = pHead1;
	PNode pCur2 = pHead2;
	if (!(IsCrossWithoutCircle(pHead1, pHead2))) //如果不相交
		return NULL;
	//求两个链表中节点个数
	while (pCur1)
	{
		size1++;
		pCur1 = pCur1->_pNext;
	}
	while (pCur2)
	{
		size2++;
		pCur2 = pCur2->_pNext;
	}
	gap = size1 - size2;
	pCur1 = pHead1;
	pCur2 = pHead2;
	if (gap > 0)
	{
		while (gap--)
		{
			pCur1 = pCur1->_pNext;
		}
	}
	else if (gap < 0)
	{
		while (gap++)
		{
			pCur2 = pCur2->_pNext;
		}
	}
	else
	{
		while (pCur1 != pCur2)
		{
			pCur1 = pCur1->_pNext;
			pCur2 = pCur2->_pNext;
		}
	}
	return pCur1;
}

//判断链表是否带环?若带环，求环的长度
PNode IsCircle(PNode pHead)
{
	PNode pFast = pHead;
	PNode pSlow = pHead;
	while (pFast && pFast->_pNext)
	{
		pFast = pFast->_pNext->_pNext;
		pSlow = pSlow->_pNext;
		if (pFast == pSlow)
			return pSlow;    //一定带环
	}
	return NULL;   //一定不带环
}
int GetCircleLen(PNode pHead)
{
	PNode pMeetNode = IsCircle(pHead);
	PNode pCur = pMeetNode;
	int count = 1;
	if (NULL == pMeetNode)
		return 0;
	if (pCur->_pNext != pMeetNode)
	{
		count++;
		pCur = pCur->_pNext;
	}
	return count;
}
//带环？求环的入口点，根据判环方式得出计算公式 ，证明？？？
PNode GetEnterNode(PNode pHead, PNode pMeetNode)
{
	PNode pH = pHead;
	PNode pM = pMeetNode;
	if (NULL == pHead || NULL == pMeetNode)
		return NULL;
	while (pH != pM)
	{
		pH = pH->_pNext;
		pM = pM->_pNext;
	}
	return pH;
}
//判断两个链表是否相交？若相交，求交点，链表可能带环
//一个带环，一个不带环肯定不会相交
int IsListCrossWithCircle(PNode pHead1, PNode pHead2)
{
	PNode pMeetNode1 = IsCircle(pHead1);
	PNode pMeetNode2 = IsCircle(pHead2);

	//如果两个链表都不带环,找两个链表的最后一个节点，并检测节点是否相等
	if (NULL == pMeetNode1 && NULL == pMeetNode2)
	{
		PNode pTail = NULL;
		PNode pTail2 = NULL;
		if (NULL == pHead1 || NULL == pHead2)
			return 0;
		pTail = pHead1;
		pTail2 = pHead2;
		while (pTail->_pNext)
		{
			pTail = pTail->_pNext;
		}
		while (pTail2->_pNext)
		{
			pTail2 = pTail2->_pNext;
		}
		if (pTail == pTail2)
		{
			return 1;
		}
	}
	//如果两个链表都带环
	else if (pMeetNode1 && pMeetNode2)
	{
		PNode pCur = pMeetNode1;
		do
		{
			if (pCur == pMeetNode2)
				return 2;
			pCur = pCur->_pNext;
		} while (pCur != pMeetNode1);
	}
	return 0;
}
//复杂链表的复制
//思路： 1、在原链表每个节点后面插入值相同的节点
//       2、给新插入节点的随机指针域赋值
//       3、将插入的新节点从链表中拆下来
PComplexNode CopyComplexList(PComplexNode pHead)
{
	PComplexNode pOldNode = pHead;
	PComplexNode pNewNode = NULL;
	PComplexNode pNewHead = NULL;
	if (NULL == pHead)
		return NULL;
	// 1、在原链表每个节点后面插入值相同的节点
	while(pOldNode)
	{
		pNewNode = (PComplexNode)malloc(sizeof(ComplexNode));
		if (NULL == pNewNode)
			return NULL;
		pNewNode->_data = pOldNode->_data;
		pNewNode->_pNext = NULL;
		pNewNode->_pRandom = NULL;

		pNewNode->_pNext = pOldNode->_pNext;
		pOldNode->_pNext = pNewNode;
		pOldNode = pNewNode->_pNext;
	}
	// 2、给新插入节点的随机指针域赋值
	pOldNode = pHead;
	while (pOldNode->_pNext)
	{
		pNewNode = pOldNode->_pNext;
		if (NULL == pOldNode->_pNext)
			pNewNode->_pRandom = NULL;
		else
			pNewNode->_pRandom = pOldNode->_pRandom->_pNext;
		pOldNode = pNewNode->_pNext;
	}
	// 3、将插入的新节点从链表中拆下来
	pOldNode = pHead;
	pNewHead = pOldNode->_pNext;
	while (pOldNode->_pNext)
	{
		pNewNode = pOldNode->_pNext;
		pOldNode->_pNext = pNewNode->_pNext;
		pOldNode = pNewNode; 
	}
	return pNewHead;
}

//求两个已排序单链表中相同的数据
void UnionSet(PNode pHead1, PNode pHead2)
{
	while (NULL != pHead1 && NULL != pHead2)
	{
		if (pHead1->_data < pHead2->_data)
		{
			pHead1 = pHead1->_pNext;
		}
		else if (pHead1->_data > pHead2->_data)
		{
			pHead2 = pHead2->_pNext;
		}
		else
		{
			printf("pHead1->_data=%d, pHead2->_data=%d", pHead1->_data,pHead2->_data);
			pHead1 = pHead1->_pNext;
			pHead2 = pHead2->_pNext;
		}
	}
}
////////////////////////////////////////////////////////
PNode BuySListNode(DataType data)
{
	PNode pNewNode = (PNode)malloc(sizeof(Node));
	if (NULL == pNewNode)
		return NULL;
	pNewNode->_pNext = NULL;
	pNewNode->_data = data;
	return pNewNode;
}
void PrintList(PNode pHead)
{
	PNode pCur = pHead;
	while (pCur)
	{
		printf("%d-->", pCur->_data);
		pCur = pCur->_pNext;
	}
	printf("NULL\n");
}

#if 0
void TestComplexList()
{
	ComplexNode node1, node2, node3, node4;
	PComplexNode pHead = NULL;
	node1._data = 1;
	node1._pNext = &node2;
	node1._pRandom = &node3;

	node2._data = 2;
	node2._pNext = &node3;
	node2._pRandom = &node1;

	node3._data = 3;
	node3._pNext = &node4;
	node3._pRandom = &node3;
 
	node4._data = 4;
	node4._pNext = NULL;
	node4._pRandom = NULL;

	pHead = CopyComplexList(&node1);
}

void TestIsListCrossWithCircle()
{
	PNode pHead1 = NULL;
	PNode pHead2 = NULL;

	SListPushBack(&pHead1, 1);
	SListPushBack(&pHead1, 2);
	SListPushBack(&pHead1, 3);
	SListPushBack(&pHead1, 4);
	SListPushBack(&pHead1, 5);
	SListPushBack(&pHead1, 6);
	SListPushBack(&pHead1, 7);
	SListPushBack(&pHead1, 8);
	SListBack(pHead1)->_pNext = SListFind(pHead1, 5);

	SListPushBack(&pHead2, 1);
	SListPushBack(&pHead2, 2);
	SListPushBack(&pHead2, 3);
	SListPushBack(&pHead2, 4);
	SListBack(pHead2)->_pNext = SListFind(pHead1, 3);

	int ret = IsListCrossWithCircle(pHead1, pHead2);
	if (1 == ret)
		printf("两个链表不带环相交\n");
	else if (2 == ret)
		printf("两个链表带环相交\n");
	else
		printf("两个链表不相交\n");
}
void TestIsSListCross()
{
	//相交
	//不相交
	PNode pHead1 = NULL;
	PNode pHead2 = NULL;
	PNode pCur;

	SListPushBack(&pHead1, 1);
	SListPushBack(&pHead1, 2);
	SListPushBack(&pHead1, 3);
	SListPushBack(&pHead1, 4);
	SListPushBack(&pHead1, 5);
	PrintList(pHead1);

	SListPushBack(&pHead2, 6);
	SListPushBack(&pHead2, 7);
	SListPushBack(&pHead2, 8);
	SListPushBack(&pHead2, 9);
	SListPushBack(&pHead2, 0);
	PrintList(pHead2);

	SListBack(pHead1->_Next) = SListFind(pHead2->_Next, 7);  //构建链表相交

	if (IsCrossWithoutCircle(pHead1, pHead2)
	{
		printf("两个链表相交\n");
			pCur = GetCrossNode(pHead1, pHead2);
			printf("交点为: %d\n", pCur->_data);
	}
	else
	{
		printf("两个链表不相交\n");
	}

	SListDestory(pHead1);
	SListDestory(pHead2);
}

void TestList()
{
	PNode pHead;
	SListInit(&pHead);

	SListPushBack(&pHead, 1);
	SListPushBack(&pHead, 2);
	SListPushBack(&pHead, 3);
	SListPushBack(&pHead, 4);
	SListPushBack(&pHead, 5);
	PrintList(pHead);

	//FindMidNode(pHead);
	PNode pCur = FindMidNode(pHead);
	printf("中间节点是：%d\n", pCur->_data);
	//ReverseSList(&pHead);
	PrintList(pHead);
	/*
	SListPopBack(&pHead);
	PrintList(pHead);

	SListPushFront(&pHead, 0);
	PrintList(pHead);

	SListPopFront(&pHead);
	PrintList(pHead);

	PNode pCur = NULL;
	pCur = SListFind(pHead, 3);
	if (pCur)
	{
		SListInsert(&pHead, 6, pCur);
	}
	PrintList(pHead);

	SListErease(&pHead, pCur);
	PrintList(pHead);
	*/
}
void TestSListBubbleSort()
{
	PNode pHead;
	SListInit(&pHead);

	SListPushBack(&pHead, 5);
	SListPushBack(&pHead, 2);
	SListPushBack(&pHead, 1);
	SListPushBack(&pHead, 6);
	SListPushBack(&pHead, 8);
	SListPushBack(&pHead, 4);
	SListPushBack(&pHead, 7);
	SListPushBack(&pHead, 3);
	PrintList(pHead);

	SListBubbleSort(pHead);
	PrintList(pHead);
	SListDestory(&pHead);
}

void TestJosephCircle()
{
	PNode pHead;
	SListInit(&pHead);

	SListPushBack(&pHead, 1);
	SListPushBack(&pHead, 2);
	SListPushBack(&pHead, 3);
	SListPushBack(&pHead, 4);
	SListPushBack(&pHead, 5);
	SListPushBack(&pHead, 6);
	SListPushBack(&pHead, 7);
	SListPushBack(&pHead, 8);
	PrintList(pHead);

	//构环
	SListBack(pHead)->_pNext = pHead;
	JosephCircle(&pHead, 3);
	//解环
	pHead->_pNext = NULL;
	PrintList(pHead);
}

void TestMergeSList()
{
	PNode pHead1;
	PNode pHead2;
	SListInit(&pHead1);
	SListInit(&pHead2);

	SListPushBack(&pHead1, 1);
	SListPushBack(&pHead1, 3);
	SListPushBack(&pHead1, 5);
	SListPushBack(&pHead1, 7);
	SListPushBack(&pHead1, 9);

	SListPushBack(&pHead2, 2);
	SListPushBack(&pHead2, 4);
	SListPushBack(&pHead2, 6);
	SListPushBack(&pHead2, 8);

	PNode pNewList = MergeSList(pHead1, pHead2);
	PrintList(pNewList);
	SListDestory(&pNewList);
}
#endif 0
