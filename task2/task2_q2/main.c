#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


typedef struct monom{
    int coefficient;
    int power;
} Monom;

//Function decleration
int* getInpt(int* size);
void checkMemoryAllocation(void* p);
int convertStringToInt(char* string, int size);
int* convertStringToIntArr(char* string, int* size);

void main(){
    int  size;
    int* input;
    input = getInpt(&size);

    for(int i = 0; i < size; i++){
        printf("%d ", input[i]);
    }
    free(input);
}

//Function implementation

int* getInpt(int* size){
    char* userInput;
    char c;
    int logSize, phySize;
    int* res;

    logSize = 0;
    phySize  = 1;
    userInput = (char*) malloc(sizeof(char) * phySize);
    checkMemoryAllocation(userInput);

    c = getchar();
    while (c != '\n'){
        if(logSize == phySize){
            phySize *= 2;
            userInput = (char*) realloc(userInput, sizeof(char) * phySize);
            checkMemoryAllocation(userInput);
        }
        userInput[logSize] = c;
        logSize++;
        c = getchar();
    }
    if(logSize < phySize){
        userInput = (char*) realloc(userInput, sizeof(char) * (logSize + 1));
        checkMemoryAllocation(userInput);
    }
    userInput[logSize] = '\0';
    *size = strlen(userInput);
    res = convertStringToIntArr(userInput, &size);
    free(userInput);

    return res;
}

void checkMemoryAllocation(void* p){
    if(p == NULL){
        printf("Memory allocation faild \n");
        exit(1);
    }
}

int* convertStringToIntArr(char* string, int* size){
    int *arr, logSize, phySize, tempNum;
    char sep = " ";
    char *token;

    logSize = 0;
    phySize = 1;

    arr = (int*) malloc(sizeof(int) * phySize);
    checkMemoryAllocation(arr);

    token = strtok(string, sep);
    while (token != NULL)
    {
        if(logSize == phySize){
            phySize *= 2;
            arr = (int*) realloc(arr, sizeof(int) * phySize);
            checkMemoryAllocation(arr);
        }
        arr[logSize] = convertStringToInt(token, strlen(token));
        logSize++;
        token = strtok(NULL, sep);
    }
    if(logSize < phySize){
        arr = (int*) realloc(arr, sizeof(int) * logSize);
        checkMemoryAllocation(arr);
    }
    *size = logSize ;
    return arr;
}

int convertStringToInt(char* string, int size){
    int number , j;
    number = 0;
    j = pow(10, size - 1);

    for(int i = 0; i < size; i++){
        number += (string[i] - '0') * j;
        j /= 10;
    }
    return number;
}

