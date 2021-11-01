#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct monom{
    int coefficient;
    int power;
} Monom;

//Function decleration
Monom* getPolynom(int* size);
void checkMemoryAllocation(void* p);
Monom* copyToZippedArr(Monom** pPolynom, int logSize);
Monom** allocateNewPolynom(Monom** pPolynom, int* logSize, int* phySize);
Monom* addNewMonom(int coefficient, int power);
Monom* findPow(Monom** pPolymon, int size, int pow);
void printPolynom(Monom* poly, int size);
void freepPolynom(Monom** pPolynom, int size);
void swapPolynom(Monom* polynom, int indexA, int indexB);
void sortPolynom(Monom* polynom, int size);
void printPolySum(Monom* polynom1, int size1, Monom* polynom2, int size2);
char chekSign(int a);
void  printPolyMul(Monom* polynom1, int polynom1Size, Monom* polynom2, int polynom2Size);


void main(){
    Monom *polynom1, *polynom2;             // The input polynoms
    int polynom1Size,polynom2Size; // The size of each polynom
 
printf("Please enter the first polynom:\n");
polynom1 = getPolynom(&polynom1Size);   // get polynom 1
printPolynom(polynom1, polynom1Size); 
printf("\n");
printf("Please enter the second polynom:\n");
polynom2 = getPolynom(&polynom2Size);   // get polynom 2
printPolynom(polynom2, polynom2Size);
printf("\n"); 
 
// printf("The multiplication of the polynoms is:\n"); // print the multiplication
printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
printf("\n");
 
// printf("The sum of the polynoms is:\n"); // print the sum
// printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
// printf("\n");
 
free(polynom1); // releasing all memory allocations
free(polynom2);
}

//Function implementation

Monom* getPolynom(int* size){
    int coefficient, pow, logSize = 0, phySize = 1;
    Monom** pPolynom;
    Monom* temp;
    Monom* res;
    char c;

    do {
        pPolynom = allocateNewPolynom(pPolynom, &logSize, &phySize);
        scanf("%d %d", &coefficient, &pow);
        if(coefficient != 0){
            temp = findPow(pPolynom,logSize, pow);
            if(temp == NULL){
                temp = addNewMonom(coefficient, pow);
                pPolynom[logSize] = temp;
                logSize++;
            }else{
                temp->coefficient += coefficient;
            }
        }
        c = getchar();
    }
    while(c != '\n');
    res = copyToZippedArr(pPolynom, logSize);
    sortPolynom(res, logSize);
    *size = logSize;
    freepPolynom(pPolynom,logSize);
    return res;
}

void checkMemoryAllocation(void* p){
    if(p == NULL){
        printf("Memory allocation faild \n");
        exit(1);
    }
}

Monom* findPow(Monom** pPolymon, int size, int pow){
    int i;
    Monom* res = NULL;

    for(i = 0; i < size; i++){
        if(pPolymon[i]->power == pow){
            res = pPolymon[i];
        }
    }
    return res;
}

Monom** allocateNewPolynom(Monom** pPolynom, int* logSize, int* phySize){
    if(*logSize == 0){
        pPolynom = (Monom**) malloc(sizeof(Monom*) * (*phySize));
        checkMemoryAllocation(pPolynom);
    }
    else if(*logSize == *phySize){
        (*phySize) *= 2;
        pPolynom = (Monom**) realloc(pPolynom, sizeof(Monom*) * (*phySize));
        checkMemoryAllocation(pPolynom);
    }
    
    return pPolynom;
}

Monom* addNewMonom(int coefficient, int power){
    Monom* newMonom;

    newMonom = (Monom*) malloc (sizeof(Monom));
    checkMemoryAllocation(newMonom);
    newMonom->coefficient = coefficient;
    newMonom->power = power;
    
    return newMonom;
}

Monom* copyToZippedArr(Monom** pPolynom, int logSize){
    Monom* zippedArr;
    zippedArr = (Monom*)malloc(sizeof(Monom) * logSize);

    for(int i = 0; i < logSize; i++){
        (zippedArr[i]).coefficient = pPolynom[i]->coefficient;
        (zippedArr[i]).power = pPolynom[i]->power;
    }

    return zippedArr;
}

void printPolynom(Monom* poly, int size){
    char c;
    for(int i = 0; i < size; i++){
        if(i == 0){
            if(poly[i].power == 0){
                printf("%d", poly[i].coefficient);
            }else{
                printf("%dx^%d", poly[i].coefficient, poly[i].power);
            }
        }else{
            c = chekSign(poly[i].coefficient);
            if(poly[i].power == 0){
                printf("%c%d", c, poly[i].coefficient);
            }
            else{
                printf("%c%dx^%d", c, poly[i].coefficient, poly[i].power);
            }   
        }
    }
}

char chekSign(int a){
    int c = '\0';
    if(a > 0){
        c = '+';
    }
    return c;
}

void freepPolynom(Monom** pPolynom, int size){
    for(int i = 0 ; i < size; i++){
        free(pPolynom[i]);
    }
    free(pPolynom);
}

void sortPolynom(Monom* polynom, int size){
    int max , j, i;
    for(i = 0; i < size - 1; i++){
        max = i;
        for(j = 1; j < size; j++){
            if(polynom[i].power < polynom[j].power){
                max = j;
            }
        }
        if(max != i){
            swapPolynom(polynom, i, max);
        }
    }
}

void swapPolynom(Monom* polynom, int indexA, int indexB){
    Monom temp;

    temp.coefficient = polynom[indexA].coefficient;
    temp.power = polynom[indexA].power;
    polynom[indexA].coefficient = polynom[indexB].coefficient;
    polynom[indexA].power = polynom[indexB].power;
    polynom[indexB].coefficient = temp.coefficient;
    polynom[indexB].power = temp.power;
}

void printPolySum(Monom* polynom1, int size1, Monom* polynom2, int size2){
    Monom* res;
    int resLogSize, resPhySize, indexPoly1, indexPoly2;
    resLogSize = indexPoly1 = indexPoly2 = 0;
    resPhySize = 1;

    res = (Monom*) malloc(sizeof(Monom) * resPhySize);
    checkMemoryAllocation(res);

    while(indexPoly1 < size1 && indexPoly2 < size2){
        if(resLogSize == resPhySize){
            resPhySize++;
            res = (Monom*)realloc(res, sizeof(Monom)*(resPhySize));
            checkMemoryAllocation(res);
        }
        if((polynom1[indexPoly1]).power == (polynom2[indexPoly2]).power){
            if(((polynom1[indexPoly1]).coefficient + (polynom2[indexPoly2]).coefficient) != 0){
                (res[resLogSize]).power = (polynom1[indexPoly1]).power;
                (res[resLogSize]).coefficient = (polynom1[indexPoly1]).coefficient + (polynom2[indexPoly2]).coefficient;
                resLogSize++;
                indexPoly1++;
                indexPoly2++;
                
            }
            indexPoly1++;
            indexPoly2++;
        }
        else if((polynom1[indexPoly1]).power > (polynom2[indexPoly2]).power){
            (res[resLogSize]).coefficient = (polynom1[indexPoly1].coefficient);
            (res[resLogSize]).power = (polynom1[indexPoly1]).power;
            resLogSize++;
            indexPoly1++;
        }
        else{
            (res[resLogSize]).coefficient = (polynom2[indexPoly2].coefficient);
            (res[resLogSize]).power = (polynom2[indexPoly2]).power;
            resLogSize++;
            indexPoly2++;
        }
    }
    while (indexPoly1 < size1)
    {
        if(resLogSize == resPhySize){
            resPhySize++;
            res = (Monom*)realloc(res, sizeof(Monom)*(resPhySize));
            checkMemoryAllocation(res);
        }
        res[resLogSize].power = polynom1[indexPoly1].power;
        res[resLogSize].coefficient = polynom1[indexPoly1].coefficient;
        resLogSize++;
        indexPoly1++;
    }
    while (indexPoly2 < size2)
    {
        if(resLogSize == resPhySize){
            resPhySize++;
            res = (Monom*)realloc(res, sizeof(Monom)*(resPhySize));
            checkMemoryAllocation(res);
        }
        res[resLogSize].power = polynom2[indexPoly2].power;
        res[resLogSize].coefficient = polynom2[indexPoly2].coefficient;
        resLogSize++;
        indexPoly2++;
    }
    printPolynom(res, resLogSize);
    free(res);
}

void  printPolyMul(Monom* polynom1, int polynom1Size, Monom* polynom2, int polynom2Size){
    Monom *multiPoly, *res;
    int multiPolySize, multiIndex = 0;

    multiPolySize = (polynom1Size * polynom2Size);
    multiPoly = (Monom*) malloc(sizeof(Monom) * multiPolySize);
    checkMemoryAllocation(multiPoly);

    for(int i = 0; i < polynom1Size; i++){
        for(int j = 0; j < polynom2Size; j++, multiIndex++){
            multiPoly[multiIndex].coefficient = (polynom1[i].coefficient * polynom2[j].coefficient);
            multiPoly[multiIndex].power = (polynom1[i].power + polynom2[j].power);
        }
    }
    printf("unsorted poly:\n");
    printPolynom(multiPoly, multiPolySize);
    printf("\n");
    sortPolynom(multiPoly, multiPolySize);
    printf("sorted poly:\n");
    printPolynom(multiPoly, multiPolySize);
}
//to do: 
//multi 
//fix sort func;
