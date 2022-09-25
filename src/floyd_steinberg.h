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

#ifndef FLOYD_STEINBERG_H
#define FLOYD_STEINBERG_H

#include "ditherbase.h"
#include "matrix.h"

class Floyd_Steinberg : public DitherBase
{
public:
    Floyd_Steinberg();
    ~Floyd_Steinberg();

private:
    void Init(int const w, int const h);
    TError & GetError(int row, int col) const;
    void CalcError(int row, int col, TError & error);

    
};

#endif // FLOYD_STEINBERG_H
