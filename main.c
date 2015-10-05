#include <stdio.h>

#define NUM_OF_BITS 32
#define SIGN 1
#define EXP 8
#define _9TH_BIT 0x800000
#define MANT 23
#define OFFSET 127

typedef union
{
    unsigned long ulong_t;
    float float_t;
} NUM;

void toBin(unsigned int, char*);
unsigned long getMant(unsigned long);
unsigned getSign(unsigned);
unsigned getExp(unsigned);
unsigned getInt(unsigned long, int);
unsigned getFract(unsigned long, int);
void toReal(unsigned long, int, char*);

int main()
{
	unsigned realExp = 0;
	unsigned mant = 0;
	unsigned sign = 0;
	unsigned exp = 0;
	unsigned int_p = 0;
	unsigned fract = 0;
	NUM num = {0};
	char str[NUM_OF_BITS + 1] = {0};

    puts("enter number:");
    scanf("%f", &num.float_t);
    toBin(num.ulong_t, str);

    mant = getMant(num.ulong_t);
    sign = getSign(num.ulong_t);
    exp = getExp(num.ulong_t);
    realExp = exp - OFFSET;
    int_p = getInt(mant, realExp);
    fract = getFract(mant, realExp);

    toBin(num.ulong_t, str);
    printf("\nbinary:\n%s\n", str);
    toBin(mant, str);
    printf("\nmantis:\n%s\n", str);
    toBin(sign << (MANT + EXP), str);
    printf("\nsign:\n%s\n", str);
    toBin(exp << MANT, str);
    printf("\nexponent:\n%s\n", str);
    toBin(int_p << (MANT - realExp), str);
    printf("\ninteger:\n%s\n", str);
    toBin(fract, str);
    printf("\nfraction:\n%s\n", str);
    toReal(mant, realExp, str);
    printf("\nreal:\n%d.%s", int_p, str);

    return 0;
}

void toBin(unsigned num, char* str)
{
	int i;
	int j = 0;
	char tmp = 0;

	for (i = 0; i < NUM_OF_BITS; i++)
	{
		str[i] = (num % 2) + '0';
		num /= 2;
	}

	for(i = 0, j = NUM_OF_BITS - 1; i < j; i++, j--)
    {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}

unsigned long getMant(unsigned long num)
{
	num <<= SIGN + EXP;
	num >>= SIGN + EXP;
	num |= _9TH_BIT;

	return num;
}

unsigned getSign(unsigned num)
{
	num >>= MANT + EXP;

	return num;
}

unsigned getExp(unsigned num)
{
	num <<= SIGN;
	num >>= MANT + SIGN;

	return num;
}

unsigned getInt(unsigned long mant, int realExp)
{
    unsigned long fract = MANT - realExp;
    unsigned int_p = mant;

    int_p >>= fract;

    return int_p;
}

unsigned getFract(unsigned long mant, int realExp)
{
    unsigned fract = mant;

	fract <<= SIGN + EXP + realExp;
	fract >>= SIGN + EXP + realExp;

	return fract;
}

void toReal(unsigned long mant, int realExp, char* str)
{
	unsigned long dig = 0;
	int i = 0;
	int j = 0;

	mant <<= SIGN + EXP + realExp;
	mant >>= SIGN + EXP + realExp;

	for (i = SIGN + EXP + realExp, j = 0; i < NUM_OF_BITS; i++, j++)
	{
		mant *= 10;
		dig = mant;
		dig >>= MANT - realExp;

		str[j] = dig + '0';

		mant <<= SIGN + EXP + realExp;
		mant >>= SIGN + EXP + realExp;
	}

	str[j + 1] = '\0';
}
