#ifndef PROG_H_INCLUDED
#define PROG_H_INCLUDED

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define REQUIRED_NUM_OF_PARAMETERS 2
#define START_SIZE 10
#define HASH_NOT_FOUND -1

#define EXTEND_SIZE(size) ((size) *= (2))

typedef struct
{
    long addr;
    unsigned long long hash_;
    int freq;
}STRING;

typedef enum
{
    INCORRECT_PARAMETERS = 1,
    INCORRECT_FILE = 2,
    MEMORY_NOT_ALLOCATED = 3
}Errors;

void checkParam(int);
void __exit(Errors, ...);
void checkFile(FILE*, char*);
void checkMem(void*);
int readStr(FILE*, STRING**);
STRING** readFile(FILE*);
int findHash(unsigned long long, STRING**);
int findMax(STRING**);
void printMax(FILE*, STRING**, int);
void destroyTable(STRING**);
void destroyFields(STRING**);

#endif /* PROG_H_INCLUDED*/
