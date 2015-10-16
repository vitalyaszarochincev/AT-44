#include "prog.h"


void checkMem(void* buff)
{
    if(!buff)
    {
        __exit(MEMORY_NOT_ALLOCATED);
    }
}

void checkFile(FILE* file, char* name)
{
    if(!file)
    {
        __exit(INCORRECT_FILE, name);
    }
}

void __exit(Errors err, ...)
{
    va_list argList;

    va_start(argList, err);

    switch(err)
    {
    case INCORRECT_PARAMETERS:
        printf("error : INCORRECT PARAMETERS\ncode : %d", INCORRECT_PARAMETERS);
        break;

    case INCORRECT_FILE:
        printf("error : FILE %s NOT FOUND\ncode : %d", va_arg(argList, char*), INCORRECT_FILE);
        break;

    case MEMORY_NOT_ALLOCATED:
        printf("error : MEMORY IS NOT ALLOCATED\ncode : %d", MEMORY_NOT_ALLOCATED);
        break;

    default:
        puts("SUCCESS");
    }

    va_end(argList);
    exit(0);
}

void checkParam(int num)
{
    if(num != REQUIRED_NUM_OF_PARAMETERS)
    {
        __exit(INCORRECT_PARAMETERS);
    }
}

void destroyTable(STRING** table)
{
    destroyFields(table);
    free(table);
}

void destroyFields(STRING** table)
{
    while(*table)
    {
        free(*table);
        table++;
    }
}
