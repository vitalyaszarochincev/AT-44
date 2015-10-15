#include "prog.h"

int main(int argc, char* argv[])
{
    FILE* file = NULL;
    STRING** table = NULL;
    int max = 0;

    checkParam(argc);

    file = fopen(argv[1], "r");
    checkFile(file, argv[1]);
    table = readFile(file);
    max = findMax(table);
    printMax(file, table, max);
    return 0;
}

int readStr(FILE* file, STRING** table)
{
    int chr = 0;
    long addr = 0;
    unsigned long long hash = 0;
    int i = 0;

    addr = ftell(file);

    while(EOF != (chr = fgetc(file)))
    {
        if(chr == '\n' || chr == 0)
        {
            break;
        }

        hash += hash * 255 + chr;
    }

    i = findHash(hash, table);

    if(table[i])
    {
        table[i]->freq++;
    }else
    {
        table[i] = (STRING*)malloc(sizeof(STRING));
        checkMem(table[i]);
        table[i]->addr = addr;
        table[i]->freq = 1;
        table[i]->hash_ = hash;
    }

    return ((chr == EOF) ? 0 : 1);
}

int findHash(unsigned long long hash, STRING** table)
{
    int i = 0;

    for(i = 0; table[i]; i++)
    {
        if(table[i])
        {
            if(table[i]->hash_ == hash)
            {
                break;
            }
        }
    }

    return i;
}

STRING** readFile(FILE* file)
{
    STRING** table = NULL;
    size_t tableSize = 0;
    size_t maxTableSize = START_SIZE;

    table = (STRING**)calloc(START_SIZE, sizeof(STRING*));
    checkMem(table);

    while(readStr(file, table))
    {
        tableSize++;

        if(maxTableSize == (tableSize - 1))
        {
            EXTEND_SIZE(maxTableSize);
            table = (STRING**)realloc(table, maxTableSize);

            memset(&table[tableSize], 0, sizeof(STRING*) * (maxTableSize - tableSize));

            checkMem(table);
        }
    }
    return table;
}

int findMax(STRING** table)
{
    int max = 0;
    int i = 0;

    for(i = 0; table[i]; i++)
    {
        if(max < table[i]->freq)
        {
            max = table[i]->freq;
        }
    }

    for(i = 0; table[i]; i++)
    {
        if(max == table[i]->freq)
        {
            break;
        }
    }

    return i;
}

void printMax(FILE* file, STRING** table, int max)
{
    int chr = 0;

    fseek(file, table[max]->addr, SEEK_SET);

    while(EOF != (chr = fgetc(file)))
    {
        putc(chr, stdout);

        if((chr == '\0') || (chr == '\n'))
        {
            break;
        }
    }
}
