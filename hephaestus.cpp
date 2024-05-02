//Receiver
#include "hephaestus.h"
#include "ui_hephaestus.h"
#include <QDebug>
#include <QImage>
#include <QTimer>

Hephaestus::Hephaestus(Minerva* minerva,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hephaestus)
    , minervaIn(minerva)
{
    draw = new Artemis;
    ui->setupUi(this);
    image = new QImage(800, 600, QImage::Format_RGB32);
    image->fill(Qt::white);
    //Update the image every 10ms
    int timerId = startTimer(1);
}

Hephaestus::~Hephaestus()
{
    delete minervaIn;
    delete draw;
    delete image;
    delete draw;
    delete ui;
}

void Hephaestus::timerEvent(QTimerEvent* event){

    	update();
}

void Hephaestus::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    //Draw on the image
    painter.drawImage(0, 0, *image);
    // painter.setRenderHint(QPainter::Antialiasing);
    QPainter imagePainter(image);
    //imagePainter.setRenderHint(QPainter::Antialiasing);
    drawOnCanvas(imagePainter, minervaIn->receiveDataPacket->pen, minervaIn->receiveDataPacket->drawMode);
    if (minervaIn->receiveDataPacket->clearCanvasFlag) {
        draw->clearCanvas(image);
    }

    minervaIn->receive();
    minervaIn->decodeData();  
   // qDebug() << "Drawing on Hephaestus";
}


void Hephaestus::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    update();
    //TODO
    //Syncronize window sizes
    // Get the server window size from Minerva
     //QSize size = drawDataPacket2->windowSize;
     //qDebug() << "Height: " <<size.height() << "Width" << size.width();
     //resize(size);
}

void Hephaestus::drawOnCanvas(QPainter& painter, QPen& pen, int drawMode) {
    draw->startPoint = minervaIn->receiveDataPacket->startPoint;
    draw->endPoint = minervaIn->receiveDataPacket->endPoint;
    draw->movingPoints = minervaIn->receiveDataPacket->movingPoint;
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
