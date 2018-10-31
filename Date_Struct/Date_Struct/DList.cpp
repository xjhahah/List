#include "DList.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>

PDListNode BuyNode(DataType data)
{
	PDListNode pNewNode = NULL;
	pNewNode = (PDListNode)malloc(sizeof(DListNode));
	if (NULL == pNewNode)
	{
		assert(0);
		return NULL;
	}
	pNewNode->_data = data;
	pNewNode->_pNext = NULL;
	pNewNode->_pPre = NULL;

	return pNewNode;
}
void DListInit(PDListNode* Phead)
{
	assert(Phead);
	*Phead = BuyNode(0);
}
//尾插
void DListPushBack(PDListNode pHead, DataType data)
{
	PDListNode pCur = pHead;
	PDListNode pNewNode = NULL;
	assert(pHead);
	while (pCur->_pNext)
	{
		pCur = pCur->_pNext;
	}
	pNewNode = BuyNode(data);
	pCur->_pNext = pNewNode;
	pNewNode->_pPre = pCur;
}
//头插
void DListPushFront(PDListNode pHead, DataType data)
{
	PDListNode pNewHead = NULL;
	assert(pHead);
	pNewHead = BuyNode(data);
	pNewHead->_pNext = pHead->_pNext;
	pHead->_pNext = pNewHead;
	pNewHead->_pPre = pHead;
	if(pNewHead->_pNext)
		pNewHead->_pNext->_pPre = pNewHead;
}

//尾删
void DListPopBack(PDListNode pHead)
{
	PDListNode pTailNode = pHead;
	assert(pHead);
	while (pTailNode->_pNext)
	{
		pTailNode = pTailNode->_pNext;
	}
	if (pTailNode != pHead)
	{
		pTailNode->_pPre->_pNext = NULL;
	}
	free(pTailNode);
}
//头删
void DListPopFront(PDListNode pHead)
{
	PDListNode pDelNode = pHead;
	assert(pHead);
	pDelNode = pHead->_pNext;
	if (NULL == pHead)
		return;
	pHead->_pNext = pDelNode->_pNext;
	if(pDelNode->_pNext)
		pDelNode->_pNext->_pPre = pHead;
	free(pDelNode);
}
//任意位置的插入
void DListInsert(PDListNode pos, DataType data)
{
	PDListNode pNewNode = NULL;
	if (NULL == pos || NULL == pos->_pPre)
		return;

	pNewNode = BuyNode(data);

	//先不破坏原链表的结构
	pNewNode->_pNext = pos;
	pNewNode->_pPre = pos->_pPre;
	pos->_pPre = pNewNode;
	pNewNode->_pPre->_pNext = pNewNode;	
}
//任意位置的删除
void DListErase(PDListNode pos)
{
	//空位置和头结点位置不能进行删除操作
	if (NULL == pos || NULL == pos->_pPre)
		return;
	pos->_pPre->_pNext = pos->_pNext;
	if(pos->_pNext)//不是最后一个节点
		pos->_pNext->_pPre = pos->_pPre;
}
PDListNode DListFind(PDListNode pHead, DataType data)
{
	PDListNode pCur = NULL;
	assert(pHead);
	pCur = pHead->_pNext;
	while (pCur)
	{
		if (pCur->_data == data)
		{
			return pCur;
		}
		pCur = pCur->_pNext;
	}
	return NULL;
}
int DListEmpty(PDListNode pHead)
{
	assert(pHead);
	return NULL == pHead->_pNext;
}
//只清空有效节点，不删除头结点
void DListClear(PDListNode pHead)
{
	PDListNode pCur = NULL;
	pCur = pHead->_pNext;
	assert(pHead);
	while (pCur)
	{
		pHead->_pNext = pCur->_pNext;
		free(pCur);
		pCur = pHead->_pNext;
	}
}
//链表中有效节点的个数,不包含头结点
int DListSize(PDListNode pHead)
{
	assert(pHead);
	int count = 0;
	PDListNode pCur = NULL;
	pCur = pHead->_pNext;
	while (pCur)
	{
		count++;
		pCur = pCur->_pNext;
	}
	return count;
}
void DListDestory(PDListNode* pHead)
{
	assert(pHead);
	DListClear(*pHead);
	free(*pHead);
	*pHead = NULL;
}
void PrintDList(PDListNode pHead)
{
	PDListNode pCur = NULL;
	assert(pHead);
	pCur = pHead->_pNext;
	while (pCur)
	{
		printf("%d ", pCur->_data);
		pCur = pCur->_pNext;
	}
	printf("\n");
}