#ifndef HEPHAESTUS_H
#define HEPHAESTUS_H

#include <QMainWindow>
#include "artemis.h"
#include "minerva.h"

namespace Ui {
class Hephaestus;
}

class Hephaestus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hephaestus(Minerva* minerva,QWidget *parent = nullptr);
    ~Hephaestus();
    
private:
    Minerva* minervaIn;
    Ui::Hephaestus *ui;
    QImage* image;
    void timerEvent(QTimerEvent* event) override;
    Artemis* draw = new Artemis;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    Minerva::drawData* drawDataPacket;
    void drawOnCanvas(QPainter& painter, QPen& pen, int drawMode);
};

#endif // HEPHAESTUS_H
