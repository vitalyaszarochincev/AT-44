#include "prog.h"

int main()
{
    int arc = 0;
    double angle = 0;
    double high = 0;
    bool flag = false;
    int angleLimit = 0;

    system("color F0");
    printStatus(angle, high);

    while(1)
    {
        if(kbhit())
        {
            arc = getch();
            flag = true;
        }

        switch(arc)
        {
        case UP:
            if(flag)
            {
                if(angle < MAX_ANGLE)
                {
                    angle += OFFSET;
                    angleLimit = 0;
                }else
                    angleLimit = 1;

                flag = false;
            }

            break;

        case DOWN:
            if(flag)
            {
                if(angle > MIN_ANGLE)
                {
                    angle -= OFFSET;
                    angleLimit = 0;
                }else
                    angleLimit = -1;

                flag = false;
            }

            break;

        case EXIT:
            exit(0);
            break;
        }

        high += countHigh(angle);
        Sleep(DELAY);
        printStatus(angle, high);

        if(angleLimit)
        {
            printWarning(angleLimit);
        }

        if(high < MIN_HIGH)
        {
            printError();
            exit(0);
        }
    }

    return 0;
}

void printError()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD) (0xFC));
    cout << "plane crushed!" << endl;
    SetConsoleTextAttribute(hConsole, (WORD) (0xF0));
    system("pause");
}

void printStatus(double angle, double high)
{
    system("cls");
    cout << "press up or down to change angle" << endl << "press esc to exit" << endl << "angle : " << angle << " high : " << high << endl;
}

void printWarning(int status)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD) (0xFC));

    switch (status)
    {
    case 1:
        cout << "maximum angle" << endl;
        break;

    case -1:
        cout << "minimum angle" << endl;
        break;
    }

    SetConsoleTextAttribute(hConsole, (WORD) (0xF0));
}
