#include "list.h"
#include "matrix.h"
#include <fstream>

///////////////////////////////////////Matrix()/////////////////////////////////////////////////////////

Matrix::Matrix():m_lines(0), m_columns(0) {}

///////////////////////////////////////Matrix(int, size_t)/////////////////////////////////////////////////////////

Matrix::Matrix(int constant, size_t dim):m_lines(dim), m_columns(dim)
{
    Elem* elem = NULL;

    for(size_t i = 0; i < dim; i++)
    {
        elem = new Elem;
        elem->line = i;
        elem->column = i;
        elem->val = constant;
        this->m_elemList.pushBack(elem);
    }
}

///////////////////////////////////////Matrix(const int**, size_t, size_t)/////////////////////////////////////////////////////////

Matrix::Matrix(int** arrMatrix, size_t lines, size_t columns):m_lines(lines), m_columns(columns)
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
                this->m_elemList.pushBack(elem);
            }
}

///////////////////////////////////////print()/////////////////////////////////////////////////////////

void Matrix::print()
{
    std::ofstream testFile("C:\\Users\\vitalii\\Documents\\projects\\matrix\\data\\test.txt", std::ios::app | std::ios::out);

    if(!m_elemList.isEmpty())
    {
        testFile << "<empty>" << endl;
        return;
    }

    Elem* tmp = this->m_elemList[0];
    size_t k = 0;

    for(size_t i = 0; i < this->m_lines; i++)
    {
        for(size_t j = 0; j < this->m_columns; j++)
            if(tmp && (i == tmp->line) && (j == tmp->column))
            {
                testFile << tmp->val << " ";
                k++;
                tmp = this->m_elemList[k];
            }else
                testFile << 0 << " ";

        testFile << endl;
    }

    testFile << endl;
}

///////////////////////////////////////operator *=(int)/////////////////////////////////////////////////////////

void Matrix::operator *=(int digit)
{
    for(size_t i = 0; i < this->m_elemList.getSize(); i++)
        this->m_elemList[i]->val *= digit;
}

///////////////////////////////////////operator +=(Matrix&)/////////////////////////////////////////////////////////

void Matrix::operator +=(Matrix& otherMatr)
{
    if((this->m_lines != otherMatr.m_lines) || (this->m_columns != otherMatr.m_columns))
        return;

    for(size_t i = 0; i < otherMatr.m_elemList.getSize(); i++)
        if((this->m_elemList[i]->line == otherMatr.m_elemList[i]->line) && (this->m_elemList[i]->column == otherMatr.m_elemList[i]->column))
            this->m_elemList[i]->val += otherMatr.m_elemList[i]->val;
}
