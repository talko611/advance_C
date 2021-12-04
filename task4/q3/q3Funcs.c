#include "q3Funcs.h"

TreeNode *createNewTreeNode(int data, TreeNode *parent, TreeNode *left, TreeNode *right) {
    TreeNode *new;

    new = (TreeNode *) malloc(sizeof(TreeNode));
    checkMemoryAllocation(new);

    new->data = data;
    new->parent = parent;
    new->left = left;
    new->right = right;

    return new;
}

void checkMemoryAllocation(void *ptr) {
    if (ptr == NULL) {
        printf("Error- memory allocation failed\n");
        exit(1);
    }
}

Tree BuildTreeFromArrayWithLeafList(int *arr, int size) {
    Tree res;

    makeEmptyList(&(res.leafList));
    res.root = BuildTreeFromArrayWithLeafListHelper(arr, size, &(res.leafList));
    return res;
}

TreeNode *BuildTreeFromArrayWithLeafListHelper(int *arr, int size, List *lst) {
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

    if (root->left == NULL && root->right == NULL)//Update leaves list
    {
        insertDataToEndList(lst, root->data);
    }
    if (root->left != NULL) {
        root->left->parent = root;
    }
    if (root->right != NULL) {
        root->right->parent = root;
    }

    return root;
}

ListNode *createNewListNode(int data, ListNode *pNext) {
    ListNode *new;

    new = (ListNode *) malloc(sizeof(ListNode *));
    checkMemoryAllocation(new);

    new->data = data;
    new->next = pNext;

    return new;
}

void makeEmptyList(List *lst) {
    lst->head = lst->tail = NULL;
}

void insertDataToEndList(List *lst, int data) {
    ListNode *new;
    new = createNewListNode(data, NULL);
    insertNodeToEndList(lst, new);
}

void insertNodeToEndList(List *lst, ListNode *new) {
    if (isEmptyList(lst)) {
        lst->head = lst->tail = new;
    } else {
        lst->tail->next = new;
        lst->tail = new;
    }
    new->next = NULL;
}

bool isEmptyList(List *lst) {
    if (lst->head == NULL) {
        return true;
    }
    return false;
}

void printTreeInorder(Tree tr) {
    printTreeInOrderHelper(tr.root);
    printf("\n");
}

void printTreeInOrderHelper(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    printTreeInOrderHelper(root->left);  // Print left sub tree
    printf("%d ", root->data);           // print root
    printTreeInOrderHelper(root->right); // print right subtree
}

void freeTree(Tree tr) {
    freeTreeHelper(tr.root);
    freeList(&(tr.leafList));
}

void freeTreeHelper(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    freeTreeHelper(root->left);
    freeTreeHelper(root->right);
    free(root);
}

void freeList(List *lst) {
    ListNode *saver;

    while (lst->head != NULL) {
        saver = lst->head;
        lst->head = lst->head->next;
        free(saver);
    }
}

void printLeafList(Tree tr) {
    PrintList(&(tr.leafList));
}

void PrintList(List *lst) {
    ListNode *temp = lst->head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

TreeNode *findParent(Tree tr, int parentData, int branchSelect) {
    TreeNode *res;
    res = findParentHelper(tr.root, parentData, branchSelect);
    return res;
}

TreeNode *findParentHelper(TreeNode *root, int parentData, int branchSelect) {
    TreeNode *found = NULL;

    if (root == NULL) //Case empty tree
    {
        return NULL;
    }
    if (root->data == parentData) {
        if (branchSelect) {
            if (root->right == NULL) {
                return root;
            }
        } else {
            if (root->left == NULL) {
                return root;
            }
        }
    }
    found = findParentHelper(root->left, parentData, branchSelect);//Search for node in left subtree
    if (found == NULL) {
        found = findParentHelper(root->right, parentData, branchSelect); //search for node in right subtree
    }

    return found;
}

Tree AddLeaf(Tree tr, TreeNode *p, int branchSelect, int data) {
    TreeNode *newTrNode;
    int saverData;
    bool isLeafExists = isLeaf(p);
    newTrNode = createNewTreeNode(data, p, NULL, NULL);

    if (branchSelect) // Insert tree node to tree
    {
        p->right = newTrNode;
    } else {
        p->left = newTrNode;
    }
    if (isLeafExists == true) {
        replaceData(&(tr.leafList), p->data, data);
    } else {
        if (branchSelect) {
            saverData = findOrientedLeaf(p->left, branchSelect);
            insertDataInPlace(&(tr.leafList), data, saverData, AFTER);
        } else {
            saverData = findOrientedLeaf(p->right, branchSelect);
            insertDataInPlace(&(tr.leafList), data, saverData, BEFORE);
        }
    }
    return tr;
}

void replaceData(List *lst, int dataToReplace, int dataToInsert) {
    ListNode *p1 = lst->head;

    while (p1->data != dataToReplace) {
        p1 = p1->next;
    }
    p1->data = dataToInsert;
}

void insertDataInPlace(List *lst, int data, int orientedLeafData, int flag) {
    ListNode *new;
    new = createNewListNode(data, NULL);

    if (flag == BEFORE) {
        insertNodeBefore(lst, new, orientedLeafData);
    } else {
        insertNodeAfter(lst, new, orientedLeafData);
    }

}

void insertNodeAfter(List *lst, ListNode *new, int afterData) {
    ListNode *p1 = lst->head;

    while (p1 != NULL) {
        if (p1->data == afterData) {
            new->next = p1->next;
            p1->next = new;
            break;
        }
        p1 = p1->next;
    }
}

void insertNodeBefore(List *lst, ListNode *new, int before) {
    ListNode *p1, *p2;

    if (lst->head->data == before)//Case new node needs to enter first
    {
        insertNodeToStartList(lst, new);
    } else {
        p1 = lst->head;
        p2 = lst->head->next;
        while (p2 != NULL) {
            if (p2->data == before) {
                new->next = p2;
                p1->next = new;
                break;
            }
            p2 = p2->next;
            p1 = p1->next;
        }
    }
}

void insertNodeToStartList(List *lst, ListNode *new) {
    if (isEmptyList(lst)) {
        lst->head = lst->tail = new;
        new->next = NULL;
    } else {
        new->next = lst->head;
        lst->head = new;
    }
}

int findOrientedLeaf(TreeNode *root, int branchSelect) {
    int leftSideLeafData, rightSideLeafData;
    if (root == NULL) {
        return -1;
    }
    leftSideLeafData = findOrientedLeaf(root->left, branchSelect);
    rightSideLeafData = findOrientedLeaf(root->right, branchSelect);

    switch (branchSelect) {
        case 1:
            if (rightSideLeafData != -1) {
                return rightSideLeafData;
            } else if (leftSideLeafData != -1) {
                return leftSideLeafData;
            } else {
                return root->data;
            }
            break;
        case 0:
            if (leftSideLeafData != -1) {
                return leftSideLeafData;
            } else if (rightSideLeafData != -1) {
                return rightSideLeafData;
            } else {
                return root->data;
            }
            break;
        default:
            break;
    }
}

bool isLeaf(TreeNode *node) {
    if (node->right == NULL && node->left == NULL) {
        return true;
    }
    return false;
}
