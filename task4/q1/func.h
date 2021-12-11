#ifndef __FUNC_H
#define __FUNC_H
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

// Functions
Tree BuildTreeFromArray(int *, int);
void checkMemoryAllocation(void *);
TreeNode *createNewTreeNode(int, TreeNode *, TreeNode *);
TreeNode *bulidTreeFromArrayHelper(int *, int); // Use in build tree from array function
void printTreeInorder(Tree);
void printTreeInOrderHepler(TreeNode *); // Use in print tree in order function  -print tree by using the root
void freeTree(Tree);
void freeTreeHelper(TreeNode *); // Use in free tree function - free tree by useing the root
#endif