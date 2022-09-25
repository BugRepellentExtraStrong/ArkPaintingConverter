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

#include "sierra.h"

static const float sierra[]={0.0,0.0,0.0,5.0/32,3.0/32,
                             2.0/32,4.0/32,5.0/32,4.0/32,2.0/32,
                             0.0/32,2.0/32,3.0/32,2.0/32,0.0};

static const float sierra2[] = {0.0,0.0,0.0,12.0/32,4.0/32,
                             0.0/32,0.0/32,12.0/32,0.0/32,0.0/32,
                             0.0/32,0.0/32,4.0/32,0.0/32,0.0};

Sierra::Sierra()
{

}

Sierra::~Sierra()
{

}

void Sierra::Init(int const w, int const h)
{
	mError = std::make_unique<Matrix<TError>>(h+2,w+4);
	TError initVal;
	mError->Init(initVal);
}
TError & Sierra::GetError(int row, int col)const
{
    return mError->GetElement(row,col+2);
}

void Sierra::CalcError(int row, int col, TError & error)
{

    for(int i = 0; i < 15; i++)
    {
        TError val = error*sierra[i] + mError->GetElement(row+i/5, col+i%5);
        mError->SetElement(val,row+i/5, col+i%5);
    }
}
