#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Function declaration
char **setPtrToCharsArray(char **str_array);
void checkMemoryAllocation(void *p);
char *getString();
char **getStrArrayInput(unsigned int *strArraySize);
void printArray(char **strArray, int size);
void freeArray(char **strArray, int size);
char *cleanString(char *strP, char **ptrToCharsArray);
bool isPointerExists(char *strPtr, char **ptrToCharsArray); // check one of the pointers in the ptrToCharsArray pointing on one of the string chars
unsigned int removeFromStrArray(char ***strArray, unsigned int strArraySize, char **ptrToCharsArray);

void main()
{
    char **str_array;
    unsigned int str_array_size;
    char **ptr_to_chars_array;
    unsigned int res = 0;

    str_array = getStrArrayInput(&str_array_size); // Get the size and strings from user (can't assume max size for each string)
    ptr_to_chars_array = setPtrToCharsArray(str_array);
    res = removeFromStrArray(&str_array, str_array_size, ptr_to_chars_array);
    printArray(str_array, str_array_size - res);

    //    Free memory
    freeArray(str_array, str_array_size - res);
    free(ptr_to_chars_array);
}

// Function Implementation
char **setPtrToCharsArray(char **str_array)
{
    char **res;
    int size, i;
    int str_array_row, str_array_col;

    scanf("%d", &size);                                 // Get number of ptrs
    res = (char **)malloc(sizeof(char *) * (size + 1)); // Add 1 for NULL at the end
    checkMemoryAllocation(res);                         // remove later

    for (i = 0; i < size; i++)
    {
        scanf("%d", &str_array_row);
        scanf("%d", &str_array_col);
        res[i] = (str_array[str_array_row] + str_array_col);
    }
    res[size] = NULL; // Set the last one to NULL

    return res;
}

char **getStrArrayInput(unsigned int *strArraySize)
{
    char **res;

    scanf("%d", strArraySize);
    getchar();
    res = (char **)malloc(sizeof(char *) * (*strArraySize));
    checkMemoryAllocation(res);

    for (int i = 0; i < (*strArraySize); i++)
    {
        res[i] = getString();
    }
    return res;
}

void checkMemoryAllocation(void *p)
{
    if (p == NULL)
    {
        printf("Memory allocation faild \n");
        exit(1);
    }
}

char *getString()
{
    char *str;
    int logSize = 0, phySize = 1;
    char c;

    str = (char *)malloc(sizeof(char) * phySize);
    checkMemoryAllocation(str);
    c = getchar();

    while (c != '\n')
    {
        if (logSize == phySize) // chek if there is room to enter new char
        {
            phySize *= 2;
            str = (char *)realloc(str, sizeof(char) * phySize);
        }

        str[logSize] = c;
        logSize++;
        c = getchar();
    }

    str = (char *)realloc(str, sizeof(char) * (logSize + 1)); // resize str (+1 for adding '\0')
    str[logSize] = '\0';

    return str;
}

void printArray(char **strArray, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%s\n", strArray[i]);
    }
}

void freeArray(char **strArray, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(strArray[i]);
    }
    free(strArray);
}

unsigned int removeFromStrArray(char ***strArray, unsigned int strArraySize, char **ptrToCharsArray)
{
    char **res;
    char **tempArray, *tempStr;
    int resSize = 0;
    tempArray = *strArray;

    res = (char **)malloc(sizeof(char *) * strArraySize);
    checkMemoryAllocation(res);

    for (int i = 0; i < strArraySize; i++)
    {
        tempStr = cleanString(tempArray[i], ptrToCharsArray); // get string after removing selected chars
        if (tempStr != NULL)
        {
            res[resSize] = tempStr;
            resSize++;
        }
    }

    res = (char **)realloc(res, sizeof(char *) * resSize);
    checkMemoryAllocation(res);
    *strArray = res;
    freeArray(tempArray, strArraySize); // free old array

    return (strArraySize - resSize);
}

bool isPointerExists(char *strPtr, char **ptrToCharsArray)
{
    int index = 0;
    bool res = false;

    while (ptrToCharsArray[index] != NULL)
    {
        if (ptrToCharsArray[index] == strPtr)
        {
            res = true;
            break;
        }
        index++;
    }
    return res;
}

char *cleanString(char *strP, char **ptrToCharsArray)
{
    char *newStr = NULL;
    int logSize = 0, phySize = 1, strPSize = strlen(strP);

    newStr = (char *)malloc(sizeof(char) * phySize);
    checkMemoryAllocation(newStr);

    for (int i = 0; i < strPSize; i++)
    {
        if (isPointerExists(strP + i, ptrToCharsArray) != true)
        {
            if (logSize == phySize)
            {
                phySize *= 2;
                newStr = (char *)realloc(newStr, sizeof(char) * phySize);
                checkMemoryAllocation(newStr);
            }
            newStr[logSize] = strP[i];
            logSize++;
        }
    }
    if (logSize > 0)
    {
        newStr = (char *)realloc(newStr, sizeof(char) * (logSize + 1));
        checkMemoryAllocation(newStr);
        newStr[logSize] = '\0';
    }
    else
    {
        free(newStr);
        return NULL;
    }

    return newStr;
}
