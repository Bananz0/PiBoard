//Sender
//https://doc.qt.io/qt-6/qimage.html
//https://doc.qt.io/qt-6/qpainter.html

#include "hermes.h"
#include "ui_hermes.h"
#include <QPainter>
#include <QImage>



Hermes::Hermes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Hermes)
{
    ui->setupUi(this);
    setMouseTracking(true);

    image = new QImage(800, 600, QImage::Format_RGB32);
    image->fill(Qt::white);
}

Hermes::~Hermes()
{
    delete ui;
    delete draw;
}

//From QT Docs
//https://doc.qt.io/qt-6/eventsandfilters.html

void Hermes::mouseReleaseEvent(QMouseEvent *event){
    qDebug() << "Mouse: " << event->position();
    draw->setEndPoint(event->position());
    update();
}

void Hermes::mousePressEvent(QMouseEvent *event){
    draw->setStartPoint(event->position());
    qDebug() << "Mouse: " << event->position();
    update();
}

void Hermes::mouseMoveEvent(QMouseEvent *event)  {
    draw->setMovingPoints(event->position());
    qDebug() << "Mouse: " << event->position();
    update();
}

void Hermes::on_clearCanvasButton_clicked()
{
    draw->clearCanvas(image);
    update();
}

void Hermes::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen pen;

    //Pen Properties
    pen.setColor(Qt::black);
    pen.setWidth(20);
    pen.setBrush(Qt::black);

    //Draw on the image
    painter.drawImage(0, 0, *image); 
    painter.setRenderHint(QPainter::Antialiasing);

    QPainter imagePainter(image);
    imagePainter.setRenderHint(QPainter::Antialiasing);


    draw->drawLine(imagePainter,pen);
   
    
 }

//https://stackoverflow.com/questions/12828825/how-to-assign-callback-when-the-user-resizes-a-qmainwindow

void Hermes::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    QSize size = this->size();
    qDebug() << "Height: " <<size.height() << "Width" << size.width();


}
