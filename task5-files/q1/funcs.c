#include "funcs.h"

void Exe5Q1(char *fName, unsigned int x) {
    FILE *input, *output;
    char **strArray;

    input = fopen(fName, "rb");
    checkFileOpen(input);

    strArray = createSrtArray(input, x);

    //write to new text file the result

}

void checkFileOpen(FILE *fp) {
    if (fp == NULL) {
        printf("Opening file failed\n");
        exit(1);
    }
}

char **createSrtArray(FILE *input, unsigned int x) {
    char **res;
    int tempSize;

    res = (char **) malloc(sizeof(char *) * x); // Allocate memory for array of strings
    checkMemoryAllocation(res);

    for (int i = 0; i < x; i++) {
        fread(&tempSize, sizeof(int), 1, input); //Read str size for the ith place in array
        res[i] = (char *) malloc(
                sizeof(char) * (tempSize + 1)); // Allocated memory for the ith string in array (+1 for '\0' at the end)
        checkMemoryAllocation(res[i]);
        fread(res[i], sizeof(char), tempSize, input);// Read string to array
        res[i][tempSize] = '\0';
    }

    return res;
}

void checkMemoryAllocation(void *p) {
    if (p == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
}

void cleanStrArray(char **strArray,  unsigned int size) {
    for(int i = 0; i < size; i++){
        strArray[i] = cleanAndCopyStr(strArray[i]);
    }
    //sort str array
}

char *cleanAndCopyStr(char *src){
    char *res;
    int size = (int) strlen(src) , i, j;

    res = (char*) malloc(sizeof (char) * (size + 1));
    checkMemoryAllocation(res);

    for( i = j = 0; j < size; j++){
        if(src[j] >= 'a' && src[j] <= 'z'){
            res[i] = src[j];
            i++;
        }
    }
    res[i] = '\0';
    realloc(res, i + 1);//Free unused memory if there is any;
    free(src);

    return res;
}

