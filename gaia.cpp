//Core
#include "gaia.h"
#include "./ui_gaia.h"


Gaia::Gaia(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gaia)
{
    Minerva *minerva = new Minerva;

    ui->setupUi(this);
    
}

Gaia::~Gaia()
{
    delete ui;
}

//TODO
//Display Minerva's status
//https://stackoverflow.com/questions/24470519/how-to-auto-scroll-qt-text-field-widget


void Gaia::on_senderButton_clicked()
{
    startServer("Center");
}

void Gaia::on_receiverButton_clicked()
{
    startClient("Center");
}

void Gaia::on_allButton_clicked()
{
    startServer("Right");
    startClient("Left");
}

void Gaia::startServer(const QString& position){
    QIcon server(":/assets/server.png");
    Hermes *senderWindow = new Hermes;
    senderWindow->show();
    senderWindow->setWindowTitle("Server");
    senderWindow->setWindowIcon(server);
    movePosition(senderWindow,position);

    minerva->serverMode();

};

void Gaia::startClient(const QString& position){
    QIcon client(":/assets/client.png");
    Hephaestus *receiverwindow = new Hephaestus;
    receiverwindow->show();
    receiverwindow->setWindowIcon(client);
    receiverwindow->setWindowTitle("Reciever");
    movePosition(receiverwindow,position);

    minerva->clientMode();
};

void Gaia::movePosition(QMainWindow* window,const QString& position){
    QRect screenRect = QGuiApplication::primaryScreen()->availableGeometry();
    int x, y;
    if (position == "Left") {
        x = 0;
        y = (screenRect.height() - window->height()) / 2;
    } else if (position == "Right") {
        x = screenRect.right() - window->width();
        y = (screenRect.height() - window->height()) / 2;
    } else if (position == "Center"){
        x = (screenRect.width() - window->width()) / 2;
        y = (screenRect.height() - window->height()) / 2;
    }
    window->move(x, y);
};

void Gaia::selectDataPinCount(int pincount){
    //TODO
    // Add loginc for selecting the number of pins for data transfer sacrificing speed for idk anything else
}

