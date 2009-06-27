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

#include "popupmenu.h"

PopupMenu::PopupMenu(QWidget * parent)
    : Inherited(parent)
{
    QAction * a;
    QMenu * m;
    QActionGroup * g;
    addSeparator();
    a = new QAction(tr("Lock window position"), this);
    a->setCheckable(true);
    addAction(a);
    lock_pos = a;
    a = new QAction(tr("Keep window always on top"), this);
    a->setCheckable(true);
    addAction(a);
    window_ontop = a;
    connect(a, SIGNAL(triggered()), parent, SLOT(menu_ontop()));
    addSeparator();

    m = addMenu("Hours mode");
    g = new QActionGroup(this);
    a = new QAction(tr("12-hours mode (from 1 to 12)"), this);
    a->setCheckable(true);
    g->addAction(a);
    m->addAction(a);
    hours_mode_actions[0] = a;
    connect(a, SIGNAL(triggered()), this, SLOT(hours_mode()));
    a = new QAction(tr("12-hours mode and PM/AM indication"), this);
    a->setCheckable(true);
    g->addAction(a);
    m->addAction(a);
    hours_mode_actions[1] = a;
    connect(a, SIGNAL(triggered()), this, SLOT(hours_mode()));
    a = new QAction(tr("24-hours mode (from 0 to 23)"), this);
    a->setCheckable(true);
    g->addAction(a);
    m->addAction(a);
    hours_mode_actions[2] = a;
    connect(a, SIGNAL(triggered()), this, SLOT(hours_mode()));

    connect(this, SIGNAL(update_hours_mode()), parent, SLOT(menu_hours_mode()));

    m = addMenu("ToolTip");
    a = new QAction(tr("Time"), this);
    a->setCheckable(true);
    m->addAction(a);
    tooltip_time_action = a;
    a = new QAction(tr("Unix time"), this);
    a->setCheckable(true);
    m->addAction(a);
    tooltip_unixtime_action = a;
    m->addSeparator();
    g = new QActionGroup(this);
    a = new QAction(tr("Dec"), this);
    a->setCheckable(true);
    g->addAction(a);
    m->addAction(a);
    tooltip_dec_action = a;
    a = new QAction(tr("Hex"), this);
    a->setCheckable(true);
    g->addAction(a);
    m->addAction(a);
    tooltip_hex_action = a;
    m->addSeparator();
    a = new QAction(tr("Set font"), this);
    m->addAction(a);
    connect(a, SIGNAL(triggered()), parent, SLOT(menu_tooltip_font()));
    a = new QAction(tr("Set text color"), this);
    m->addAction(a);
    connect(a, SIGNAL(triggered()), parent, SLOT(menu_tooltip_fg()));
    a = new QAction(tr("Set background color"), this);
    m->addAction(a);
    connect(a, SIGNAL(triggered()), parent, SLOT(menu_tooltip_bg()));

    addSeparator();
    a = new QAction(tr("Color of \"0\" indicator"), this);
    addAction(a);
    connect(a, SIGNAL(triggered()), this, SLOT(color_0()));
    a = new QAction(tr("Color of \"1\" indicator"), this);
    addAction(a);
    connect(a, SIGNAL(triggered()), this, SLOT(color_1()));
    a = new QAction(tr("Restore original colors"), this);
    addAction(a);
    connect(a, SIGNAL(triggered()), parent, SLOT(menu_oem_colors()));
    addSeparator();
    a = new QAction(tr("Save current settings as default"), this);
    addAction(a);
    connect(a, SIGNAL(triggered()), parent, SLOT(menu_save_setings()));
    addSeparator();
    a = new QAction(tr("About"), this);
    connect(a, SIGNAL(triggered()), parent, SLOT(menu_about()));
    addAction(a);
    a = new QAction(tr("About Qt"), this);
    connect(a, SIGNAL(triggered()), parent, SLOT(menu_about_qt()));
    addAction(a);
    addSeparator();
    a = new QAction(tr("Quit"), this);
    addAction(a);
    connect(a, SIGNAL(triggered()), parent, SIGNAL(menu_quit()));
    connect(this, SIGNAL(set_color(int)), parent, SLOT(menu_color(int)));
}

bool
PopupMenu::is_window_locked()
{
    return lock_pos->isChecked();
}

void
PopupMenu::set_window_lock(bool s)
{
    lock_pos->setChecked(s);
}

bool
PopupMenu::is_window_ontop()
{
    return window_ontop->isChecked();
}

void
PopupMenu::set_window_ontop(bool s)
{
    window_ontop->setChecked(s);
}

int
PopupMenu::get_hours_mode()
{
    return hours_mode_idx;
}

bool
PopupMenu::is_hours_ampm_mode()
{
    return hours_mode_idx == 1;
}

bool
PopupMenu::is_hours_12_mode()
{
    return hours_mode_idx != 2;
}

void
PopupMenu::set_hours_mode(int m)
{
    hours_mode_idx = m; // is it good idea to check m?
    hours_mode_actions[m]->setChecked(true);
}

int
PopupMenu::get_base()
{
    return tooltip_dec_action->isChecked() ? 10 : 16;
}

void
PopupMenu::set_base(int b)
{
    tooltip_dec_action->setChecked(b == 10);
    tooltip_hex_action->setChecked(b != 10);
}

bool
PopupMenu::is_time_on_tooltip()
{
    return tooltip_time_action->isChecked();
}

void
PopupMenu::set_time_on_tooltip(bool v)
{
    tooltip_time_action->setChecked(v);
}

bool
PopupMenu::is_unixtime_on_tooltip()
{
    return tooltip_unixtime_action->isChecked();
}

void
PopupMenu::set_unixtime_on_tooltip(bool v)
{
    tooltip_unixtime_action->setChecked(v);
}

bool
PopupMenu::is_any_on_tooltip()
{
    return tooltip_unixtime_action->isChecked() ||
           tooltip_time_action->isChecked();
}

/*
 * SLOTS
 */

void
PopupMenu::color_0()
{
    emit set_color(0);
}

void
PopupMenu::color_1()
{
    emit set_color(1);
}

void
PopupMenu::hours_mode()
{
    for (int i = 0; i != 3; ++i) {
        if (hours_mode_actions[i]->isChecked()) {
            hours_mode_idx = i;
            break;
        }
    }
    emit update_hours_mode();
}
