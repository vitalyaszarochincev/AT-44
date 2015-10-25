#include "prog.h"

void writeArrToFile(FILE* file)
{
    vector<int> readedDig;

    int digit = 1;

    while(digit)
    {
        cin >> digit;

        if(!isdigit(digit))
        {
            readedDig.push_back(digit);
        }
    }

    for(size_t i = 0; i < readedDig.size() - 1; i++)
    {
        fwrite(&readedDig[i], sizeof(int), 1, file);
    }
}

void readDigFromFile(FILE* file, int num)
{
    fseek(file, (num - 1) * sizeof(int), SEEK_SET);

    int digit = 0;

    fread(&digit, sizeof(int), 1, file);

    if(feof(file) || (num <= 0))
    {
        __exit(INCORRECT_NUMBER, num);
    }

    cout << digit << endl;
}
