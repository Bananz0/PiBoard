//Receiver
#include "hephaestus.h"
#include "ui_hephaestus.h"
#include <QDebug>
#include <QImage>
#include <QTimer>



Hephaestus::Hephaestus(Minerva::drawData* drawDataPacketIn,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hephaestus)
    , drawDataPacket(drawDataPacketIn)
{
    ui->setupUi(this);
    image = new QImage(800, 600, QImage::Format_RGB32);
    image->fill(Qt::white);

    //https://surfer.nmr.mgh.harvard.edu/ftp/dist/freesurfer/tutorial_versions/freesurfer/lib/qt/qt_doc/html/qtimer.html#:~:text=Example%20for%20a,called%20every%20second.
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&QWidget::update));
    timer->start(10);
    
}

Hephaestus::~Hephaestus()
{
    delete draw;
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

    ////imagePainter.drawLine(drawDataPacket->startPoint, drawDataPacket->endPoint);
    //QPointF point, point2;
    //point.setX(322);
    //point.setY(422);
    //point2.setX(100);
    //point2.setY(100);
    //imagePainter.drawLine(point, point2);
    //imagePainter.drawPoint(drawDataPacket->startPoint);
    //imagePainter.drawLine(drawDataPacket->startPoint, drawDataPacket->endPoint);
    //imagePainter.drawPoint(drawDataPacket->movingPoint);

   // qDebug() << "Drawing on Hephaestus";
}


void Hephaestus::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    update();
    //TODO
    //Syncronize window sizes
    // Get the server window size from Minerva
     //QSize size = drawDataPacket->windowSize;
     //qDebug() << "Height: " <<size.height() << "Width" << size.width();
     //resize(size);
}

void Hephaestus::drawOnCanvas(QPainter& painter, QPen& pen, int drawMode) {
    draw->startPoint = drawDataPacket->startPoint;
    draw->endPoint = drawDataPacket->endPoint;
    draw->movingPoints = drawDataPacket->movingPoint;
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