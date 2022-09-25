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

#include "colorchooser.h"
#include <QString>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <math.h>
using namespace std;

static const TColorTable ColorTable = {
    {"Black",   0xff1c1c1c, 0x04},
    {"Blue",    0xff0000ff, 0x03},
    {"Brick",   0xff94321c, 0x18},
    {"Brown",   0xff756046, 0x06},
    {"Cantaloupe", 0xffff9a00,  0x19},
    {"Cyan",    0xff00ffff, 0x07},
    {"Forest",  0xff006b00, 0x08},
    {"Green",   0xff00ff00, 0x02},
    {"Magenta", 0xffe71cd9, 0x17},
    {"Mud",     0xff463b2b, 0x1a},
    {"Navy",    0xff32326b, 0x1b},
    {"Olive",   0xffbaba59, 0x1c},
    {"Orange",  0xffff8800, 0x0b},
    {"Parchment", 0xffffffba,   0x0c},
    {"Pink",    0xffff7be1, 0x0d},
    {"Purple",  0xff7b00e0, 0x0e},
    {"Red",     0xffff0000, 0x01},
    {"Royalty", 0xff7b00a8, 0x10},
    {"Silver",  0xffe0e0e0, 0x11},
    {"Sky",     0xffbad4ff, 0x12},
    {"Slate",   0xff595959, 0x1d},
    {"Tan",     0xffffedb2, 0x13},
    {"Tangerine", 0xffad652b,   0x14},
    {"White",   0xfffefefe, 0x15},
    {"Yellow",  0xffffff00, 0x16}

};

TColorTable ColorChooser::GetArkColorTable()
{
    return ColorTable;
}


void ColorChooser::CalcDist(QRgb rgb)
{
    int rx = qRed(rgb);
    int gx = qGreen(rgb);
    int bx = qBlue(rgb);
    for(auto val : ColorTable)
    {


        int ry = qRed(val.argb);
        int gy = qGreen(val.argb);
        int by = qBlue(val.argb);

        int r = ry - rx;
        int g = gy - gx;
        int b = by - bx;

        double d = std::sqrt(r*r+g*g+b*b);

        cout << val.name << ": " << d << endl;
    }
}

ColorChooser::ColorChooser(QWidget *parent) : QWidget(parent)
{
    mVBox = new QVBoxLayout();
    mBtnSelectAll = new QPushButton("SelectAll");
    mBtnDeselectAll = new QPushButton("Deselect All");
	
	connect(mBtnDeselectAll, SIGNAL(clicked()), this, SLOT(DeselectAll()));
	connect(mBtnSelectAll, SIGNAL(clicked()), this, SLOT(SelectAll()));
	
    QCheckBox * p;
	
	std::stringstream ss;
    std::string backgroundStr("background-color: #");
	
	
	for(auto val : ColorTable)
	{
		ss << backgroundStr << std::hex << val.argb << endl;
        p = new QCheckBox(val.name.c_str());
        p->setMinimumWidth(100);
		mCheckBoxList.push_back(p);
        p->setChecked(true);

        QHBoxLayout * l = new QHBoxLayout();
        l->addWidget(p);
        QWidget * wid = new QWidget;
        wid->setStyleSheet(ss.str().c_str());
        l->addWidget(wid);
        mVBox->addLayout(l);
        ss.str("");
	}

    QHBoxLayout * hbox = new QHBoxLayout();
    hbox->addWidget(mBtnSelectAll);
    hbox->addWidget(mBtnDeselectAll);
    mVBox->addLayout(hbox);
    this->setLayout(mVBox);
}

ColorChooser::~ColorChooser()
{
    for(auto val : mCheckBoxList)
    {
        if(val != 0)
        {
            delete val;
        }
    }
}

TColorTable ColorChooser::GetColorTable()const
{
	TColorTable table;
	size_t i = 0;
	for(auto val : mCheckBoxList)
	{
		if(val->isChecked())
		{
			table.push_back(ColorTable[i]);
		}
		i++;
	}
	return table;
	
}

void ColorChooser::SelectAll()
{
	for(auto val : mCheckBoxList)
	{
		val->setChecked(true);
	}	
}

void ColorChooser::DeselectAll()
{
	for(auto val : mCheckBoxList)
	{
		val->setChecked(false);
	}	
}
	
