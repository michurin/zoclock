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

public:
    PopupMenu(QWidget * parent = 0);
    bool is_window_locked();
    void set_window_lock(bool);
    bool is_window_ontop();
    void set_window_ontop(bool);

signals:
    void set_color(int);

public slots:
    void color_0();
    void color_1();
};

#endif
