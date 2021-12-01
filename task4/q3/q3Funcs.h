#ifndef __Q3FUNCS_H
#define __Q3FUNCS_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Data structures
typedef struct listNode
{
	int data;
	struct listNode* next;
} ListNode;

typedef struct list
{
	ListNode* head;
	ListNode* tail;
} List;

typedef struct  treeNode
{
	int data;
	struct treeNode* parent;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree
{
TreeNode* root;
List leafList;   /*רשימה מקושרת של כל העלים בעץ*/ 
} Tree;

//Functions
void checkMemoryAllocation(void *);
TreeNode* createNewTreeNode(int, TreeNode*, TreeNode*,TreeNode*);
ListNode* createNewListNode(int, ListNode*);
void makeEmptyList(List*);
void insertDataToEndList(List*, int);
void insertNodeToEndList(List*, ListNode*);
bool isEmptyList(List* lst);
Tree BuildTreeFromArrayWithLeafList(int *, int);
TreeNode *BuildTreeFromArrayWithLeafListHelper(int *, int, List*);
void printTreeInorder(Tree);
void printTreeInOrderHepler(TreeNode *);
void freeTreeHelper(TreeNode*);
void freeList(List*);
void freeTree(Tree);
void printLeafList(Tree);
void PrintList(List*);

#endif