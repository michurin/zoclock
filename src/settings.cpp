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

#include "settings.h"

const QString Settings::FIELD_X("window/pos_x");
const QString Settings::FIELD_Y("window/pos_y");
const QString Settings::FIELD_R0("color_0/red");
const QString Settings::FIELD_G0("color_0/green");
const QString Settings::FIELD_B0("color_0/blue");
const QString Settings::FIELD_R1("color_1/red");
const QString Settings::FIELD_G1("color_1/green");
const QString Settings::FIELD_B1("color_1/blue");
const QString Settings::FIELD_LOCK("window/lock");

const int Settings::def_r0(0);
const int Settings::def_g0(30);
const int Settings::def_b0(0);
const int Settings::def_r1(0);
const int Settings::def_g1(180);
const int Settings::def_b1(0);
const bool Settings::def_lock(false);

Settings::Settings(int x, int y)
    : keeper("michurin", "zoclock"),
      def_x(x),
      def_y(y)
{
}

void
Settings::read(int &x, int &y, QColor &c0, QColor &c1, bool &lock)
{
    x = keeper.value(FIELD_X, def_x).toInt();
    y = keeper.value(FIELD_Y, def_y).toInt();
    int r, g, b;
    r = keeper.value(FIELD_R0, def_r0).toInt();
    g = keeper.value(FIELD_G0, def_g0).toInt();
    b = keeper.value(FIELD_B0, def_b0).toInt();
    c0.setRgb(r, g, b);
    r = keeper.value(FIELD_R1, def_r1).toInt();
    g = keeper.value(FIELD_G1, def_g1).toInt();
    b = keeper.value(FIELD_B1, def_b1).toInt();
    c1.setRgb(r, g, b);
    lock = keeper.value(FIELD_LOCK, def_lock).toBool();
}

void
Settings::write(int x, int y, const QColor &c0, const QColor &c1, bool lock)
{
    keeper.setValue(FIELD_X, x);
    keeper.setValue(FIELD_Y, y);
    int r, g, b;
    c0.getRgb(&r, &g, &b);
    keeper.setValue(FIELD_R0, r);
    keeper.setValue(FIELD_G0, g);
    keeper.setValue(FIELD_B0, b);
    c1.getRgb(&r, &g, &b);
    keeper.setValue(FIELD_R1, r);
    keeper.setValue(FIELD_G1, g);
    keeper.setValue(FIELD_B1, b);
    keeper.setValue(FIELD_LOCK, lock);
}

void
Settings::get_oem_colors(QColor &c0, QColor &c1)
{
    c0.setRgb(def_r0, def_g0, def_b0);
    c1.setRgb(def_r1, def_g1, def_b1);
}
