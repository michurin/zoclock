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
#include <QDateTime>
#include <QMessageBox>
#include <QColorDialog>
#include <QFontDialog>
#include "zocwidget.h"
#include "zoclock.h"

int
BinClockWidget::wallClockHour()
{
    if (popup_menu.is_hours_12_mode()) {
        return (wall_clock_hour + 11) % 12 + 1;
    }
    return wall_clock_hour;
}

void
BinClockWidget::updateLine(int line, int val)
{
    for (int c = 5; c >= 0; c--) {
        displayDots[line][c].setPalette(palettes[val & 1]);
        val >>= 1;
    }
}

void
BinClockWidget::updateView()
{
    int h = wallClockHour();
    if (popup_menu.is_hours_ampm_mode() && wall_clock_hour > 12) {
        h |= 32;
    }
    updateLine(0, h);
    updateLine(1, wall_clock_minute);
}

void
BinClockWidget::appendToToolTip(int n, QString & tip_text)
{
    QString s = QString::number(n, popup_menu.get_base());
    tip_text.append(QString().fill('0', 2 - s.size()));
    tip_text.append(s);
}

const QString BinClockWidget::TOOLTIP_TIME_SEPERATOR(":");
const QString BinClockWidget::TOOLTIP_TIME_AM_SIG(" AM");
const QString BinClockWidget::TOOLTIP_TIME_PM_SIG(" PM");
const QString BinClockWidget::TOOLTIP_TIME_LSEPERATOR(" / ");

void
BinClockWidget::updateToolTip(bool force_show)
{
    if (! popup_menu.is_any_on_tooltip()) {
        return;
    }
    QString tip_text("");
    if (popup_menu.is_time_on_tooltip()) {
        appendToToolTip(wallClockHour(), tip_text);
        tip_text.append(TOOLTIP_TIME_SEPERATOR);
        appendToToolTip(wall_clock_minute, tip_text);
        if (popup_menu.is_hours_ampm_mode()) {
            if (wall_clock_hour > 12) {
                tip_text.append(TOOLTIP_TIME_PM_SIG);
            } else {
                tip_text.append(TOOLTIP_TIME_AM_SIG);
            }
        }
        if (popup_menu.is_unixtime_on_tooltip()) {
            tip_text.append(TOOLTIP_TIME_LSEPERATOR);
        }
    }
    if (popup_menu.is_unixtime_on_tooltip()) {
        appendToToolTip(wall_clock_time, tip_text);
    }
    popup_tip.setText(tip_text);

    QSize s = popup_tip.sizeHint();
    s.setWidth(s.width() + ZOC_TOOLTIP_EXTRAWIDTH);
    popup_tip.resize(s);
    QPoint tl = geometry().topLeft() - QPoint(0, s.height() + ZOC_TOOLTIP_GAP);
    if (tl.y() < screen_geometry.top()) {
        tl = geometry().bottomLeft() + QPoint(0, ZOC_TOOLTIP_GAP + 1);
    }
    if (tl.x() + popup_tip.width() > screen_geometry.right()) {
        tl.setX(screen_geometry.right() - popup_tip.width());
    }
    popup_tip.move(tl);
    
    if (force_show) {
        popup_tip.show();
    }
}

bool
BinClockWidget::updateWallClock()
{
    QDateTime d = QDateTime::currentDateTime();
    QTime t = d.time();
    wall_clock_time = d.toTime_t();
    int m = t.minute();
    if (m == wall_clock_minute) {
        return false;
    }
    wall_clock_hour = t.hour();
    wall_clock_minute = m;
    return true;
}

void
BinClockWidget::updateState(bool force)
{
    if (updateWallClock() || force) {
        updateView();
    }
    if (popup_tip.isVisible()) {
        updateToolTip(false);
    }
}

void
BinClockWidget::setColor(int i, QColor const & c)
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

void
BinClockWidget::setToolTipColor(QPalette::ColorRole cr)
{
    QPalette p = popup_tip.palette();
    QColor c = QColorDialog::getColor(p.color(cr), this);
    if (c.isValid()) {
        p.setColor(cr, c);
        popup_tip.setPalette(p);
    }
}

void
BinClockWidget::setToolTipColors(QColor const & fg, QColor const & bg)
{
    QPalette p;
    p.setColor(QPalette::Foreground, fg);
    p.setColor(QPalette::Background, bg);
    popup_tip.setPalette(p);
}

BinClockWidget::BinClockWidget(QRect const & sg)
    : Inherited(0, Qt::Tool |
                   Qt::FramelessWindowHint |
                   Qt::X11BypassWindowManagerHint |
                   Qt::WindowStaysOnTopHint),
      screen_geometry(sg),
      settings(QPoint((sg.right()-sg.left())/2,
                      (sg.bottom()-sg.top())/2)),
      popup_tip(0, Qt::ToolTip),
      popup_menu(this)
{
    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    int r, c;
    for (r = 0; r != 2; ++r) {
        for (c = 0; c != 6; ++c) {
            QFrame *b = &(displayDots[r][c]);
            b->setParent(this);
            b->setFrameStyle(QFrame::Panel | QFrame::Raised);
            b->setLineWidth(ZOC_WINDOW_BORDER);
            b->setAutoFillBackground(true);             
            layout->addWidget(b, r, c);
        }
    }
    setLayout(layout);
    setGeometry(0, 0, ZOC_WINDOW_WIDTH, ZOC_WINDOW_HEIGHT);
    popup_tip.setMargin(0);
    popup_tip.setAlignment(Qt::AlignHCenter);
    popup_tip.setWordWrap(false);
    QColor c0, c1, tt_fg, tt_bg;
    QFont tt_font;
    QPoint window_xy;
    bool lock, ontop;
    int h_mode, n_base;
    bool tt_tm, tt_utm;
    settings.read(window_xy, c0, c1, lock, ontop, h_mode, n_base,
                  tt_tm, tt_utm,
                  tt_font, tt_fg, tt_bg);
    popup_menu.set_window_lock(lock);
    popup_menu.set_window_ontop(ontop);
    popup_menu.set_hours_mode(h_mode);
    popup_menu.set_base(n_base);
    popup_menu.set_time_on_tooltip(tt_tm);
    popup_menu.set_unixtime_on_tooltip(tt_utm);
    setOnTop(ontop);
    setColor(0, c0);
    setColor(1, c1);
    move(window_xy);
    setToolTipColors(tt_fg, tt_bg);
    popup_tip.setFont(tt_font);
}

void
BinClockWidget::timerEvent(QTimerEvent *)
{
    updateState(false);
}

void
BinClockWidget::mousePressEvent(QMouseEvent* e)
{
    click_pos = e->pos();
    raise();
    if(e->button() == Qt::RightButton) {
        popup_menu.popup(e->globalPos());
    }
    popup_tip.hide();
}

void
BinClockWidget::mouseReleaseEvent(QMouseEvent *)
{
    updateToolTip(true);
}

void
BinClockWidget::mouseMoveEvent(QMouseEvent* e)
{
    if(!popup_menu.is_window_locked()) {
        QPoint new_place = e->globalPos() - click_pos;
        move(new_place);
    }
}           

void
BinClockWidget::enterEvent(QEvent *)
{
    updateToolTip(true);
}

void
BinClockWidget::leaveEvent(QEvent *)
{
    popup_tip.hide();
}

void
BinClockWidget::move(QPoint const & p)
{
    int x0, x1, y0, y1;
    int x = p.x();
    int y = p.y();
    screen_geometry.getCoords(&x0, &y0, &x1, &y1);
    x1 -= ZOC_WINDOW_WIDTH-1;
    y1 -= ZOC_WINDOW_HEIGHT-1;
    Inherited::move(x<x0 ? x0 : x>x1 ? x1 : x, y<y0 ? y0 : y>y1 ? y1 : y);
}

void
BinClockWidget::show()
{
    timerId = startTimer(1000);
    updateState(true);
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
    settings.write(geometry().topLeft(),
                   palettes[0].color(QPalette::Background),
                   palettes[1].color(QPalette::Background),
                   popup_menu.is_window_locked(),
                   popup_menu.is_window_ontop(),
                   popup_menu.get_hours_mode(),
                   popup_menu.get_base(),
                   popup_menu.is_time_on_tooltip(),
                   popup_menu.is_unixtime_on_tooltip(),
                   popup_tip.font(),
                   popup_tip.palette().color(QPalette::Foreground),
                   popup_tip.palette().color(QPalette::Background));
    QMessageBox::information(this,
        tr("Settings has been saved"),
        tr("Current window position, colors,"
           " window status and other settings"
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
    QColor c0, c1, tt_bg, tt_fg;
    settings.get_oem_colors(c0, c1, tt_bg, tt_fg);
    setColor(0, c0);
    setColor(1, c1);
    updateView();
    setToolTipColors(tt_bg, tt_fg);
}

#ifndef ZOCVERSION
#define ZOCVERSION [unknown version]
#endif

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
           "<p>The ZOClock (Zero-One Clock) is a tiny desktop widget."
           " The program emulate"
           " two-line LED display to show the time in"
           " binary form."
           " It highly customizable to better fit with"
           " your desktop environment."
           "<p>Project home page: "
           "<a href=\"http://zoclock.googlecode.com/\">"
           "http://zoclock.googlecode.com/</a></p>"
           "<p>Author: "
           "<a href=\"mailto:a.michurin@gmail.com\">"
           "Alexey Michurin &lt;a.michurin@gmail.com&gt;</a></p>"
           ));
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

void
BinClockWidget::menu_hours_mode()
{
    updateView();
}

void
BinClockWidget::menu_tooltip_font()
{
    popup_tip.setFont(QFontDialog::getFont(0, popup_tip.font(), this));
}

void
BinClockWidget::menu_tooltip_bg()
{
    setToolTipColor(QPalette::Background);
}

void
BinClockWidget::menu_tooltip_fg()
{
    setToolTipColor(QPalette::Foreground);
}
