#include "list.h"
#include "matrix.h"

Matrix::
Matrix() :
lines(0), columns(0)
{}

Matrix::
Matrix(int constant, size_t dim) :
lines(dim), columns(dim)
{
    Elem* elem = NULL;

    for(size_t i = 0; i < dim; i++)
    {
        elem = new Elem;
        elem->line = i;
        elem->column = i;
        elem->val = constant;
        elemList.pushBack(elem);
    }
}

Matrix::
Matrix(const int** arrMatrix, size_t lines, size_t columns) :
lines(lines), columns(columns)
{
    Elem* elem = NULL;

    for(size_t i = 0; i < lines; i++)
        for(size_t j = 0; j < columns; j++)
            if(arrMatrix[i][j])
            {
                elem = new Elem;
                elem->line = i;
                elem->column = j;
                elem->val = arrMatrix[i][j];
                elemList.pushBack(elem);
            }
}

void Matrix::
print()
{
    Elem* tmp = elemList[0];
    size_t k = 0;

    for(size_t i = 0; i < lines; i++)
    {
        for(size_t j = 0; j < columns; j++)
            if(tmp && (i == tmp->line) && (j == tmp->column))
            {
                cout << tmp->val << " ";
                k++;
                tmp = elemList[k];
            }else
                cout << 0 << " ";

        cout << endl;
    }

    cout << endl;
}

void Matrix::
operator *=(int digit)
{
    for(size_t i = 0; i < elemList.getSize(); i++)
        elemList[i]->val *= digit;
}

void Matrix::
operator +=(Matrix otherMatr)
{
    if((this->lines != otherMatr.lines) || (this->columns != otherMatr.columns))
        return;

    for(size_t i = 0; i < otherMatr.elemList.getSize(); i++)
        if((this->elemList[i]->line == otherMatr.elemList[i]->line) && (this->elemList[i]->column == otherMatr.elemList[i]->column))
            this->elemList[i]->val += otherMatr.elemList[i]->val;
}
