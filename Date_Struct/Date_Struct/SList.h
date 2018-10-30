#pragma once

#include <stdio.h>
#include <assert.h>
#include <malloc.h>

typedef int DataType;

typedef struct Node
{
	struct Node* _pNext;
	DataType _data;
}Node, *PNode;

//////////////////////////
//复杂链表
typedef struct ComplexNode
{
	struct ComplexNode* _pNext;
	struct ComplexNode* _pRandom;  //随机指针域指向链表中的一个随机节点或者NULL
	DataType _data;
}ComplexNode, *PComplexNode;

//复杂链表相关面试题
PComplexNode CopyComplexList(PComplexNode pHead);

/////////////不带头结点的单链表///////////////////////
void SListInit(PNode* pHead);
PNode BuySListNode(DataType data);
void SListPushBack(PNode* pHead, DataType data);
void SListPushFront(PNode* pHead, DataType data);
void SListPopBack(PNode* pHead);
void SListPopFront(PNode* pHead);
PNode SListFind(PNode pHead, DataType data);
void SListInsert(PNode* pHead, DataType data, PNode pos);
void SListErease(PNode* pHead, PNode pos);
void SListDestory(PNode* pHead);
int SListSize(PNode* pHead);
void SListClear(PNode* pHead);
PNode SListBack(PNode pHead);//查找尾节点
////////////////链表面试题////////////////////////////
void PrintListFromTailToHead(PNode pHead);
void DeleteNotTailNode(PNode pos);
void InsertPosFront(PNode pos, DataType data);
PNode JosephCircle(PNode* pHead, const int M);
void SListBubbleSort(PNode pHead);
void ReverseSList(PNode* pHead);
PNode ReverseSListOP(PNode pHead);
PNode MergeSList(PNode pHead1, PNode pHead);
PNode FindMidNode(PNode pHead);
PNode FindLastKNode(PNode pHead, int K);
int IsCrossWithoutCircle(PNode pHead1, PNode pHead2);
PNode GetCrossNode(PNode pHead1, PNode pHead2);
PNode IsCircle(PNode pHead);
int GetCircleLen(PNode pHead);
PNode GetEnterNode(PNode pHead, PNode pMeetNode);
int IsListCrossWithCircle(PNode pHead1, PNode pHead2);
void UnionSet(PNode pHead1, PNode pHead2);
//////////////////////////////////////////////////////
//void TestList();
//void PrintList(PNode pHead);
//void TestJosephCircle();
//void TestSListBubbleSort();
//void TestMergeSList();
//void TestIsSListCross();
//void TestIsListCrossWithCircle();
//void TestComplexList();
