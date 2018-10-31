#pragma once

typedef int DataType;

typedef struct DListNode
{
	struct DListNode* _pPre;
	struct DListNode* _pNext;
	DataType _data;
}DListNode,*PDListNode;

///////////////带头结点的双向链表相关操作/////////////////////////

PDListNode BuyNode(DataType data);
void DListInit(PDListNode* Phead);
void DListPushBack(PDListNode pHead, DataType data);
void DListPushFront(PDListNode pHead, DataType data);
void DListPopBack(PDListNode pHead);
void DListPopFront(PDListNode pHead);
PDListNode DListFind(PDListNode pHead, DataType data);
void DListInsert(PDListNode pos, DataType data);
void DListErase(PDListNode pos);
int DListEmpty(PDListNode pHead);
void DListClear(PDListNode pHead);
int DListSize(PDListNode pHead);
void DListDestory(PDListNode* pHead);


