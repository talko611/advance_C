#ifndef __Q3FUNCS_H
#define __Q3FUNCS_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEFT 0
#define RIGHT 1
#define BEFORE -1
#define AFTER 1

//Data structures
typedef struct listNode {
    int data;
    struct listNode *next;
} ListNode;

typedef struct list {
    ListNode *head;
    ListNode *tail;
} List;

typedef struct treeNode {
    int data;
    struct treeNode *parent;
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

typedef struct tree {
    TreeNode *root;
    List leafList;
} Tree;

//Functions
void checkMemoryAllocation(void *);

TreeNode *createNewTreeNode(int, TreeNode *, TreeNode *, TreeNode *);

ListNode *createNewListNode(int, ListNode *);

void makeEmptyList(List *);

void insertDataToEndList(List *, int);

void insertNodeToEndList(List *, ListNode *);

bool isEmptyList(List *lst);

Tree BuildTreeFromArrayWithLeafList(int *, int);

TreeNode *BuildTreeFromArrayWithLeafListHelper(int *, int, List *); //Used inside BuildTreeFromArrayWithLeafList

void printTreeInorder(Tree);

void printTreeInOrderHelper(TreeNode *);// Used inside printTreeInorder

void freeTreeHelper(TreeNode *);// Used inside freeTree

void freeList(List *);

void freeTree(Tree);

void printLeafList(Tree);

void PrintList(List *);

TreeNode *findParentHelper(TreeNode *, int, int);//used inside find parent

TreeNode *findParent(Tree, int, int);

void replaceData(List *, int, int);//function replace treeNode data in other data

void insertNodeToStartList(List *, ListNode *);

void insertNodeBefore(List *, ListNode *, int);// Insert node before node with the data passed to the function

void insertNodeAfter(List *, ListNode *, int);//Insert node after the node with the data passed to the function

void insertDataInPlace(List *, int, int,
                       int);// Create new list node and calls to insertNodeBefore and insertNodeAfter according to flag passed

Tree AddLeaf(Tree tr, TreeNode *p, int branchSelect, int data);

int findOrientedLeaf(TreeNode *root, int branchSelect);// Finds the most right/left leaf in a tree according to flag

bool isLeaf(TreeNode *node);// checks if a node id a leaf*/

#endif