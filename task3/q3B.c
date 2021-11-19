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
unsigned int getYOccurrences(List coord_list, int y);

void main()
{

    List coordList;
    int y;
    unsigned int res;

    coordList = getCoordList();
    // get the (*,y) to look for
    scanf("%d", &y);
    res = getYOccurrences(coordList, y);
    printf("The point (*,%d) appears %u times\n", y, res);

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

    newNode = (YListNode *)malloc(sizeof(YListNode)); // allocating new memory for node
    checkMemoryAllocation(newNode);

    newNode->data = data; // setting node fileds
    newNode->nextY = pNext;

    return newNode;
}

XListNode *createNewXNode(int dataX, int dataY, XListNode *pNext, XListNode *pPrev)
{
    XListNode *newNode;

    newNode = (XListNode *)malloc(sizeof(XListNode)); // allocating new memory for new node
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
        if (x == lastX)
        { // case point has same x coordinate
            insertDataToEndYList(&(res.tail->listOfY), y);
        }
        else
        { // case point has different x coordinate
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

unsigned int getYOccurrences(List coordList, int y)
{
    XListNode *currX;
    YListNode *currY;
    unsigned int res = 0;

    currX = coordList.head; // set currX to first node on list

    while (currX != NULL)
    {
        currY = currX->listOfY.head; // set currY to first node of y list
        while (currY != NULL)
        {
            if (currY->data == y)
            { // case value of currY equals to the value we are looking
                res++;
            }
            else if (currY->data > y)
            { // case value of currY is more then value of node(list is sorted)
                break;
            }
            currY = currY->nextY; // move currY to next node
        }
        currX = currX->nextX; // move currX to next node
    }
    return res;
}
