#include "prog.h"

void checkParameters(int num)
{
    if(num != REQUIRED_PARAMETERS_NUM)
    {
        __exit(INCORRECT_PARAMETERS);
    }
}

void __exit(Errors err, ...)
{
    va_list argList;

    va_start(argList, err);
    va_end(argList);

    switch(err)
    {
    case(INCORRECT_PARAMETERS):
        cout << "incorrect parameters" << endl;

        break;

    case(INCORRECT_FILE):
        cout << "file " << va_arg(argList, char*) << " not found" << endl;

        break;
    }

    exit(0);
}

void checkFile(FILE* file, char* name)
{
    if(!file)
    {
        __exit(INCORRECT_FILE, name);
    }
}
