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
