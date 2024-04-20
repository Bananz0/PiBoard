//Receiver
#include "hephaestus.h"
#include "ui_hephaestus.h"

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

void Hephaestus::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "Mouse x " << event->position() << " Mouse y " << event->position();
}
