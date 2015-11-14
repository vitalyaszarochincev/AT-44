#include "cip.h"

int main(int argc, char** argv)
{
	int parametersCode = checkParameters(argc, argv);
	TASK_F fileProc[] = {encode, decode};
    fileProc[parametersCode](argv[2]);

	return 0;
}

void __exit(Errors errorCode)
{
	switch(errorCode)
	{
	case INCORRECT_PARAMETERS:
		cout << "incorrect parameters" << endl;
		break;

	case INCORRECT_FILE:
		cout << "incorrect file" << endl;
		break;
	}

	exit(0);
}

inline int checkParameters(int argc, char** argv)
{
    switch(argc)
    {
    case REQUIRED_NUM_OF_PARAMETERS:
        if(!strcmp(argv[1], ENCODE))
        {
            return 0;
        }else if(!strcmp(argv[1], DECODE))
        {
            return 1;
        }else
        {
            __exit(INCORRECT_PARAMETERS);
        }

    default:
        __exit(INCORRECT_PARAMETERS);
        break;

    }
}
