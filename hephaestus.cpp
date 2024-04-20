//Receiver
#include "hephaestus.h"
#include "ui_hephaestus.h"
#include <QDebug>

Hephaestus::Hephaestus(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hephaestus)
{
    ui->setupUi(this);
}

Hephaestus::~Hephaestus()
{
    free(draw);
    delete ui;
}

void Hephaestus::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    //TODO
    //Syncronize window sizes
    // Get the server window size from Minerva
    // QSize size = draw->minerva->setClentWindowSize();
    // qDebug() << "Height: " <<size.height() << "Width" << size.width();
    // resize(size);
}
