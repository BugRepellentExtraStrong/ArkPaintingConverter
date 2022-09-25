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

#include "jarvisjudiceninke.h"

static const float jarvis_judice_ninke[]={0.0,0.0,0.0,7.0/48,5.0/48,
                                          3.0/48,5.0/48,7.0/48,5.0/48,3.0/48,
                                         1.0/48,3.0/48,5.0/48,3.0/48,1.0/48};

JarvisJudiceNinke::JarvisJudiceNinke()
{

}

JarvisJudiceNinke::~JarvisJudiceNinke()
{

}

void JarvisJudiceNinke::Init(int const w, int const h)
{
    mError = std::make_unique<Matrix<TError>>(h+2,w+4);
    TError initVal;
    mError->Init(initVal);
}
TError & JarvisJudiceNinke::GetError(int row, int col)const
{
    return mError->GetElement(row,col+2);
}

void JarvisJudiceNinke::CalcError(int row, int col, TError & error)
{

    for(int i = 0; i < 15; i++)
    {
        TError val = error*jarvis_judice_ninke[i] + mError->GetElement(row+i/5, col+i%5);
        mError->SetElement(val,row+i/5, col+i%5);
    }
}


