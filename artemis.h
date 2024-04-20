#ifndef ARTEMIS_H
#define ARTEMIS_H
#include <QImage>
#include <QDebug>


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

    void eraseCanvas();

    void drawLine();
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
