#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "list.h"

struct Elem
{
    unsigned line;
    unsigned column;
    int val;
};

class Matrix
{
private:
    List<Elem*> m_elemList;
    size_t m_lines;
    size_t m_columns;

public:
    Matrix();
    Matrix(int, size_t);
    Matrix(int** arrMatrix, size_t, size_t);

    void print();

    void operator *=(int);

    void operator +=(Matrix&);
};

#endif // MATRIX_H_INCLUDED
