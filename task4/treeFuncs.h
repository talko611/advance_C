#ifndef __TREEFUNCS_H
#define __TREEFUNCS_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Structs:
typedef struct treeNode
{
    unsigned int data;
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

typedef struct tree
{
    TreeNode *root;
} Tree;

//Functions
void checkMemoryAllocation(void *);
TreeNode *createNewTreeNode(int, TreeNode *, TreeNode *);
void printTreeInorder(Tree);
void printTreeInOrderHepler(TreeNode *);
void freeTree(Tree);
void freeTreeHelper(TreeNode *);
#endif