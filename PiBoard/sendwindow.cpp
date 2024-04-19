#include "sendwindow.h"
#include "ui_sendwindow.h"

SendWindow::SendWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SendWindow)
{
    ui->setupUi(this);
}

SendWindow::~SendWindow()
{
    delete ui;
}
