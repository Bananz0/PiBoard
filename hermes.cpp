//Sender
#include "hermes.h"
#include "ui_hermes.h"

Hermes::Hermes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hermes)
{
    ui->setupUi(this);
}

Hermes::~Hermes()
{
    delete ui;
}
