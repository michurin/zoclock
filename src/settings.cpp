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
const QString Settings::FIELD_COLOR_0("window/color_0");
const QString Settings::FIELD_COLOR_1("window/color_1");
const QString Settings::FIELD_LOCK("window/lock");
const QString Settings::FIELD_TOP("window/ontop");
const QString Settings::FIELD_HOURS_MODE("view/hours_mode");
const QString Settings::FIELD_NUM_BASE("tooltip/num_base");
const QString Settings::FIELD_TT_TIME("tooltip/show_time");
const QString Settings::FIELD_TT_UNIXTIME("tooltip/show_unix_time");
const QString Settings::FIELD_TT_FONT("tooltip/font");
const QString Settings::FIELD_TT_FG("tooltip/foreground");
const QString Settings::FIELD_TT_BG("tooltip/background");

const QString Settings::def_color_0("#333333");
const QString Settings::def_color_1("#009900");
const bool Settings::def_lock(false);
const bool Settings::def_ontop(true);
const int Settings::def_hours_mode(0);
const int Settings::def_num_base(10);
const bool Settings::def_tt_time(true);
const bool Settings::def_tt_unixtime(false);
const QString Settings::def_tt_font("");
const QString Settings::def_tt_fg("#000000");
const QString Settings::def_tt_bg("#ffff66");

Settings::Settings(QPoint const & p)
    : keeper("michurin", "zoclock"),
      def_x(p.x()),
      def_y(p.y())
{
}

void
Settings::getColor(QString const & field, QString const & def, QColor & c) {
    c.setNamedColor(keeper.value(field, def).toString());
    if (! c.isValid()) {
        c = def;
    }
}

void
Settings::read(QPoint & wxy,
               QColor & c0, QColor & c1,
               bool & lock, bool & ontop,
               int & hours_mode, int & num_base,
               bool & tt_time, bool & tt_unixtime,
               QFont & tt_font, QColor & tt_fg, QColor & tt_bg)
{
    wxy = QPoint(keeper.value(FIELD_X, def_x).toInt(),
                 keeper.value(FIELD_Y, def_y).toInt());
    getColor(FIELD_COLOR_0, def_color_0, c0);
    getColor(FIELD_COLOR_1, def_color_1, c1);
    getColor(FIELD_TT_FG, def_tt_fg, tt_fg);
    getColor(FIELD_TT_BG, def_tt_bg, tt_bg);
    lock = keeper.value(FIELD_LOCK, def_lock).toBool();
    ontop = keeper.value(FIELD_TOP, def_ontop).toBool();
    hours_mode = keeper.value(FIELD_HOURS_MODE, def_hours_mode).toInt();
    num_base = keeper.value(FIELD_NUM_BASE, def_num_base).toInt();
    tt_time = keeper.value(FIELD_TT_TIME, def_tt_time).toBool();
    tt_unixtime = keeper.value(FIELD_TT_UNIXTIME, def_tt_unixtime).toBool();
    tt_font.fromString(keeper.value(FIELD_TT_FONT, def_tt_font).toString());
}

void
Settings::write(QPoint const & wxy,
                const QColor & c0, const QColor & c1,
                bool lock, bool ontop,
                int hours_mode, int num_base,
                bool tt_time, bool tt_unixtime,
                QFont const & tt_font, QColor const & tt_fg, QColor const & tt_bg)
{
    keeper.setValue(FIELD_X, wxy.x());
    keeper.setValue(FIELD_Y, wxy.y());
    keeper.setValue(FIELD_COLOR_0, c0.name());
    keeper.setValue(FIELD_COLOR_1, c1.name());
    keeper.setValue(FIELD_LOCK, lock);
    keeper.setValue(FIELD_TOP, ontop);
    keeper.setValue(FIELD_HOURS_MODE, hours_mode);
    keeper.setValue(FIELD_NUM_BASE, num_base);
    keeper.setValue(FIELD_TT_TIME, tt_time);
    keeper.setValue(FIELD_TT_UNIXTIME, tt_unixtime);
    keeper.setValue(FIELD_TT_FONT, tt_font.toString());
    keeper.setValue(FIELD_TT_FG, tt_fg.name());
    keeper.setValue(FIELD_TT_BG, tt_bg.name());
}

void
Settings::get_oem_colors(QColor &c0, QColor &c1, QColor &tt_fg, QColor &tt_bg)
{
    c0 = def_color_0;
    c1 = def_color_1;
    tt_bg = def_tt_bg;
    tt_fg = def_tt_fg;
}
