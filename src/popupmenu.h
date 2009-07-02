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

#ifndef POPUPMENU_H_
#define POPUPMENU_H_

#include <QMenu>

class PopupMenu : public QMenu
{

    Q_OBJECT

    typedef QMenu Inherited;

private:
    QAction* lock_pos;
    QAction* window_ontop;
    QAction* hours_mode_actions[3];
    QAction* tooltip_dec_action;
    QAction* tooltip_hex_action;
    QAction* tooltip_unixtime_action;
    QAction* tooltip_time_action;
    QAction* tooltip_date_action;
    int hours_mode_idx;

public:
    PopupMenu(QWidget * parent = 0);
    bool is_window_locked();
    void set_window_lock(bool);
    bool is_window_ontop();
    void set_window_ontop(bool);
    int get_hours_mode();
    bool is_hours_ampm_mode();
    bool is_hours_12_mode();
    void set_hours_mode(int);
    int get_base();
    void set_base(int);
    bool is_time_on_tooltip();
    void set_time_on_tooltip(bool);
    bool is_date_on_tooltip();
    void set_date_on_tooltip(bool);
    bool is_unixtime_on_tooltip();
    void set_unixtime_on_tooltip(bool);
    bool is_any_on_tooltip();

signals:
    void set_color(int);
    void update_hours_mode();

private slots:
    void color_0();
    void color_1();
    void hours_mode();
};

#endif
