//Core
#include "gaia.h"
#include "./ui_gaia.h"

Gaia::Gaia(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gaia)
{
    ui->setupUi(this);
}

Gaia::~Gaia()
{
    delete ui;
}

void Gaia::on_senderButton_clicked()
{
    QIcon server(":/assets/server.png");
    Hermes *senderwindow = new Hermes;
    senderwindow->show();
    senderwindow->setWindowTitle("Server");
    senderwindow->setWindowIcon(server);
}


void Gaia::on_receiverButton_clicked()
{
    QIcon client(":/assets/client.png");
    Hephaestus *receiverwindow = new Hephaestus;
    receiverwindow->show();
    receiverwindow->setWindowIcon(client);
    receiverwindow->setWindowTitle("Reciever");
}


void Gaia::on_allButton_clicked()
{
    QIcon server(":/assets/server.png");
    Hermes *senderwindow = new Hermes;
    senderwindow->show();
    senderwindow->setWindowTitle("Server");
    senderwindow->setWindowIcon(server);
    QIcon client(":/assets/client.png");
    Hephaestus *receiverwindow = new Hephaestus;
    receiverwindow->show();
    receiverwindow->setWindowIcon(client);
    receiverwindow->setWindowTitle("Reciever");
}



