#ifndef HEPHAESTUS_H
#define HEPHAESTUS_H

#include <QMainWindow>
#include "artemis.h"



namespace Ui {
class Hephaestus;
}

class Hephaestus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hephaestus(QWidget *parent = nullptr);
    ~Hephaestus();
    Artemis *draw = new Artemis;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    class drawData {
    public:
        QPointF startPoint;
        QPointF endPoint;
        QPointF movingPoint;
        QPen pen;
        int drawMode = 1;
        QSize windowSize;

        drawData() {
        }
    };


    drawData* drawDataPacket = new drawData;

    void drawOnCanvas(QPainter& painter, QPen& pen, int drawMode);

private:
    Ui::Hephaestus *ui;
    QImage* image;
};

#endif // HEPHAESTUS_H
