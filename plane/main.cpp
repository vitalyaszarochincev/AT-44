#include "prog.h"

int main()
{
    int arc = 0;
    double angle = 0;
    double high = 0;
    bool flag = false;

    system("color F0");
    system("cls");
    cout << "press up or down to change angle" << endl << "press esc to exit" << endl << "angle : " << angle << " high : " << high;

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
                angle += OFFSET;
                flag = false;
            }

            break;

        case DOWN:
            if(flag)
            {
                angle -= OFFSET;
                flag = false;
            }

            break;

        case EXIT:
            exit(0);
            break;
        }

        high += countHigh(angle);
        Sleep(100);
        system("cls");
        cout << "angle : " << angle << " high : " << high;
    }

    return 0;
}
