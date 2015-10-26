#include "prog.h"

int main(int argc, char** argv)
{
    int paramCode = checkParameters(argc, argv);

    switch(paramCode)
    {
    case NO_PARAMETERS://downfall
    case MANY_PARAMETERS:
        __exit(paramCode);

    case INCORRECT_TASK:
        __exit(paramCode, argv[1]);

    default:
        task_t task[NUM_OF_TASKS];
        task[0] = task1;
        task[1] = task2;
        task[2] = task3;
        task[3] = task4;
        task[4] = task5;
        task[5] = task6;
        task[6] = task7;
        task[7] = task8;
        task[8] = task9;
        task[9] = task10;

        switch(argc)
        {
        case TWO_PARAMETERS:
            task[paramCode - 1](argv[2], NO_PARAMETERS);

            break;

        case THREE_PARAMETERS:
            task[paramCode - 1](argv[2], atoi(argv[3]));

            break;
        }
    }

    return 0;
}
