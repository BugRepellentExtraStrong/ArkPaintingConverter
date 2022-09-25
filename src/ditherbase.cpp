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

#include <iostream>
#include <chrono>
#include <math.h>
#include <memory>

#include <QColor>

#include "ditherbase.h"

using namespace std;

DitherBase::DitherBase():mMatrix(new Matrix<unsigned char>())
{

}
DitherBase::~DitherBase()
{

}

QImage DitherBase::ConvertImage(QImage const & img, TColorTable const & colorTable,
                                float ditherFact, QProgressBar * const progressBar)
{
    if(colorTable.size() == 0){return QImage();}

    int width = img.width();
    int height = img.height();

    mMatrix = make_unique<Matrix<unsigned char>>(height,width);

    Init(width, height);
    
    TError error;

    auto data = make_unique<uchar[]>(width*height*4);
    
    QRgb * p = reinterpret_cast<QRgb*>(data.get());

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int progress = 100*(width*y+x+1)/(width*height);
            progressBar->setValue(progress);
            QRgb color = img.pixel(x,y);
            if(qAlpha(color) != 0)
            {

            int idx = ConvertPixel(color,colorTable,GetError(y,x),error);

            if(ditherFact > 0)
            {
                error = error * ditherFact;
                CalcError(y,x,error);
            }
            *p = colorTable[idx].argb;
            mMatrix->SetElement(colorTable[idx].id,y,x);
            }
            else
            {
                *p = color;
                mMatrix->SetElement(0,y,x);
            }
            p++;
        }
    }
    QImage newImg(data.get(), width, height,QImage::Format_ARGB32);

    return newImg.copy();
}

int DitherBase::ConvertPixel(QRgb rgb, TColorTable const & colorTable,
                             TError & errorIn, TError & errorOut)
{
    int ry = qRed(rgb) + errorIn.x();
    int gy = qGreen(rgb) + errorIn.y();
    int by = qBlue(rgb) + errorIn.z();
    double min = -1;
    int idx = 0;
    int result = 0;


    for(auto val: colorTable)
    {
        int rx = qRed(val.argb);
        int gx = qGreen(val.argb);
        int bx = qBlue(val.argb);

        int r = ry - rx;
        int g = gy - gx;
        int b = by - bx;



        double d = sqrt(r*r+g*g+b*b);

        if(min < 0 || d < min)
        {
            min = d;
            result = idx;

            errorOut.setX(r);
            errorOut.setY(g);
            errorOut.setZ(b);

        }
        idx++;
    }


    return result;
}

Matrix<unsigned char> & DitherBase::GetColorIdMatrix() const
{
    return *mMatrix;
}
