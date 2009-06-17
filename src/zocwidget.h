/*
 * Copyright 2009 Alexey Michurin
 * 
 * This file is part of ZOClock.
 * 
 * ZOclock is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * ZOclock is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with ZOClock. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ZOCWIDGET_H_
#define ZOCWIDGET_H_

#include <QFrame>
#include "zocdot.h"
#include "popupmenu.h"
#include "settings.h"

class BinClockWidget : public QFrame
{

    Q_OBJECT

    typedef QFrame Inherited;

private:
    int bound_x0;
    int bound_x1;
    int bound_y0;
    int bound_y1;
    QPalette palettes[2];
    int displayData[2];
    int timerId;
    BinClockDot *displayDots[2][6];
    QPoint click_pos;
    PopupMenu popup_menu;
    Settings settings;

    void setColor(int, QColor &);
    void setOnTop(bool);

    void updateLine(int);
    void updateView();
    void updateState();

public:
    BinClockWidget(int, int, int, int);

    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void move(int x, int y);
    void show();
    void hide();

signals:
    void menu_quit();

public slots:
    void menu_save_setings();
    void menu_ontop();
    void menu_oem_colors();
    void menu_color(int);
    void menu_about();
    void menu_about_qt();
};

#endif
