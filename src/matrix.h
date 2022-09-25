/*********************************************************************
** Copyright (C) 2022  https://github.com/BugRepellentExtraStrong
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <https://www.gnu.org/licenses/>.
***********************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include <QVector3D>

using Vector3D = QVector3D;

template <typename T>
class Matrix
{
public:
    Matrix():mArr(0),mRow(0), mCol(0){}
    Matrix(size_t const row, size_t const col):mArr(new T[row*col]), mRow(row),mCol(col)
    {
    }
    ~Matrix(){
        if(mArr != 0)
        {
            delete[] mArr;
        }
    }

    Matrix & operator=(Matrix & m)
    {
        if(mArr != 0)
        {
            delete[] mArr; mArr = 0;
        }
        mCol = m.mCol;
        mRow = m.mRow;
        mArr = new T[mRow*mCol];
        for(size_t i = 0; i < mRow*mCol; i++)
        {
            mArr[i] = m.mArr[i];
        }

        return *this;
    }

    void Init(T const & initVal)
    {
        if(mArr == 0) {return;}
        for(size_t i = 0; i < mRow*mCol; i++)
        {
            mArr[i] = initVal;
        }
    }

    T & GetElement(size_t row, size_t col) const
    {
        if (row < mRow && col < mCol)
        {
            return mArr[row*mCol + col];
        }
        else
        {

            return mArr[0];
        }
    }

    void SetElement(T const & val, size_t row, size_t col)
    {
        if (row < mRow && col < mCol)
        {
            mArr[row*mCol + col] = val;
        }
    }
    size_t Cols()const{return mCol;}
    size_t Rows()const{return mRow;}

private:
    T * mArr;
    size_t mRow;
    size_t mCol;
};

#endif // MATRIX_H
