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
#include <fstream>
#include <exception>
#include <chrono>
#include <math.h>
#include <sstream>
#include <memory>

#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QVector3D>
#include <QProgressBar>
#include <QMessageBox>

#include "ditherbase.h"
#include "floyd_steinberg.h"
#include "jarvisjudiceninke.h"
#include "sierra.h"
#include "tpainting.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mScale(0.25),mColorChooser(new ColorChooser),
    mDrawingArea1(new DrawingArea),
    mDrawingArea2(new DrawingArea),
    mProgressBar(new QProgressBar),
    mIniFileName("painting.ini"),
    mIniFilePath("../resources/config/")
{
    ui->setupUi(this);

    ui->scrollArea->setWidget(mColorChooser);
    ui->scrollArea_img1->setWidget(mDrawingArea1);
    ui->scrollArea_img2->setWidget(mDrawingArea2);
    
	
    ifstream in(mIniFilePath + mIniFileName);
    if(!in)
    {
        ostringstream os;
        os << "error: couldn't open "<< mIniFileName << " in directory ";
        os << QDir::currentPath().toStdString() + mIniFilePath << endl;
        os << "thrown in File: ";
        os << __FILE__ << " on line: " << __LINE__;
        throw logic_error(os.str());
    }

    constexpr size_t SIZE = 100;
    char buff[SIZE];
    in.getline(buff, SIZE);
    TPainting entry;
    while(!in.eof())
    {
        QString str(buff);
        entry.name = str.section(",",0,0).toStdString();
        entry.saveFileName = str.section(",",1,1).toStdString();
        entry.width = str.section(",", 2,2).toInt();
        entry.height = str.section(",", 3,3).toInt();
        entry.ratio = str.section(",",4,4).toFloat();
        mPaintings.push_back(entry);
        in.getline(buff,SIZE);
    }
    in.close();

    for(auto & val : mPaintings)
    {
        stringstream ss;
        ss << val.name << " " << val.width << "x" << val.height;
        ui->comboBox->addItem(ss.str().c_str());
    }


    mDrawingArea2->SetTemplate(mPaintings[ui->comboBox->currentIndex()]);
    ui->lineEditPixelX->setText(QString::number(mPaintings[ui->comboBox->currentIndex()].width));
    ui->lineEditPixelY->setText(QString::number(mPaintings[ui->comboBox->currentIndex()].height));


    ui->comboBox_2->addItem("FloydSteinberg");
    ui->comboBox_2->addItem("JarvisJudiceNinke");
    ui->comboBox_2->addItem("Sierra");
    
    this->setWindowFlags(Qt::Window);
    
    mProgressBar->setMaximum(100);
    mProgressBar->setMinimum(0);
    mProgressBar->setValue(0);
    
    this->statusBar()->setVisible(true);
	this->statusBar()->addWidget(mProgressBar);

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(TemplateChanged(int)));
    connect(ui->spinBox, SIGNAL(valueChanged(int)), mDrawingArea1, SLOT(SetViewScale(int)));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), mDrawingArea2, SLOT(SetViewScale(int)));
    connect(ui->checkBox, SIGNAL(clicked(bool)),this,SLOT(CheckboxClicked()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::TemplateChanged(int idx)
{
    ui->lineEditPixelX->setText(QString::number(mPaintings[idx].width));
    ui->lineEditPixelY->setText(QString::number(mPaintings[idx].height));
    ui->checkBox->setChecked(false);

}

void MainWindow::OpenImage()
{
    mImage.load(ui->lineEditImgPath->text());
    mDrawingArea1->SetImage(mImage);
}

void MainWindow::CheckboxClicked()
{
    PixelXChanged();
}

void MainWindow::ConvertImage()
{
    unique_ptr<DitherBase> dither;
    switch(ui->comboBox_2->currentIndex())
    {
        case 0:
            dither = make_unique<Floyd_Steinberg>();
            break;

        case 1:
            dither = make_unique<JarvisJudiceNinke>();
            break;

        case 2:
            dither = make_unique<Sierra>();
            break;

        default:
            dither = make_unique<Floyd_Steinberg>();
        break;
    }
    float ditherFact = ui->lineEditDither->text().toFloat();
    int const x = ui->lineEditPixelX->text().toInt();
    int const y = ui->lineEditPixelY->text().toInt();

    mDrawingArea2->SetTemplate(mPaintings[ui->comboBox->currentIndex()]);
    mDrawingArea2->SetImage(dither->ConvertImage(mImage.scaled(x,y),
                         mColorChooser->GetColorTable(),ditherFact,mProgressBar));

    mMatrix = dither->GetColorIdMatrix();

}

void MainWindow::SelectImage()
{
    QString str = QFileDialog::getOpenFileName(this, "Open File", "", "Images (*.png *.jpg)");
    if(str.isEmpty())return;
	ui->lineEditImgPath->setText(str);
    OpenImage();
}

void MainWindow::PixelXChanged()
{
    if(ui->checkBox->isChecked())
    {
        float ratio = static_cast<float>(mImage.width())/mImage.height();
        int x = ui->lineEditPixelX->text().toInt();
        TPainting painting = mPaintings[ui->comboBox->currentIndex()];
        int y = x*painting.ratio/ratio;
        ui->lineEditPixelY->setText(QString::number(y));
    }
}

void MainWindow::PixelYChanged()
{
    if(ui->checkBox->isChecked())
    {
        float ratio = static_cast<float>(mImage.width())/mImage.height();
        int y = ui->lineEditPixelY->text().toInt();
        TPainting painting = mPaintings[ui->comboBox->currentIndex()];
        int x = y*ratio/painting.ratio;
        ui->lineEditPixelX->setText(QString::number(x));
    }
}

void MainWindow::SaveAsPng()
{
    QString str = QFileDialog::getSaveFileName(this, "Save File", "", "Images (*.png *.jpg)");
    if(str.isEmpty()) return;
    QImage m = mDrawingArea2->GetImage();
    m.save(str);
}

void MainWindow::WriteFile()
{
	if(mMatrix.Cols() == 0 || mMatrix.Rows() == 0) return;

    QString saveFileName = QFileDialog::getSaveFileName(this, "Save File", "", "Images (*.pnt)");
    if(saveFileName.isEmpty()) return;
    QFileInfo info(saveFileName);
    QString fileName = info.fileName();

    size_t area_width = 0;
    size_t area_height = 0;

    std::ostringstream ss;
    string PaintingTypeName;
    TPainting painting = mPaintings[ui->comboBox->currentIndex()];
    area_width = painting.width;
    area_height = painting.height;
    PaintingTypeName = painting.saveFileName;


    char header[HEADER_SIZE];
    memset(header,0,HEADER_SIZE);
    header[5] = area_width/HEADER_PIXEL_PER_UNIT;
    header[9] = area_height/HEADER_PIXEL_PER_UNIT;
    header[18] =  header[5]*header[9];

    size_t canvas_width = (mMatrix.Cols()-1)/area_width;
    size_t canvas_height = (mMatrix.Rows()-1)/area_height;
    
    for(size_t y = 0; y < 1+canvas_height;y++)
    {
        for(size_t x = 0; x < 1+canvas_width;x++)
        {
            ss.str("");
            ss << info.absolutePath().toStdString() << "/";
            if(fileName.contains(".pnt"))
                ss << fileName.toStdString().substr(0,fileName.toStdString().size()-4);
            else
                ss << fileName.toStdString();
            ss << "-" << y*(canvas_width+1) + x <<"-y"<<y<<"-x"<<x  << "_" << PaintingTypeName;
            ofstream out(ss.str(), ios_base::out | ios_base::binary);
            if(!out){
                ostringstream os;
                os << "error: couldn't open "<< ss.str() << endl;
                os << "thrown in File: ";
                os << __FILE__ << " on line: " << __LINE__;
                throw logic_error(os.str());
            }

            out.write(header, HEADER_SIZE);
            for(size_t row = area_height*y; row < area_height*(y+1); row++)
            {
                for(size_t col = area_width*x; col < area_width*(x+1); col++)
                {
                    if(row < mMatrix.Rows() && col < mMatrix.Cols())
                    {
                        out.put(mMatrix.GetElement(row,col));
                    }
                    else
                    {
                        out.put(ColorChooser::COLOR_EMPTY);
                    }
                }
            }

            out.close();
        }
    }

	
}

void MainWindow::ConvertPntToPng()
{
    QStringList list = QFileDialog::getOpenFileNames(this, "Select files to convert", "", "Images (*.pnt)");
    QString str;
    for(auto & val : list)
    {
        str = val;
        QFileInfo file(str);
        QString name = file.fileName();
        QString path = file.absoluteFilePath();
        if(!name.contains(".pnt"))
        {
            continue;
        }

       ifstream in(str.toStdString(), ios_base::binary);
       if(!in)
       {
           cerr << "file couldn't be opened: " << str.toStdString() << endl;
           continue;
       }
        vector<unsigned char> vec;
        while(true){
            unsigned char val = in.get();
            if(in.eof()) break;
            vec.push_back(val);

        }
        in.close();

        int const x = vec[5] * HEADER_PIXEL_PER_UNIT;
        int const y = vec[9] * HEADER_PIXEL_PER_UNIT;

        TColorTable table = ColorChooser::GetArkColorTable();
        vector<uchar> arr(x*y*sizeof(QRgb));
        QRgb * p = reinterpret_cast<QRgb*>(&arr[0]);
        for(size_t i = HEADER_SIZE; i < vec.size(); i++)
        {
            unsigned char id = vec[i];
            TColorTable::iterator itor = find_if(table.begin(),table.end(),
                [id](TColorEntry & e){if(e.id == id)return true; return false;});
            if(itor != table.end())
            {
                *p = (*itor).argb;
            }
            else
            {
                *p = ColorChooser::COLOR_EMPTY;
            }
            p++;
        }
        stringstream ss;
        ss << path.toStdString().substr(0,path.toStdString().size()-4) << ".png";
        QImage img(&arr[0], x, y, QImage::Format_ARGB32);
        if(!img.save(ss.str().c_str()))
        {
            cerr << "error save image" << endl;
        }
    }
}


