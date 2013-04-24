/*
 * Copyright 2009-2013 Alexey Michurin
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
#include <QLabel>
#include <QPalette>
#include <QDateTime>
#include "popupmenu.h"
#include "settings.h"

class BinClockWidget : public QFrame
{

    Q_OBJECT

    typedef QFrame Inherited;

private:

    static const QString TOOLTIP_TIME_SEPERATOR;
    static const QString TOOLTIP_DATE_SEPERATOR;
    static const QString TOOLTIP_TIME_AM_SIG;
    static const QString TOOLTIP_TIME_PM_SIG;
    static const QString TOOLTIP_TIME_LSEPERATOR;

    QRect screen_geometry;
    QPalette palettes[2];
    int timerId;
    QDateTime wall_clock_datetime;
    int wall_clock_hour;
    int wall_clock_minute;
    int wall_clock_time;
    QFrame displayDots[2][6];
    QPoint click_pos;
    Settings settings;
    QLabel popup_tip;
    PopupMenu popup_menu;

    void setColor(int, QColor const &);
    void setOnTop(bool);

    int wallClockHour();
    void updateLine(int, int);
    void updateView();
    void appendToToolTip(int, QString &);
    void updateToolTip(bool);
    bool updateWallClock();
    void updateState(bool);
    void setToolTipColor(QPalette::ColorRole);
    void setToolTipColors(QColor const &, QColor const &);

public:
    BinClockWidget(QRect const &);

    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

    void move(QPoint const &);
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
    void menu_hours_mode();
    void menu_tooltip_font();
    void menu_tooltip_bg();
    void menu_tooltip_fg();
};

#endif
