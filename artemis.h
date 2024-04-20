#ifndef ARTEMIS_H
#define ARTEMIS_H
#include <QImage>
#include <QDebug>
#include <QMouseEvent>

class Artemis
{
public:
    Artemis();
    void eraseCanvas();
    void drawLine();
    class drawShapes{
        void Circle();
        void Square();
        void Triangle();
        void Squircle();
    };



};

#endif // ARTEMIS_H
