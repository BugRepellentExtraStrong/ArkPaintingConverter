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

#include "floyd_steinberg.h"

static const float floyd_steinberg[]={0.0,0.0,7.0/16,3.0/16,5.0/16,1.0/16};

Floyd_Steinberg::Floyd_Steinberg()
{

}

Floyd_Steinberg::~Floyd_Steinberg()
{
}

void Floyd_Steinberg::Init(int const w, int const h)
{
    mError = std::make_unique<Matrix<TError>>(h+1,w+2);
    TError initVal;
    mError->Init(initVal);
}
TError & Floyd_Steinberg::GetError(int row, int col)const
{
    return mError->GetElement(row,col+1);
}

void Floyd_Steinberg::CalcError(int row, int col, TError & error)
{

    for(int i = 0; i < 6; i++)
    {
        TError val = error*floyd_steinberg[i] + mError->GetElement(row+i/3, col+i%3);
        mError->SetElement(val,row+i/3, col+i%3);
    }
}
