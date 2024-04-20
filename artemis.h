#ifndef ARTEMIS_H
#define ARTEMIS_H
#include <QImage>
#include <QDebug>
#include "minerva.h"

class Artemis
{
public:


    Artemis();
    void setStartPoint(QPointF start);
    void setEndPoint(QPointF end);
    void setMovingPoints(QPointF move);

    QPointF getStartPoint();
    QPointF getEndPoint();
    QPointF getMovingPoints();

    void drawLine();

    class drawShapes{
        void Circle();
        void Square();
        void Triangle();
        void Squircle();
    };

    void eraseCanvas();


private:
    QPointF startPoint, endPoint, movingPoints;

};

#endif // ARTEMIS_H
