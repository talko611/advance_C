#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define INCREASE 1
#define DECREASE 0
typedef struct monom
{
    int coefficient;
    int power;
} Monom;

// Function Declaration:
void addNewMonom(Monom *polynom, int coefficient, int power, int index); // adds new monom to polymon.
Monom *getPolynom(unsigned int *size);
int IsMonomExists(Monom *polynom, int size, int power);       // check if a monom with the same power is alreay exists and retutn it's index if not found return 0;
void updateMonom(Monom *polynom, int index, int coefficient); // adds to an exists monom the new scand coefficient
void checkMemoryAllocation(void *p);
void checkPolynomSize(Monom **Polynom, int *logSize, int *phySize, int flag); // check if polynom has enough and allocate new memory if needed.
void sortPolynom(Monom *polynom, int size);
void setPolynom(Monom **polynom, int *logSize, int *phySize, int coefficient, int power); // check input and add to exists monom or create new monom  with the input.
void swapPolynom(Monom *polynom, int indexA, int indexB);                                 // swaps places between two monoms
void printPolynom(Monom *poly, int size);
void printPolyMul(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size);
void printPolySum(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size);
void printCoefficient(int coefficient, int power, int index); // help func to print polynom - prints the coefficeint according to monom's index, power and value.
void printPower(int power);                                   // help func to print polynom - prints power according to monom's power value.

void main()
{

    Monom *polynom1, *polynom2;              // The input polynoms
    unsigned int polynom1Size, polynom2Size; // The size of each polynom

    printf("Please enter the first polynom:\n");
    polynom1 = getPolynom(&polynom1Size); // get polynom 1

    printf("Please enter the second polynom:\n");
    polynom2 = getPolynom(&polynom2Size); // get polynom 2

    printf("The multiplication of the polynoms is:\n"); // print the multiplication
    printPolyMul(polynom1, polynom1Size, polynom2, polynom2Size);
    printf("\n");

    printf("The sum of the polynoms is:\n"); // print the sum
    printPolySum(polynom1, polynom1Size, polynom2, polynom2Size);
    printf("\n");

    free(polynom1); // releasing all memory allocations
    free(polynom2);
}

void addNewMonom(Monom *polynom, int coefficient, int power, int index)
{

    polynom[index].coefficient = coefficient;
    polynom[index].power = power;
}

Monom *getPolynom(unsigned int *size)
{
    int coefficient, power, logSize = 0, phySize = 1;
    Monom *res = NULL;
    char c;

    do
    {
        scanf("%d %d", &coefficient, &power);
        if (coefficient != 0)
        {
            setPolynom(&res, &logSize, &phySize, coefficient, power);
        }
        c = getchar();
    } while (c != '\n');
    checkPolynomSize(&res, &logSize, &phySize, DECREASE); // resize polynom size if needed
    *size = logSize;
    sortPolynom(res, *size);

    return res;
}

void setPolynom(Monom **polynom, int *logSize, int *phySize, int coefficient, int power)
{
    int exists;

    exists = IsMonomExists(*polynom, *logSize, power); // check if there is a monom with same power and get it's index;
    if (exists > -1)
    {
        updateMonom(*polynom, exists, coefficient); // adds coefficient to the existing monom
    }
    else
    {
        checkPolynomSize(polynom, logSize, phySize, INCREASE); // check if polynom has room for new monom
        addNewMonom(*polynom, coefficient, power, *logSize);   // add new monom and updates polynom size
        (*logSize)++;
    }
}

int IsMonomExists(Monom *polynom, int size, int power)
{
    int res = -1;
    for (int i = 0; i < size; i++)
    {
        if (polynom[i].power == power)
        {
            res = i;
        }
    }
    return res;
}

void updateMonom(Monom *polynom, int index, int coefficient)
{
    polynom[index].coefficient += coefficient;
}

void checkPolynomSize(Monom **Polynom, int *logSize, int *phySize, int flag)
{
    if (flag)
    {
        if (*logSize == 0)
        {
            *Polynom = (Monom *)malloc(sizeof(Monom) * (*phySize)); // creates new
        }
        else if (*logSize == *phySize)
        {
            *phySize *= 2;
            *Polynom = (Monom *)realloc(*Polynom, sizeof(Monom) * (*phySize)); // increase size * 2
        }
    }
    else
    {
        if (*logSize < *phySize)
        {
            *Polynom = (Monom *)realloc(*Polynom, sizeof(Monom) * (*logSize)); // decrease size to log size val
        }
    }

    checkMemoryAllocation(*Polynom);
}

void checkMemoryAllocation(void *p)
{
    if (p == NULL)
    {
        printf("Memory allocation faild \n");
        exit(1);
    }
}

void sortPolynom(Monom *polynom, int size)
{
    int max, j, i;
    for (i = 0; i < size - 1; i++)
    {
        max = i;
        for (j = i + 1; j < size; j++)
        {
            if (polynom[max].power < polynom[j].power)
            {
                max = j;
            }
        }
        if (max != i)
        {
            swapPolynom(polynom, i, max);
        }
    }
}

void swapPolynom(Monom *polynom, int indexA, int indexB)
{
    Monom temp;

    temp = polynom[indexA];
    polynom[indexA] = polynom[indexB];
    polynom[indexB] = temp;
}

void printPolyMul(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size)
{
    Monom *mutliPoly;
    int logSize, phySize, power, coefficient;

    logSize = 0;
    phySize = polynom1Size * polynom2Size;

    mutliPoly = (Monom *)malloc(sizeof(Monom) * phySize); // allocate new memory for multiplication polynom
    checkMemoryAllocation(mutliPoly);

    for (int i = 0; i < polynom1Size; i++)
    { // multiply polynoms and arrange by need in  multiplication polynom
        for (int j = 0; j < polynom2Size; j++)
        {
            power = polynom1[i].power + polynom2[j].power;
            coefficient = polynom1[i].coefficient * polynom2[j].coefficient;
            setPolynom(&mutliPoly, &logSize, &phySize, coefficient, power);
        }
    }
    checkPolynomSize(&mutliPoly, &logSize, &phySize, DECREASE); // resize if needed
    sortPolynom(mutliPoly, logSize);
    printPolynom(mutliPoly, logSize);
    free(mutliPoly);
}

void printPolySum(Monom *polynom1, unsigned int polynom1Size, Monom *polynom2, unsigned int polynom2Size)
{
    Monom *sumPoly;
    int logSize, phySize, power, coefficient, i;

    logSize = 0;
    phySize = polynom2Size + polynom1Size;

    sumPoly = (Monom *)malloc(sizeof(Monom) * phySize); // allocate memomry for sum polynom
    checkMemoryAllocation(sumPoly);

    for (i = 0; i < polynom1Size; i++)
    { // copy polymon1 to sum polynom
        setPolynom(&sumPoly, &logSize, &phySize, polynom1[i].coefficient, polynom1[i].power);
    }
    for (i = 0; i < polynom2Size; i++)
    { // adds polymon 2 according to polynom 1
        setPolynom(&sumPoly, &logSize, &phySize, polynom2[i].coefficient, polynom2[i].power);
    }
    checkPolynomSize(&sumPoly, &logSize, &phySize, DECREASE); // release memory if needed
    sortPolynom(sumPoly, logSize);
    printPolynom(sumPoly, logSize);
    free(sumPoly);
}

void printCoefficient(int coefficient, int power, int index)
{
    if (power != 0)
    {
        if (coefficient == 1)
        {
            if (index != 0)
            {
                printf("+");
            }
        }
        else if (coefficient == -1)
        {
            printf("-");
        }
        else
        {
            if (index == 0)
            {
                printf("%d", coefficient);
            }
            else
            {
                if (coefficient > 0)
                {
                    printf("+");
                }
                printf("%d", coefficient);
            }
        }
    }
    else
    {
        if (coefficient > 0)
        {
            printf("+");
        }
        printf("%d", coefficient);
    }
}

void printPower(int power)
{
    if (power == 1)
    {
        printf("x");
    }
    else if (power != 1 && power != 0)
    {
        printf("x^%d", power);
    }
}

void printPolynom(Monom *poly, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (poly[i].coefficient != 0)
        {
            printCoefficient(poly[i].coefficient, poly[i].power, i);
            printPower(poly[i].power);
        }
    }
}
