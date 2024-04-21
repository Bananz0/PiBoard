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
    delete ui;
}

void Hephaestus::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QPen pen;

    //Pen Properties
    pen.setColor(Qt::white);
    pen.setWidth(20);
    

    //Draw on the image
    painter.drawImage(0, 0, *image);
    painter.setRenderHint(QPainter::Antialiasing);

    QPainter imagePainter(image);
    imagePainter.setRenderHint(QPainter::Antialiasing);

}


void Hephaestus::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    //TODO
    //Syncronize window sizes
    // Get the server window size from Minerva
    // QSize size = draw->minerva->setClentWindowSize();
    //qDebug() << "Height: " <<size.height() << "Width" << size.width();
    // resize(size);
}
