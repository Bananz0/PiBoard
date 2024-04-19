#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_senderButton_clicked()
{
    SendWindow *senderwindow = new SendWindow;
    senderwindow->show();
}


void MainWindow::on_receiverButton_clicked()
{
    ReceiveWindow *receiverwindow = new ReceiveWindow;
    receiverwindow->show();
}


void MainWindow::on_allButton_clicked()
{
    SendWindow *senderwindow = new SendWindow;
    ReceiveWindow *receiverwindow = new ReceiveWindow;

    receiverwindow->show();
    senderwindow->show();
}

