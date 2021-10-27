#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int **pointerSort(int *arr, unsigned int size, int ascendFlag);
void mergeSortP(int **arr, int size, int flag);
int **merge(int **arr1, int size1, int **arr2, int size2, int flag);
void copyArr(int **dest, int **src, int size);
int compare(int a, int b, int flag);
void printPointers(int** pointersArr, int size);

void main()
{

    unsigned int size, i;

    int arr[SIZE];

    int **pointers;

    int ascend_flag;

    printf("Please enter the number of items:\n");

    scanf("%u", &size);

    for (i = 0; i < size; i++){
        scanf("%d", &arr[i]);
    }
    printf("please enter ascending/decending flag\n");//remove later
    scanf("%d", &ascend_flag);
    
    pointers = pointerSort(arr, size, ascend_flag);

    printf("The sorted array:\n"); // Print the sorted array

    printPointers(pointers, size);
    
    free(pointers);
}

int** pointerSort(int *arr, unsigned int size, int ascendFlag)
{
    int **pointersArr;

    // allocate new memory for the arry of pointers
    pointersArr = (int **)malloc(sizeof(int*) * size);
    if (pointersArr == NULL)
    {
        printf("Error - memory allocation faild\n");
        exit(1);
    }

    // init the array of pointers
    for (int i = 0; i < size; i++)
    {
        pointersArr[i] = arr + i;
    }

    mergeSortP(pointersArr, size, ascendFlag);

    return pointersArr;
}

void mergeSortP(int **arr, int size, int flag)
{
    int **tempArr = NULL;

    if (size <= 1)
    {
        return;
    }
    mergeSortP(arr, size / 2, flag);
    mergeSortP(arr + size / 2, size - size / 2, flag);
    tempArr = merge(arr, size / 2, arr + size / 2, size - size / 2, flag);
    copyArr(arr, tempArr, size);//copy temp arr to the original arr
    free(tempArr);
}

int **merge(int **arr1, int size1, int **arr2, int size2, int flag)
{
    int index1, index2, indexRes;
    int **res;
    index1 = 0;
    index2 = 0;
    indexRes = 0;

    //allocate new array to combine the two arrays from the function
    res = (int **)malloc(sizeof(int *) * (size1 + size2));
    if (res == NULL)
    {
        printf("Error - memory allocation faild!");
        exit(1);
    }

    while (index1 < size1 && index2 < size2)
    {
        if (compare(*(arr1[index1]), *(arr2[index2]),flag))//use compare to sort in decending/ ascending order according to the flag
        {
            res[indexRes] = arr1[index1];
            index1++;
        }
        else
        {
            res[indexRes] = arr2[index2];
            index2++;
        }
        indexRes++;
    }

    while (index1 < size1)
    {
        res[indexRes] = arr1[index1];
        index1++;
        indexRes++;
    }

    while (index2 < size2)
    {
        res[indexRes] = arr2[index2];
        index2++;
        indexRes++;
    }

    return res;
}

void copyArr(int **dest, int **src, int size)
{
    for (int i = 0; i < size; i++)
    {
        dest[i] = src[i];
    }
}

int compare(a, b, flag) {
    if (flag == 1) {
        return a < b;
    }

    return a > b;
}

void printPointers(int** pointersArr, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", *(pointersArr[i]));
    }
}