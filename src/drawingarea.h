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

#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QWidget>
#include <QPaintEvent>
#include <QImage>
#include <QBoxLayout>
#include "tpainting.h"


class DrawingArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = nullptr);
    void SetImage(QImage const & image);
    QImage const & GetImage()const;
    void SetTemplate(TPainting const & painting);

signals:

public slots:
    void SetViewScale(int s);


protected:
    void paintEvent(QPaintEvent * e);

private:

    void SetScale();

    QImage mImage;
    float mViewScale;
    TPainting mPainting;
    bool isTemplate = false;
    

};

#endif // DRAWINGAREA_H
