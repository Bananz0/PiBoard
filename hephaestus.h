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
    Minerva* minervaIn;
    explicit Hephaestus(Minerva* minerva,QWidget *parent = nullptr);
    ~Hephaestus();
    Artemis *draw = new Artemis;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

    Minerva::drawData* drawDataPacket;

    void drawOnCanvas(QPainter& painter, QPen& pen, int drawMode);

private:
    Ui::Hephaestus *ui;
    QImage* image;
};

#endif // HEPHAESTUS_H
