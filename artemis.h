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

    Artemis();    
    void setStartPoint(QPointF start);
    void setEndPoint(QPointF end);
    void setMovingPoints(QPointF move);

    QPointF getStartPoint();
    QPointF getEndPoint();
    QPointF getMovingPoints();

    void drawPoint(QPainter& painter, QPen& pen);
    void drawLine(QPainter& painter, QPen& pen);

    void clearCanvas(QImage* image);


    class drawShapes{
        void Circle();
        void Square();
        void Triangle();
        void Squircle();
    };



private:
    QPointF startPoint, endPoint, movingPoints;

};

#endif // ARTEMIS_H
