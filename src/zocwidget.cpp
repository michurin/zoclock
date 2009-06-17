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

#include <QFrame>
#include <QGridLayout>
#include <QMouseEvent>
#include <QTime>
#include <QMessageBox>
#include <QColorDialog>
#include "zocwidget.h"
#include "zoclock.h"

void
BinClockWidget::updateLine(int line)
{
    int c;
    int val = displayData[line];
    for (c = 5; c >= 0; c--) {
        displayDots[line][c]->setPalette(palettes[val & 1]);
        val >>= 1;
    }
}

void
BinClockWidget::updateView()
{
    updateLine(0);
    updateLine(1);
}

void
BinClockWidget::updateState()
{
    QTime t = QTime::currentTime();
    int data[2];
    data[1] = t.minute();
    data[0] = (t.hour()-1) % 12 + 1;
    int i;
    for (i = 1; i >= 0; i--) {
        if (data[i] != displayData[i]) {
            displayData[i] = data[i];
            updateLine(i);
        } else {
            break;
        }
    }
}

void
BinClockWidget::setColor(int i, QColor & c)
{
    palettes[i].setColor(QPalette::Background, c);
    palettes[i].setColor(QPalette::Light, c.lighter());
    palettes[i].setColor(QPalette::QPalette::Dark, c.darker());
}

void
BinClockWidget::setOnTop(bool f)
{
    Qt::WindowFlags wf = windowFlags();
    bool isv = isVisible();
    if (f) {
        wf |= Qt::WindowStaysOnTopHint;
    } else {
        wf &= ~Qt::WindowStaysOnTopHint;
    }
    if (wf != windowFlags()) {
        setWindowFlags(wf);
        if (isv) {
            show();
            raise();
        }
    }
}

BinClockWidget::BinClockWidget(int x0, int x1, int y0, int y1)
    : Inherited(0, Qt::SplashScreen | Qt::WindowStaysOnTopHint),
      bound_x0(x0),
      bound_x1(x1 - ZOC_WINDOW_WIDTH + 1),
      bound_y0(y0),
      bound_y1(y1 - ZOC_WINDOW_HEIGHT + 1),
      popup_menu(this),
      settings(bound_x1/2, bound_y1/2)
{
    displayData[1] = -1;
    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    int r, c;
    for (r=0; r<2; r++) {
        for (c=0; c<6; c++) {
            BinClockDot *b = new BinClockDot(this);
            displayDots[r][c] = b;
            layout->addWidget(b, r, c);
        }
    }
    setLayout(layout);
    setGeometry(0, 0, ZOC_WINDOW_WIDTH, ZOC_WINDOW_HEIGHT);
    QColor c0, c1;
    int wx, wy;
    bool lock;
    bool ontop;
    settings.read(wx, wy, c0, c1, lock, ontop);
    popup_menu.set_window_lock(lock);
    popup_menu.set_window_ontop(ontop);
    setOnTop(ontop);
    setColor(0, c0);
    setColor(1, c1);
    move(wx, wy);
}

void
BinClockWidget::timerEvent(QTimerEvent *)
{
    updateState();
}

void
BinClockWidget::mousePressEvent(QMouseEvent* e)
{
    click_pos = e->pos();
    raise();
    if(e->button() == Qt::RightButton) {
        popup_menu.popup(QCursor::pos());
    }
}

void
BinClockWidget::mouseMoveEvent(QMouseEvent* e)
{
    if(!popup_menu.is_window_locked()) {
        QPoint new_place = e->globalPos() - click_pos;
        move(new_place.x(), new_place.y());
    }
}           

void
BinClockWidget::move(int x, int y)
{
    Inherited::move(x < bound_x0 ? bound_x0 : x > bound_x1 ? bound_x1 : x,
                    y < bound_y0 ? bound_y0 : y > bound_y1 ? bound_y1 : y);
}

void
BinClockWidget::show()
{
    timerId = startTimer(1000);
    updateState();
    Inherited::show();
}

void
BinClockWidget::hide()
{
    killTimer(timerId);
    Inherited::hide();
}

/*
 * SLOTS
 */

void
BinClockWidget::menu_save_setings()
{
    settings.write(pos().x(),
                   pos().y(),
                   palettes[0].color(QPalette::Background),
                   palettes[1].color(QPalette::Background),
                   popup_menu.is_window_locked(),
                   popup_menu.is_window_ontop());
    QMessageBox::information(this,
        tr("Settings has been saved"),
        tr("Current window position, colors, lock status"
           " and always on top status"
           " has been saved as default."
           " They would be restored automaticaly"
           " the next time you start ZOClock."));
}

void
BinClockWidget::menu_ontop()
{
    setOnTop(popup_menu.is_window_ontop());
}

void
BinClockWidget::menu_oem_colors()
{
    QColor c0, c1;
    settings.get_oem_colors(c0, c1);
    setColor(0, c0);
    setColor(1, c1);
    updateView();
}

void
BinClockWidget::menu_about()
{
    QMessageBox::about(
        this,
        tr("About ZOClock"),
        tr("<h3>ZOClock " STR(ZOCVERSION) "</h3>"
           "<p>Copyright (c) 2009 Alexey Michurin</p>"
           "<p>Released under the terms of the"
           " <a href=\"http://www.gnu.org/licenses/\">GNU GPL v3</a></p>"
           "<p>The ZOClock (Zero-One Clock) program emulate"
           " two-line LED display to show the time in"
           " binary form."
           " The upper line of LEDs displays hours (12 hour clock)."
           " The lower line of LEDs displays minutes.</p>"
           "<p>Project home page: "
           "<a href=\"http://zoclock.googlecode.com/\">"
           "http://zoclock.googlecode.com/</a></p>"));
}
    
void
BinClockWidget::menu_about_qt()
{
    QMessageBox::aboutQt(this);
}

void
BinClockWidget::menu_color(int i)
{
    QColor c = QColorDialog::getColor(
                             palettes[i].color(QPalette::Background),
                             this);
    if (c.isValid()) {
        setColor(i, c);
        updateView();
    }
}
