//Sender
#include "hermes.h"
#include "ui_hermes.h"

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
    endPoint = event->position();
    update();
}

void Hermes::mousePressEvent(QMouseEvent *event){
    startPoint = event->position();
    qDebug() << "Mouse: " << event->position();
    update();
}

void Hermes::mouseMoveEvent(QMouseEvent *event)  {
    movingPoints = event->position();
    qDebug() << "Mouse: " << event->position();
    update();
}
