#ifndef __Q2FUNCS_H
#define __Q2FUNCS_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int BOOL;
#define FALSE 0
#define TRUE 1
#define SIZE 100

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

typedef struct tree {
    TreeNode *root;
} Tree;

BOOL isValidParentheses(const char *str, int* parenthesesCounter);//Check if parentheses are correct and updates counter
BOOL isValidNum(char ch);//checks if the character is a number between 0-9
BOOL isValidOperator(char ch);//Checks if character sent is a valid operator
BOOL isStrValid(const char *str);//checks that str contains the right amount of parentheses and only numbers and valid operators
BOOL buildExpressionTree(const char *str, Tree *tr);// check if str is valid and build tree
TreeNode *buildExpressionTreeHelper(const char *str); //use inside buildExpressionTree func -build tree from string
void checkMemoryAllocation(void *ptr);
void freeTreeHelper(TreeNode* root);
void freeTree(Tree* tr);
TreeNode *createNewTreeNode(char data, TreeNode *left, TreeNode *right);
int findRootNodeData(const char *str);//Finds in each string the middle operator or if operator not exists return first num index
int findFirstNum(const char *str);//Finds the first num on the string
char *createNewStr(int size);//create new string pointer
char *copyStr(const char * src, int length);// create new string and copies to new string the amount of chars as length
double calcWithOperator(int num1, int num2, char operator); //return result of two numbers according to operator that sent
double calcExpressionHelper(TreeNode *root);//use inside calc expression
double calcExpression(Tree tr);
#endif