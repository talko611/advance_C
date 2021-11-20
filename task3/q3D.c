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
int insertCoordinate(List *coordList, int x, int y);
void printList(List *lst);
void insertXNodeAfter(XListNode *after, XListNode *newNode); // insert x node between 2 nodes
XListNode *findXNode(List *lst, int x, int y, int *found);   // search for same x coordinate if found return match x node if not found create new coordinate and insert in correct place
void insertDataToStartYList(YList *lst, int data);
void insertYNodeToStartList(YList *lst, YListNode *newNode);
void insertDataAfterYnode(YListNode *after, int data);
void insertYcooradinate(YList *lst, int y, int *found); // checks if y coordinate is exists and add new y to correct location
int insertCoordinate(List *coordList, int x, int y);

void main()
{
    List coordList;
    int x, y;
    int res;

    coordList = getCoordList();
    // get the (x,y) to insert
    scanf("%d%d", &x, &y);
    res = insertCoordinate(&coordList, x, y);

    if (res == 0)
    {
        printf("The point (%d,%d) didn't appear\n", x, y);
    }
    else
    {
        printf("The point (%d,%d) already appeared\n", x, y);
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

int insertCoordinate(List *coordList, int x, int y)
{
    XListNode *xNode;
    int res = 0, foundX = 0, foundY = 0;

    xNode = findXNode(coordList, x, y, &foundX); // look for match coordinate or insert new one;
    if (foundX == 1)
    {                                                      // case x is found
        insertYcooradinate(&(xNode->listOfY), y, &foundY); // check if y is found and insert y cooradinate
        if (foundY == 1)
        {
            res = 1;
        }
    }
    return res;
}

void insertYcooradinate(YList *lst, int y, int *found)
{
    YListNode *p1, *p2, *temp;

    p1 = lst->head;
    p2 = lst->head->nextY;

    if (p1->data == y)
    { // case y coordinate is in beginnig of the list
        insertDataToStartYList(lst, y);
        *found = 1;
    }
    else if (p1->data > y)
    { // case head cooradinate is bigger than y
        insertDataToStartYList(lst, y);
    }
    else // look for y in the middle of the list
    {
        while (p2 != NULL)
        {
            if (p2->data == y)
            {
                insertDataAfterYnode(p2, y);
                *found = 1;
                break;
            }
            else if (p2->data > y)
            {
                insertDataAfterYnode(p1, y);
                break;
            }
            p1 = p1->nextY;
            p2 = p2->nextY;
        }
    }
    if (p2 == NULL) // case not found in list
    {
        insertDataToEndYList(lst, y);
    }
}

void insertDataToStartYList(YList *lst, int data)
{
    YListNode *newNode;
    newNode = createNewYNode(data, NULL);
    insertYNodeToStartList(lst, newNode);
}

void insertYNodeToStartList(YList *lst, YListNode *newNode)
{
    if (isYListEmpty(lst))
    {
        lst->head = lst->tail = newNode;
        newNode->nextY = NULL;
    }
    else
    {
        newNode->nextY = lst->head;
        lst->head = newNode;
    }
}

void insertDataAfterYnode(YListNode *after, int data)
{
    YListNode *newNode;
    newNode = createNewYNode(data, NULL);

    newNode->nextY = after->nextY;
    after->nextY = newNode;
}

XListNode *findXNode(List *lst, int x, int y, int *found)
{
    XListNode *res = NULL, *newNode, *p = lst->head;

    while (p != NULL)
    {
        if (p->data == x)
        { // case found node with same x set res to the node and update found to 1
            res = p;
            *found = 1;
            break;
        }
        else if (p->data > x)
        {                                           // case find node with bigger x in list
            res = createNewXNode(x, y, NULL, NULL); // create new node
            insertXNodeAfter(p->prevX, res);        // insert node between
            break;
        }
        p = p->nextX;
    }
    if (res == NULL)
    { // case reach to null or empty list
        res = createNewXNode(x, y, NULL, NULL);
        insertXNodeToEndList(lst, res);
    }
    return res;
}

void insertXNodeAfter(XListNode *after, XListNode *newNode)
{
    newNode->nextX = after->nextX;
    newNode->prevX = after;
    after->nextX->prevX = newNode;
    after->nextX = newNode;
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
