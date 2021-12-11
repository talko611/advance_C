#include "/Users/talkoren/sandbox/university/advance_c/task4/treeFuncs.h"

TreeNode *createNewTreeNode(int data, TreeNode *left, TreeNode *right)
{
    TreeNode *new;

    new = (TreeNode *)malloc(sizeof(TreeNode));
    checkMemoryAllocation(new);

    new->data = data;
    new->left = left;
    new->right = right;

    return new;
}

void checkMemoryAllocation(void *ptr)
{
    if (ptr == NULL)
    {
        printf("Error- memory allocation falid\n");
        exit(1);
    }
}

void printTreeInorder(Tree tr)
{
    printTreeInOrderHepler(tr.root);
}

void printTreeInOrderHepler(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    printTreeInOrderHepler(root->left);  // Print left sub tree
    printf("%d ", root->data);           // print root
    printTreeInOrderHepler(root->right); // print right sub tree
}

void freeTree(Tree tr)
{
    freeTreeHelper(tr.root);
}

void freeTreeHelper(TreeNode *root)
{
    if (root == NULL) // Case tree is empty
    {
        return;
    }
    freeTreeHelper(root->left);  // free left sub tree
    freeTreeHelper(root->right); // free right sub tree
    free(root);
}