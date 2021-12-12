#ifndef TASK5_FILES_FUNCS_H
#define TASK5_FILES_FUNCS_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Exe5Q1(char *fName, unsigned int x);
void checkFileOpen(FILE* fp);
void checkMemoryAllocation(void *p);
char **createSrtArray(FILE *input, unsigned int x);
char *cleanAndCopyStr(char *src);
#endif //TASK5_FILES_FUNCS_H
