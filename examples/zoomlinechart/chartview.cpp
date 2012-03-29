/****************************************************************************
 **
 ** Copyright (C) 2012 Digia Plc
 ** All rights reserved.
 ** For any questions to Digia, please use contact form at http://qt.digia.com
 **
 ** This file is part of the Qt Commercial Charts Add-on.
 **
 ** $QT_BEGIN_LICENSE:BSD$
 ** You may use this file under the terms of the BSD license as follows:
 **
 ** "Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are
 ** met:
 **   * Redistributions of source code must retain the above copyright
 **     notice, this list of conditions and the following disclaimer.
 **   * Redistributions in binary form must reproduce the above copyright
 **     notice, this list of conditions and the following disclaimer in
 **     the documentation and/or other materials provided with the
 **     distribution.
 **   * Neither the name of Digia nor the names of its contributors
 **     may be used to endorse or promote products derived from this
 **     software without specific prior written permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 ** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 ** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 ** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 ** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 ** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 ** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 ** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 ** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 ** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 ** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include "chartview.h"
#include <QMouseEvent>

ChartView::ChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent), m_rubberBand(QRubberBand::Rectangle, this), m_chart(chart)
{
}

void ChartView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    m_origin = event->pos();
    m_rubberBand.setGeometry(QRect(m_origin, QSize()));
    m_rubberBand.show();

    event->accept();
}

void ChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_rubberBand.isVisible())
        m_rubberBand.setGeometry(QRect(m_origin, event->pos()).normalized());
}

void ChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_rubberBand.isVisible()) {
        m_rubberBand.hide();

        QRect rect = m_rubberBand.geometry();
        m_chart->zoomIn(rect);
        event->accept();
    }

    if (event->button() == Qt::RightButton) {
        m_chart->zoomOut();
    }
}

void ChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        m_chart->zoomIn();
        break;
    case Qt::Key_Minus:
        m_chart->zoomOut();
        break;
    case Qt::Key_Left:
        m_chart->scrollLeft();
        break;
    case Qt::Key_Right:
        m_chart->scrollRight();
        break;
    case Qt::Key_Up:
        m_chart->scrollUp();
        break;
    case Qt::Key_Down:
        m_chart->scrollDown();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
        break;
    }
}
