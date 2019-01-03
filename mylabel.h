#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void sentRect(QPoint ,QPoint);
public slots:
private:
    QPixmap pix;
    QPoint lastPoint;
    QPoint endPoint;

    QPixmap tempPix;
    bool isDrawing;
};

#endif // MYLABEL_H
