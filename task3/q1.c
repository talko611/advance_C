#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list_node
{
    char *dataPtr;
    struct list_node *next;
} ListNode;

typedef struct list
{
    ListNode *head;
    ListNode *tail;
} List;

typedef struct student
{
    List first;
    int grade;
} Student;

// Function decletation
void makeEmptyList(List *lst); // sets list to null.
void checkMemoryAllocation(void *ptr);
ListNode *createNewNode(char data, ListNode *next);
bool isEmptyList(List *lst);
void insertNodeToEndList(List *lst, ListNode *newNode);
void insertDataToEndList(List *lst, char data);
void printList(List *lst); // Test func remve later
void freeList(List *lst);  // Test func
void freeNode(ListNode *node);
Student unScramble(List lst);
bool isNumeric(char ch);//checks if the char field contain a number 
void printStudent(Student* student);

void main()
{
    List lst;
    Student student;
    char ch;

    makeEmptyList(&lst);
    printf("Please enter the scrambled student:\n");
    ch = (char)getchar();
    while (ch != '\n')
    {
        insertDataToEndList(&lst, ch);
        ch = (char)getchar();
    }

    student = unScramble(lst);
    printStudent(&student);
    freeList(&student.first);
}

// Function implementation

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

ListNode *createNewNode(char data, ListNode *next)
{
    ListNode *newNode;

    // Allocate memory for new node and char* for data
    newNode = (ListNode *)malloc(sizeof(ListNode));
    checkMemoryAllocation(newNode);
    newNode->dataPtr = (char *)malloc(sizeof(char));
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

void insertDataToEndList(List *lst, char data)
{
    ListNode *newNode;
    newNode = createNewNode(data, NULL);
    insertNodeToEndList(lst, newNode);
}

void printList(List *lst) // Test func
{
    ListNode *curr;

    for (curr = lst->head; curr != NULL; curr = curr->next)
    {
        printf("%c", *(curr->dataPtr));
    }
}

void freeList(List *lst)
{
    ListNode *curr;

    curr = lst->head;
    while (lst->head != NULL)
    {
        lst->head = lst->head->next;
        freeNode(curr);
        curr = lst->head;
    }
}

Student unScramble(List lst)
{
    Student res;
    ListNode *pCurr, *pNext;
    int grade;

    grade = 0;
    pCurr = lst.head;

    while (isNumeric(*(pCurr->dataPtr))) // handle numbers in beginning of list
    {
        grade *= 10;
        grade += *(pCurr->dataPtr) - '0'; // convert char to int
        lst.head = pCurr->next;               // update head to pNext node
        freeNode(pCurr);                      // free number node
        pCurr = lst.head;                     // update pCurr to pNext node
    }
    pNext = pCurr->next; // set pNext to point pCurr pNext node

    while (pNext != NULL) // handle numbers in middle and end of list
    {
        if (isNumeric(*(pNext->dataPtr)))
            {
                grade *= 10;
                grade += *(pNext->dataPtr) - '0';
                pCurr->next = pNext->next;
                freeNode(pNext);
                pNext = pCurr->next;
            }
        else
            {
            pCurr = pCurr->next;
            pNext = pNext->next;
            }
    }
    lst.tail = pCurr;// update tail
    res.first = lst;
    res.grade = grade;

    return res;
}

void freeNode(ListNode *node)
{
    free(node->dataPtr);
    free(node);
}

void printStudent(Student* student){
    printf("First name: ");
    printList(&(student->first));
    printf("\n");
    printf("Grade: %d",student->grade);
}

bool isNumeric(char ch){
    if( ch >= '0' && ch <= '9'){
        return true;
    }
    else{
        return false;
    }
}