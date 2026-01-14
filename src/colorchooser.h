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

#ifndef COLORCHOOSER_H
#define COLORCHOOSER_H

#include <QWidget>
#include <QCheckBox>
#include <QBoxLayout>
#include <vector>
#include <string>
#include <QPushButton>



struct TColorEntry
{
    std::string name;
    QRgb argb;
    char id;
};

using TColorTable = std::vector<TColorEntry>;


class ColorChooser : public QWidget
{
    Q_OBJECT
public:
    static constexpr int COLOR_EMPTY = 0;

    explicit ColorChooser(QWidget * parent = nullptr, const std::string & file="data/ColorTableEvolved.csv");
    ~ColorChooser();
    bool ReadColorTable(const std::string& filename);
    TColorTable GetColorTable()const;
    TColorTable GetArkColorTable()const;

    void CalcDist(QRgb rgb);

signals:

public slots:
	void SelectAll();
	void DeselectAll();

private:
    TColorTable mColorTable;
    using TCheckBoxList = std::vector<QCheckBox*>;
	TCheckBoxList mCheckBoxList;
    QVBoxLayout * mVBox;
	QPushButton * mBtnSelectAll;
	QPushButton * mBtnDeselectAll;
    
    void PrintColorTable();
};

#endif // COLORCHOOSER_H
