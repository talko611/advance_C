#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct YlistNode
{
    int data;
    struct YlistNode *nextY;
} YListNode;

typedef struct Ylist
{
    YListNode *head;
    YListNode *tail;
} YList;

typedef struct XlistNode
{
    int data;
    YList listOfY;
    struct XlistNode *nextX, *prevX;
} XListNode;

typedef struct list
{
    XListNode *head;
    XListNode *tail;
} List;

// Functions decleration
void checkMemoryAllocation(void *ptr);
void makeEmptyXList(List *lst);
void makeEmptyYList(YList *lst);
bool isXListEmpty(List *lst);
bool isYListEmpty(YList *lst);
void insertYNodeToEndList(YList *lst, YListNode *newNode);
void insertDataToEndYList(YList *lst, int data);
YListNode *createNewYNode(int data, YListNode *pNext);
XListNode *createNewXNode(int dataX, int dataY, XListNode *pNext, XListNode *pPrev);
void insertXNodeToEndList(List *lst, XListNode *newNode);
void insertDataToEndXList(List *lst, int dataX, int dataY);
List getCoordList();
void freeYList(YList *lst);
void freeList(List *lst);
void removeXNode(List *lst, XListNode *toDelete);
void removeYNode(YList *lst, YListNode *after);
unsigned int getPairOccurrences(List coordList, int x, int y, XListNode **foundX, YListNode **foundY); // counts how many times (x,y) is exists and return x and y last occurrance
YListNode *getNodeBefore(YList *lst, YListNode *node);                                                 // gets the yNode before the node sent
int removeCoordinate(List *coordList, int x, int y);
void printList(List *lst);

void main()

{

    List coordList;
    int x, y, res;

    coordList = getCoordList();
    // get the (x,y) to remove
    scanf("%d%d", &x, &y);
    res = removeCoordinate(&coordList, x, y);

    if (res == 1)
    {
        printf("The point (%d,%d) didn't appear\n", x, y);
    }
    else if (res == 2)
    {
        printf("The point (%d,%d) has another occurrence\n", x, y);
    }
    else if (res == 3)
    {
        printf("The point (%d,%d) was the only point with this x\n", x, y);
    }
    else
    {
        printf("Other\n");
    }
    printf("Updated list: ");
    printList(&coordList);
    freeList(&coordList);
}

// Functions implementation
void checkMemoryAllocation(void *ptr)
{
    if (ptr == NULL)
    {
        printf("Error- memory allocation falid\n");
        exit(1);
    }
}

void makeEmptyXList(List *lst)
{
    lst->head = lst->tail = NULL;
}

void makeEmptyYList(YList *lst)
{
    lst->head = lst->tail = NULL;
}

bool isXListEmpty(List *lst)
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

bool isYListEmpty(YList *lst)
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

YListNode *createNewYNode(int data, YListNode *pNext)
{
    YListNode *newNode;
    // allocating new memory for node
    newNode = (YListNode *)malloc(sizeof(YListNode));
    checkMemoryAllocation(newNode);

    // setting node fileds
    newNode->data = data;
    newNode->nextY = pNext;

    return newNode;
}

XListNode *createNewXNode(int dataX, int dataY, XListNode *pNext, XListNode *pPrev)
{
    XListNode *newNode;

    // allocating new memory for new node
    newNode = (XListNode *)malloc(sizeof(XListNode));
    checkMemoryAllocation(newNode);

    newNode->data = dataX; // setting fileds
    newNode->nextX = pNext;
    newNode->prevX = pPrev;
    makeEmptyYList(&(newNode->listOfY));              // setting the y's list
    insertDataToEndYList(&(newNode->listOfY), dataY); // insert y value

    return newNode;
}

void insertDataToEndYList(YList *lst, int data)
{
    YListNode *newNode;

    newNode = createNewYNode(data, NULL);
    insertYNodeToEndList(lst, newNode);
}

void insertYNodeToEndList(YList *lst, YListNode *newNode)
{
    if (isYListEmpty(lst))
    {
        lst->head = lst->tail = newNode;
    }
    else
    {
        lst->tail->nextY = newNode;
        lst->tail = newNode;
    }
    newNode->nextY = NULL;
}

void insertXNodeToEndList(List *lst, XListNode *newNode)
{
    if (isXListEmpty(lst))
    {
        lst->head = lst->tail = newNode;
        newNode->prevX = NULL;
    }
    else
    {
        newNode->prevX = lst->tail;
        lst->tail->nextX = newNode;
        lst->tail = newNode;
    }
    newNode->nextX = NULL;
}

void insertDataToEndXList(List *lst, int dataX, int dataY)
{
    XListNode *newNode;

    newNode = createNewXNode(dataX, dataY, NULL, NULL);
    insertXNodeToEndList(lst, newNode);
}

List getCoordList()
{
    List res;
    int numOfPoints, x, y, lastX;

    makeEmptyXList(&res); // set list to be empty

    printf("please enter number of points:\n");
    scanf("%d %d %d", &numOfPoints, &x, &y);
    lastX = x;
    insertDataToEndXList(&res, x, y); // enter first point.

    for (int i = 1; i < numOfPoints; i++)
    {
        scanf("%d %d", &x, &y);
        if (x == lastX) // case point has same x coordinate
        {
            insertDataToEndYList(&(res.tail->listOfY), y);
        }
        else // case point has different x coordinate
        {
            insertDataToEndXList(&res, x, y);
            lastX = x;
        }
    }
    return res;
}

void freeYList(YList *lst)
{
    YListNode *temp;

    temp = lst->head; // setting temp to current head
    while (lst->head != NULL)
    {
        lst->head = lst->head->nextY; // moving head to next node
        free(temp);                   // free temp node
        temp = lst->head;             // setting temp to current head
    }
}

void freeList(List *lst)
{
    XListNode *temp;

    temp = lst->head; // setting temp to current head
    while (lst->head != NULL)
    {
        lst->head = lst->head->nextX; // moving head to next node
        freeYList(&(temp->listOfY));  // free list of Ys;
        free(temp);                   // free temp node
        temp = lst->head;             // setting temp to current head
    }
}

void removeXNode(List *lst, XListNode *toDelete)
{
    if (lst->head == lst->tail) // case there is only one item in the list
    {
        makeEmptyXList(lst);
    }
    else if (toDelete == lst->head) // case need to delete first item
    {
        lst->head = toDelete->nextX;
        toDelete->nextX->prevX = NULL;
    }
    else if (toDelete == lst->tail)
    {
        toDelete->prevX->nextX = NULL;
        lst->tail = toDelete->prevX;
    }
    else // case in the middle
    {
        toDelete->prevX->nextX = toDelete->nextX;
        toDelete->nextX->prevX = toDelete->prevX;
    }
    // free item
    freeYList(&(toDelete->listOfY));
    free(toDelete);
}

void removeYNode(YList *lst, YListNode *after)
{
    YListNode *toDelete;
    if (after == NULL && lst->head == lst->tail) // case one item in the list
    {
        toDelete = lst->head;
        makeEmptyYList(lst);
    }
    else if (after == NULL) // case first item in the list
    {
        toDelete = lst->head;
        lst->head = lst->head->nextY;
    }
    else if (after->nextY == lst->tail) // case item is in the end
    {
        toDelete = after->nextY;
        after->nextY = toDelete->nextY;
        lst->tail = after;
    }
    else // case in the middle
    {
        toDelete = after->nextY;
        after->nextY = toDelete->nextY;
    }
    free(toDelete);
}

int removeCoordinate(List *coordList, int x, int y)
{
    unsigned int numOfOccurrences;
    int res;
    XListNode *foundX;
    YListNode *foundY, *after;

    numOfOccurrences = getPairOccurrences(*coordList, x, y, &foundX, &foundY);
    if (numOfOccurrences == 0)
    {
        res = 1;
    }
    else if (numOfOccurrences == 1)
    {
        if (foundY == foundX->listOfY.head && foundY == foundX->listOfY.tail) // case y found is the only item in list related to x
        {
            removeXNode(coordList, foundX);
            res = 3;
        }
        else // case there are y isn't the only item in the list but there are no more items with same value as y
        {
            after = getNodeBefore(&(foundX->listOfY), foundY);
            removeYNode(&(foundX->listOfY), after);
            res = 0;
        }
    }
    else // case more than one coordinate with same x y
    {
        after = getNodeBefore(&(foundX->listOfY), foundY);
        removeYNode(&(foundX->listOfY), after);
        res = 2;
    }
    return res;
}

unsigned int getPairOccurrences(List coordList, int x, int y, XListNode **foundX, YListNode **foundY)
{
    XListNode *currX;
    YListNode *currY;
    unsigned int res = 0;

    currX = coordList.head;
    while (currX != NULL)
    {
        if (currX->data == x)
        {
            *foundX = currX;
            currY = currX->listOfY.head;
            while (currY != NULL)
            {
                if (currY->data == y)
                {
                    *foundY = currY;
                    res++;
                }
                currY = currY->nextY;
            }
        }
        currX = currX->nextX;
    }
    return res;
}

YListNode *getNodeBefore(YList *lst, YListNode *node)
{
    YListNode *p, *res;

    if (lst->head == node) // case node is first item
    {
        res = NULL;
    }
    else
    {
        p = lst->head;
        while (p != NULL)
        {
            if (p->nextY == node)
            {
                res = p;
                break;
            }
            p = p->nextY;
        }
    }
    return res;
}

void printList(List *lst)
{
    XListNode *currX;
    YListNode *currY;

    currX = lst->head;
    currY = lst->head->listOfY.head;

    while (currX != NULL)
    {
        while (currY != NULL)
        {
            printf("(%d,%d) ", currX->data, currY->data);
            currY = currY->nextY;
        }
        currX = currX->nextX;
        if (currX != NULL)
        { // To avoid case currX is null
            currY = currX->listOfY.head;
        }
    }
}