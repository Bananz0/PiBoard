#ifndef ARTEMIS_H
#define ARTEMIS_H
#include <QImage>
#include <QDebug>
#include <QImage>
#include <QPainter>

class Artemis
{
public:
    QImage *backG = new QImage(":/assets/background.png");
    QPointF startPoint, endPoint, movingPoints;

    Artemis();    
    void setStartPoint(QPointF start);
    void setEndPoint(QPointF end);
    void setMovingPoints(QPointF move);

    QPointF getStartPoint();
    QPointF getEndPoint();
    QPointF getMovingPoints();

    void drawPoint(QPainter& painter, QPen& pen);
    void drawLine(QPainter& painter, QPen& pen);
    void drawCircle(QPainter& painter, QPen& pen);
    void drawRectangle(QPainter& painter, QPen& pen);
    void erasePoint(QPainter& painter, QPen& pen);
    void clearCanvas(QImage* image);
    QPointF onlyOnCanvas(QPointF canvasPoint);

 private:
    

};

#endif // ARTEMIS_H
