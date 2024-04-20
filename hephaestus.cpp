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
    delete ui;
}
