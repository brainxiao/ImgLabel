#include "mylabel.h"
#include <QPainter>
#include <QDebug>
MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    pix = QPixmap(200,200);
    isDrawing = false;
}
void MyLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    int x,y,w,h;
    x = lastPoint.x();
    y = lastPoint.y();
    w = endPoint.x() - x;
    h = endPoint.y() - y;
    QPainter painter(this);

    if(isDrawing)
    {
        tempPix = pix;
        QPainter pp(&tempPix);
        pp.setPen(QPen(Qt::red,1));
        pp.drawRect(x,y,w,h);
        painter.drawPixmap(0,0,tempPix);
    }
}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    if(event -> buttons()&Qt::LeftButton)
    {
        //qDebug() << "mousePress";
        pix = *(this->pixmap());
        lastPoint = event->pos();
        isDrawing = true;
    }
}
void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(event -> buttons() & Qt::LeftButton)
    {
        endPoint = event -> pos();
        update();
    }
}
void MyLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event -> button() == Qt::LeftButton)
    {
        //qDebug() << "mouseRease";
        emit sentRect(lastPoint,event->pos());
        isDrawing = false;
    }
}

