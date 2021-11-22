#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct listnode
{
    int *dataPtr;
    struct listnode *next;
} ListNode;

typedef struct list
{
    ListNode *head;
    ListNode *tail;
} List;

// Function declaration
void makeEmptyList(List *lst);
void checkMemoryAllocation(void *ptr);
ListNode *createNewNode(int data, ListNode *next);
bool isEmptyList(List *lst);
void insertNodeToEndList(List *lst, ListNode *newNode);
void insertDataToEndList(List *lst, int data);
void freeList(List *lst);
void printList(List *lst);
List getList();
List merge(List lst1, List lst2);
void insertDataToStartList(List *lst, int data);
void insertNodeToStartList(List *lst, ListNode *newNode);
void copyList(List *dest, List *src);

void main()
{
    List lst1, lst2, mergedList;

    lst1 = getList();
    lst2 = getList();

    mergedList = merge(lst1, lst2);
    printf("Merged list:\n");
    printList(&mergedList);

    freeList(&lst1);
    freeList(&lst2);
    freeList(&mergedList);
}
// Function implementation

List getList()
{
    List res;
    int size, num, i;

    makeEmptyList(&res);

    printf("Please enter the number of items to be entered:\n");
    scanf("%d", &size);

    printf("Please enter the numbers:\n");
    for (i = 0; i < size; i++)
    {
        scanf("%d", &num);
        insertDataToEndList(&res, num);
    }

    return res;
}

void makeEmptyList(List *lst)
{
    lst->head = lst->tail = NULL;
}

void checkMemoryAllocation(void *ptr)
{
    if (ptr == NULL)
    {
        printf("Error- memory allocation falid\n");
        exit(1);
    }
}

ListNode *createNewNode(int data, ListNode *next)
{
    ListNode *newNode;

    // Allocate memory for new node and int* for data
    newNode = (ListNode *)malloc(sizeof(ListNode));
    checkMemoryAllocation(newNode);
    newNode->dataPtr = (int *)malloc(sizeof(int));
    checkMemoryAllocation(newNode->dataPtr);

    *(newNode->dataPtr) = data; // enter data to new node
    newNode->next = next;

    return newNode;
}

void insertNodeToEndList(List *lst, ListNode *newNode)
{
    if (isEmptyList(lst))
    {
        lst->head = lst->tail = newNode;
    }
    else
    {
        lst->tail->next = newNode;
        lst->tail = newNode;
    }
    newNode->next = NULL;
}

bool isEmptyList(List *lst)
{
    if (lst->head == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void insertDataToEndList(List *lst, int data)
{
    ListNode *newNode;
    newNode = createNewNode(data, NULL);
    insertNodeToEndList(lst, newNode);
}

void printList(List *lst)
{
    ListNode *p;

    p = lst->head;
    while (p != NULL)
    {
        printf("%d ", *(p->dataPtr));
        p = p->next;
    }
}

void freeList(List *lst)
{
    ListNode *p1, *p2;

    p1 = lst->head;
    p2 = lst->head->next;

    while (p1 != NULL)
    {
        free(p1->dataPtr);
        free(p1);
        p1 = p2;
        if (p2 != NULL) // To avoid memory leakage
        {
            p2 = p2->next;
        }
    }
}

List merge(List lst1, List lst2)
{
    List res, sLst1, sLst2;
    // case both lists are empty
    if (lst1.head == NULL && lst2.head == NULL)
    {
        makeEmptyList(&res);
        return res;
    } // case 1 list is empty
    if (lst1.head == NULL)
    {
        makeEmptyList(&res);
        copyList(&res, &lst2);
        return res;
    }
    if ((lst2.head == NULL))
    {
        makeEmptyList(&res);
        copyList(&res, &lst1);
        return res;
    } // check who is the the more big head and add it to start list
    if (*(lst1.head->dataPtr) >= *(lst2.head->dataPtr))
    {
        sLst1.head = lst1.head->next;
        sLst1.tail = lst1.tail;
        res = merge(sLst1, lst2);
        insertDataToStartList(&res, *(lst1.head->dataPtr));
    }
    else
    {
        sLst2.head = lst2.head->next;
        sLst2.tail = lst2.tail;
        res = merge(lst1, sLst2);
        insertDataToStartList(&res, *(lst2.head->dataPtr));
    }
    return res;
}

void insertDataToStartList(List *lst, int data)
{
    ListNode *newNode;
    newNode = createNewNode(data, NULL);
    insertNodeToStartList(lst, newNode);
}

void insertNodeToStartList(List *lst, ListNode *newNode)
{
    if (isEmptyList(lst))
    {
        lst->head = lst->tail = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = lst->head;
        lst->head = newNode;
    }
}

void copyList(List *dest, List *src)
{
    ListNode *p;

    p = src->head;
    while (p != NULL)
    {
        insertDataToEndList(dest, *(p->dataPtr));
        p = p->next;
    }
}