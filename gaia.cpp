//Core
#include "gaia.h"
#include "./ui_gaia.h"

#include <QTextBrowser>
#include <QString>
#include <QTimer>

Gaia::Gaia(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Gaia)
{
      


    ui->setupUi(this);
    ui->minervaStatus->setText("Welcome to PiBoard");
    minerva->initializeGPIO();


    ui->minervaStatus->append(minerva->testConnection());

}

Gaia::~Gaia()
{
    delete ui;
}

//TODO
//Display Minerva's status
//https://stackoverflow.com/questions/24470519/how-to-auto-scroll-qt-text-field-widget\
//https://doc.qt.io/qt-5/qtextedit.html#append


void Gaia::on_senderButton_clicked()
{
    startServer("Center",1);
}

void Gaia::on_receiverButton_clicked()
{
    startClient("Center",1);
}

void Gaia::on_allButton_clicked()
{
    startServer("Left",0);
    startClient("Right",0);
}

void Gaia::startServer(const QString& position,int localMode){
    QIcon server(":/assets/server.png");
    Hermes *senderWindow = new Hermes;
    senderWindow->show();
    senderWindow->setWindowTitle("Server");
    senderWindow->setWindowIcon(server);
    movePosition(senderWindow,position);

    //localMode ? minerva->serverMode() : ui->minervaStatus->append("PiBoard Server is running locally");
    if (localMode) {
		minerva->serverMode();
        ui->minervaStatus->append("PiBoard Server has started");
    }
    else {
		ui->minervaStatus->append("PiBoard Server is running locally");
    }

};

void Gaia::startClient(const QString& position, int localMode){
    QIcon client(":/assets/client.png");
    Hephaestus *receiverwindow = new Hephaestus();
    receiverwindow->show();
    receiverwindow->setWindowIcon(client);
    receiverwindow->setWindowTitle("Reciever");
    movePosition(receiverwindow,position);

    //localMode ? minerva->serverMode() : ui->minervaStatus->append("PiBoard Client is running locally");
    if (localMode) {
        minerva->clientMode();
        ui->minervaStatus->append("PiBoard Client has started");
    }
    else {
		ui->minervaStatus->append("PiBoard Client is running locally");
	}
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
    // minerva->selectDataPin(pincount);
}

