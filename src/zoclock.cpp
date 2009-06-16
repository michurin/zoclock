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

#include <QApplication>
#include <QDesktopWidget>
#include "zocwidget.h"

int
main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QDesktopWidget * dsk = app.desktop();
    QRect rect(dsk->screenGeometry());
    BinClockWidget zoc(rect.left(), rect.right(), rect.top(), rect.bottom());
    QObject::connect(&zoc, SIGNAL(menu_quit()), &app, SLOT(quit()));
    zoc.show();
    return app.exec();
}
