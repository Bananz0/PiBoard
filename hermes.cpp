//Sender
#include "hermes.h"
#include "ui_hermes.h"
#include <QPainter>


Hermes::Hermes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hermes)
{
    ui->setupUi(this);
    setMouseTracking(true);
}

Hermes::~Hermes()
{
    free(draw);
    delete ui;
}

//From QT Docs
//https://doc.qt.io/qt-6/eventsandfilters.html

void Hermes::mouseReleaseEvent(QMouseEvent *event){
    qDebug() << "Mouse: " << event->position();
    draw->setEndPoint(event->position());
    update();
}

void Hermes::mousePressEvent(QMouseEvent *event){
    draw->setStartPoint(event->position());
    qDebug() << "Mouse: " << event->position();
    update();
}

void Hermes::mouseMoveEvent(QMouseEvent *event)  {
    draw->setMovingPoints(event->position());
    qDebug() << "Mouse: " << event->position();
    update();
}

void Hermes::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //PEN
    QPen pen;
    painter.setPen(pen);
    painter.setRenderHint(QPainter::TextAntialiasing);
    pen.setWidth(60);

    painter.drawLine(draw->getStartPoint(), draw->getEndPoint());

}

//https://stackoverflow.com/questions/12828825/how-to-assign-callback-when-the-user-resizes-a-qmainwindow

void Hermes::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    QSize size = this->size();


    //TODO
    //Syncronize window sizes
    // minerva-> getServerWindowSize(size);
    // qDebug() << "Height: " <<size.height() << "Width" << size.width();


}
