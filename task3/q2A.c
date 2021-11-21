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
    List res;
    ListNode *curr1, *curr2;

    curr1 = lst1.head;
    curr2 = lst2.head;
    makeEmptyList(&res);

    while (curr1 != NULL && curr2 != NULL)
    {
        if (*(curr1->dataPtr) >= *(curr2->dataPtr))
        {
            insertDataToEndList(&res, *(curr1->dataPtr));
            curr1 = curr1->next;
        }
        else
        {
            insertDataToEndList(&res, *(curr2->dataPtr));
            curr2 = curr2->next;
        }
    }
    while (curr1 != NULL)
    {
        insertDataToEndList(&res, *(curr1->dataPtr));
        curr1 = curr1->next;
    }
    while (curr2 != NULL)
    {
        insertDataToEndList(&res, *(curr2->dataPtr));
        curr2 = curr2->next;
    }

    return res;
}