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

#ifndef DITHERBASE_H
#define DITHERBASE_H

#include <memory>
#include <QImage>
#include <QRgb>
#include <QProgressBar>
#include "colorchooser.h"
#include "matrix.h"

using TError = Vector3D;
class DitherBase
{
public:
    DitherBase();
    virtual ~DitherBase();
    QImage ConvertImage(QImage const & img, TColorTable const & colorTable,
                        float ditherFact, QProgressBar * const progressBar);

    Matrix<unsigned char> & GetColorIdMatrix() const;
protected:
    //Matrix<unsigned char> * mMatrix;
    std::unique_ptr<Matrix<unsigned char>> mMatrix;
    int ConvertPixel(QRgb rgb, TColorTable const & colorTable,
                     TError & errorIn, TError & errorOut);
	std::unique_ptr<Matrix<TError>> mError;

private:

    virtual void Init(int const w, int const h) = 0;
    virtual TError & GetError(int row, int col)const = 0;
    virtual void CalcError(int row, int col, TError & error) = 0;

};

#endif // DITHERBASE_H
