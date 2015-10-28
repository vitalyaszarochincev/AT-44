#include "prog.h"

int checkParameters(int argc, char** argv)
{
    int numOfTask = 0;

    switch(argc)
    {
    case ONLY_EXE://downfall
    case ONE_PARAM:
        return NO_PARAMETERS;

    case TWO_PARAMETERS://downfall
    case THREE_PARAMETERS:
        numOfTask = atoi(argv[1]);

        if((numOfTask >= MIN_TASK) && (numOfTask <= MAX_TASK))
        {
            return numOfTask;
        }else
        {
            return INCORRECT_TASK;
        }

        break;
    }

    return MANY_PARAMETERS;
}

void __exit(int err, ...)
{
    va_list argList;

    va_start(argList, err);

    switch(err)
    {
    case NO_PARAMETERS:
        cout << "too few parameters" << endl;
        break;

    case MANY_PARAMETERS:
        cout << "too many parameters" << endl;
        break;

    case INCORRECT_TASK:
        cout << "incorrect parameter " << va_arg(argList, char*) << endl;
        break;

    case INCORRECT_FILE:
        cout << "incorrect file " << va_arg(argList, char*) << endl;
        break;

    case INCORRECT_NUMBER:
        cout << "incorrect number " << va_arg(argList, int) << endl;
        break;

    case INCORRECT_INDEX:
        cout << "incorrect index " << va_arg(argList, long) << endl;
        break;

    case MEMORY_NOT_ALLOCATED:
        cout << "memory is not allocated" << endl;
        break;
    }

    va_end(argList);
    exit(0);
}

void checkFile(FILE* file, char* fileName)
{
    if(!file)
    {
        __exit(INCORRECT_FILE, fileName);
    }
}

void checkFileFormat(FILE* file, char* fileName)
{
    char contStr[CONTROL_STR_SIZE + 1] = {0};

    fread(contStr, sizeof(char), CONTROL_STR_SIZE, file);

    if(strcmp(contStr, controlStr))
    {
        __exit(INCORRECT_FILE, fileName);
    }
}

void formatFile(FILE* file)
{
    fwrite(controlStr, sizeof(char), CONTROL_STR_SIZE, file);
}

void formatFile(FILE* file, long fileLenght)
{
    fwrite(controlStr, sizeof(char), CONTROL_STR_SIZE, file);
    fwrite(&fileLenght, sizeof(long), 1, file);
}

bool checkFileAndContinue(FILE* file)
{
    return (file ? true : false);
}

char* createFileName(char* oldName)
{
    char* newName = oldName;
    size_t nameLenght = strlen(newName);
    strcpy(&newName[nameLenght - ESCALATION], ".idx");

    return newName;

}