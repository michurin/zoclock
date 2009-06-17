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

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <QSettings>
#include <QColor>

class Settings
{
private:
    QSettings keeper;

    static const QString FIELD_X;
    static const QString FIELD_Y;
    static const QString FIELD_R0;
    static const QString FIELD_G0;
    static const QString FIELD_B0;
    static const QString FIELD_R1;
    static const QString FIELD_G1;
    static const QString FIELD_B1;
    static const QString FIELD_LOCK;
    static const QString FIELD_TOP;

    static const int def_r0;
    static const int def_g0;
    static const int def_b0;
    static const int def_r1;
    static const int def_g1;
    static const int def_b1;
    static const bool def_lock;
    static const bool def_ontop;

    int def_x;
    int def_y;

public:
    Settings(int, int);
    void get_oem_colors(QColor &, QColor &);
    void read(int &, int &, QColor &, QColor &, bool &, bool &);
    void write(int, int, const QColor &, const QColor &, bool, bool);
};

#endif
