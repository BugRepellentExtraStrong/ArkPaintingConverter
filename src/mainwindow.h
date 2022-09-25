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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <vector>

#include <QMainWindow>
#include <QRgb>
#include <QColor>
#include <QUrl>
#include <QVector3D>
#include <QProgressBar>
#include <QTranslator>
#include <QLocale>

#include "matrix.h"
#include "tpainting.h"
#include "drawingarea.h"
#include "colorchooser.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void OpenImage();
    void ConvertImage();
    void SelectImage();

    void PixelXChanged();
    void PixelYChanged();
    void WriteFile();

    void ConvertPntToPng();
    void SaveAsPng();

    void TemplateChanged(int idx);
    void CheckboxClicked();
	
private slots:

	
private:

    static constexpr size_t HEADER_SIZE = 20;

    Ui::MainWindow *ui;
    QUrl mUrl;
    QImage mImage;
    float mScale;
    Matrix<unsigned char> mMatrix;
    ColorChooser * mColorChooser;
    DrawingArea * mDrawingArea1;
    DrawingArea * mDrawingArea2;
    QProgressBar * mProgressBar;
    QTranslator mTranslator;

    std::vector<TPainting> mPaintings;

    std::string const mIniFileName;
};

#endif // MAINWINDOW_H


