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

#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QDir>

#include "drawingarea.h"

DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent), mViewScale(1.0)
{
    mPainting.width = 0;
    mPainting.height = 0;
}

void DrawingArea::paintEvent(QPaintEvent * e)
{
    QPainter painter(this);

    QRect sourceRec = mImage.rect();
    QRect targetRec = sourceRec;
    
    if(isTemplate)
    {

        targetRec.setWidth(targetRec.width()*mViewScale * mPainting.ratio);
    }
    else{
        targetRec.setWidth(targetRec.width()*mViewScale);
    }
    targetRec.setHeight(targetRec.height()*mViewScale);
    
	if(mImage.isNull()) return;
    QImage img = mImage.scaled(targetRec.width(),targetRec.height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawImage(0,0,img);
    if(isTemplate)
    {
        painter.drawRect(0,0,mPainting.width*mViewScale* mPainting.ratio,mPainting.height*mViewScale);
    }


}

void DrawingArea::SetImage(QImage const & image)
{
    mImage = image;
    SetScale();
}

void DrawingArea::SetViewScale(int s)
{
    mViewScale = (float)s/100;
    SetScale();
}

void DrawingArea::SetScale()
{

    QRect targetRec = mImage.rect();
    int x;
    if(isTemplate)
        x = std::max(static_cast<size_t>(targetRec.width()*mViewScale*mPainting.ratio),static_cast<size_t>(mPainting.width*mPainting.ratio));
    else
        x = std::max(static_cast<size_t>(targetRec.width()*mViewScale),mPainting.width);

    int y = std::max(static_cast<size_t>(targetRec.height()*mViewScale),mPainting.height);
    this->setFixedSize(x+10,y+10);
    this->repaint();
}

QImage const & DrawingArea::GetImage()const
{
    return mImage;
}

void DrawingArea::SetTemplate(TPainting const & painting)
{
    isTemplate = true;
    mPainting = painting;
}
