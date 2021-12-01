#include "q3Funcs.h"

TreeNode* createNewTreeNode(int data, TreeNode* parent, TreeNode* left,TreeNode* right)
{
    TreeNode* new;

    new = (TreeNode*)malloc(sizeof(TreeNode));
    checkMemoryAllocation(new);

    new->data = data;
    new->parent = parent;
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

Tree BuildTreeFromArrayWithLeafList(int *arr, int size)
{
    Tree res;
    
    makeEmptyList(&(res.leafList));
    res.root = BuildTreeFromArrayWithLeafListHelper(arr, size, &(res.leafList));
    return res;
}

TreeNode *BuildTreeFromArrayWithLeafListHelper(int *arr, int size, List* lst)
{
    TreeNode *root;

    if (size == 0) // Case get empty array
    {
        return NULL;
    }
    if (*(arr + (size / 2)) == -1) // Case data is < 0
    {
        return NULL;
    }

    root = createNewTreeNode(*(arr + (size / 2)), NULL, NULL, NULL);
    root->left = BuildTreeFromArrayWithLeafListHelper(arr, size / 2, lst);
    root->right = BuildTreeFromArrayWithLeafListHelper(arr + ((size / 2) + 1), size / 2, lst);

    if(root->left == NULL && root->right == NULL)//Update leaves list
    {
        insertDataToEndList(lst, root->data);
    }
    if(root->left != NULL){
        root->left->parent = root;
    }
    if(root->right != NULL)
    {
        root->right->parent = root;
    }

    return root;
}

ListNode* createNewListNode(int data, ListNode* pNext)
{
    ListNode* new;

    new = (ListNode*)malloc(sizeof(ListNode*));
    checkMemoryAllocation(new);

    new->data = data;
    new->next = pNext;

    return new;
}

void makeEmptyList(List* lst)
{
    lst->head = lst->tail = NULL;
}

void insertDataToEndList(List* lst, int data)
{
    ListNode* new;
    new = createNewListNode(data, NULL);
    insertNodeToEndList(lst, new);
}

void insertNodeToEndList(List* lst, ListNode* new)
{
    if(isEmptyList(lst))
    {
        lst->head = lst->tail = new;
    }
    else
    {
        lst->tail->next = new;
        lst->tail = new;
    }
    new->next = NULL;
}

bool isEmptyList(List* lst)
{
    if(lst->head == NULL)
    {
        return true;
    }
    return false;
}

void printTreeInorder(Tree tr)
{
    printTreeInOrderHepler(tr.root);
    printf("\n");
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
    freeList(&(tr.leafList));
}

void freeTreeHelper(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    freeTreeHelper(root->left);
    freeTreeHelper(root->right);
    free(root);
}

void freeList(List* lst)
{
    ListNode* saver;

    while(lst->head != NULL){
        saver = lst->head;
        lst->head = lst->head->next;
        free(saver);
    }
}

void printLeafList(Tree tr)
{
    PrintList(&(tr.leafList));
}

void PrintList(List* lst)
{
    ListNode* temp = lst->head;
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}
