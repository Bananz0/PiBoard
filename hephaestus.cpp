//Receiver
#include "hephaestus.h"
#include "ui_hephaestus.h"
#include <QDebug>
#include <QImage>




Hephaestus::Hephaestus(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hephaestus)
{
    ui->setupUi(this);
    image = new QImage(800, 600, QImage::Format_RGB32);
    image->fill(Qt::black);
    update();
    
}

Hephaestus::~Hephaestus()
{
    delete draw;
    delete drawDataPacket;
    delete ui;
}

void Hephaestus::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
       

    //Draw on the image
    painter.drawImage(0, 0, *image);
    // painter.setRenderHint(QPainter::Antialiasing);

    QPainter imagePainter(image);
    //imagePainter.setRenderHint(QPainter::Antialiasing);

    drawOnCanvas(imagePainter, drawDataPacket->pen, drawDataPacket->drawMode);
}


void Hephaestus::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    //TODO
    //Syncronize window sizes
    // Get the server window size from Minerva
     QSize size = drawDataPacket->windowSize;
     qDebug() << "Height: " <<size.height() << "Width" << size.width();
     resize(size);
}

void Hephaestus::drawOnCanvas(QPainter& painter, QPen& pen, int drawMode) {
    switch (drawMode) {
    case 0:
        draw->drawLine(painter, pen);
        break;
    case 1:
        draw->drawPoint(painter, pen);
        break;
    case 2:
        draw->drawCircle(painter, pen);
        break;
    case 3:
        draw->drawRectangle(painter, pen);
        break;
    case 8:
        pen.setColor(Qt::white);
        draw->erasePoint(painter, pen);
        break;
    default:
        qDebug() << "Unexpected drawMode value:" << drawMode;
        qWarning() << "Unexpected drawMode value:" << drawMode;
        break;
    }
}