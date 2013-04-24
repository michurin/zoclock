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

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <QSettings>
#include <QColor>
#include <QPoint>
#include <QFont>

class Settings
{
private:
    QSettings keeper;

    static const QString FIELD_X;
    static const QString FIELD_Y;
    static const QString FIELD_COLOR_0;
    static const QString FIELD_COLOR_1;
    static const QString FIELD_LOCK;
    static const QString FIELD_TOP;
    static const QString FIELD_HOURS_MODE;
    static const QString FIELD_NUM_BASE;
    static const QString FIELD_TT_TIME;
    static const QString FIELD_TT_DATE;
    static const QString FIELD_TT_UNIXTIME;
    static const QString FIELD_TT_FONT;
    static const QString FIELD_TT_FG;
    static const QString FIELD_TT_BG;

    static const QString def_color_0;
    static const QString def_color_1;
    static const bool def_lock;
    static const bool def_ontop;
    static const int def_hours_mode;
    static const int def_num_base;
    static const bool def_tt_time;
    static const bool def_tt_date;
    static const bool def_tt_unixtime;

    QString def_tt_fg;
    QString def_tt_bg;
    QString def_tt_font;

    int def_x;
    int def_y;

    void getColor(QString const &, QString const &, QColor &);

public:
    Settings(QPoint const &);
    void get_oem_colors(QColor &, QColor &, QColor &, QColor &);
    void read(QPoint &, QColor &, QColor &,
             bool &, bool &, int &, int &, bool &, bool &, bool &,
             QFont &, QColor &, QColor &);
    void write(QPoint const &, QColor const &, QColor const &,
             bool, bool, int, int, bool, bool, bool,
             QFont const &, QColor const &, QColor const &);
};

#endif
