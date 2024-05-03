
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
    minervaOut = new Minerva();
    minervaIn = new Minerva();
    ui->setupUi(this);
    ui->minervaStatus->setText("Welcome to PiBoard");
    ui->minervaStatus->append(minervaIn->testConnection());

    //Start thread and worker
    epimetheusThread = new EpimetheusThread();
    prometheusThread = new PrometheusThread();
    epimetheus = new Epimetheus(minervaIn);
    prometheus = new Prometheus(minervaOut);

    //Start Send and receive timer
    sendTimer = new QTimer();
    sendTimer->start(5);
    recTimer = new QTimer();
    recTimer->start(5);
    QObject::connect(sendTimer, &QTimer::timeout, prometheus, &Prometheus::sendDataUsingThread);
    QObject::connect(recTimer, &QTimer::timeout, epimetheus, &Epimetheus::receiveDataUsingThread);

    recTimer->moveToThread(epimetheusThread);
    sendTimer->moveToThread(prometheusThread);
}

Gaia::~Gaia()
{
    delete sendTimer, recTimer;
    delete epimetheus;
    delete prometheus;
    delete epimetheusThread;
    delete prometheusThread;
    delete senderWindow;
    delete receiverWindow;
    delete minervaOut;
    delete minervaIn;
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
    prometheus->moveToThread(prometheusThread);
    QObject::connect(prometheusThread, &QThread::started, prometheus, &Prometheus::sendDataUsingThread);
    prometheusThread->start();
    QIcon server(":/assets/server.png");
    senderWindow = new Hermes(minervaOut);
    senderWindow->show();
    senderWindow->setWindowTitle("Server");
    senderWindow->setWindowIcon(server);
    movePosition(senderWindow,position);
    //localMode ? minerva->serverMode() : ui->minervaStatus->append("PiBoard Server is running locally");
    if (localMode) {
		minervaOut->serverMode();
        ui->minervaStatus->append("PiBoard Server has started");
    }
    else {
		ui->minervaStatus->append("PiBoard Server is running locally");
    }

};

void Gaia::startClient(const QString& position, int localMode){
    epimetheus->moveToThread(epimetheusThread);
    QObject::connect(epimetheusThread, &QThread::started, epimetheus, &Epimetheus::receiveDataUsingThread);

    epimetheusThread->start();
    QIcon client(":/assets/client.png");
    minervaIn->sendDataPacket->drawMode=0;
    minervaIn->decodeData();
    receiverWindow = new Hephaestus(minervaIn);
    receiverWindow->show();
    receiverWindow->setWindowIcon(client);
    receiverWindow->setWindowTitle("Reciever");
    movePosition(receiverWindow,position);

    //localMode ? minerva->serverMode() : ui->minervaStatus->append("PiBoard Client is running locally");
    if (localMode) {
        minervaIn->clientMode();
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

