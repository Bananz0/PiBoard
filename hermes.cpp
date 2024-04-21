//Sender
//https://doc.qt.io/qt-6/qimage.html
//https://doc.qt.io/qt-6/qpainter.html

#include "hermes.h"
#include "ui_hermes.h"
#include <QPainter>
#include "gaia.h"

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
    delete drawDataPacket;
    delete ui;
    delete draw;
}

//From QT Docs
//https://doc.qt.io/qt-6/eventsandfilters.html
void Hermes::mouseReleaseEvent(QMouseEvent *event){
    qDebug() << "Mouse: " << event->position();
    drawDataPacket->endPoint = event->position();
    draw->setEndPoint(drawDataPacket->endPoint);
    update();
}

void Hermes::mousePressEvent(QMouseEvent *event){
    drawDataPacket->startPoint = event->position();
    draw->setStartPoint(drawDataPacket->startPoint);
    qDebug() << "Mouse: " << event->position();
    update();
}

void Hermes::mouseMoveEvent(QMouseEvent *event)  {
    drawDataPacket->movingPoint = event->position();
    draw->setMovingPoints(drawDataPacket->movingPoint);
    qDebug() << "Mouse: " << event->position();
    update();
}


void Hermes::on_clearCanvas_clicked()
{
    draw->clearCanvas(image);
    update();
}


void Hermes::paintEvent(QPaintEvent *event){
    QPainter painter(this);


    //Pen Properties
    drawDataPacket->pen.setColor(Qt::black);
    drawDataPacket->pen.setWidth(20);
    drawDataPacket->pen.setBrush(Qt::black);

    //Draw on the image
    painter.drawImage(0, 0, *image); 
   // painter.setRenderHint(QPainter::Antialiasing);

    QPainter imagePainter(image);
    //imagePainter.setRenderHint(QPainter::Antialiasing);

    drawOnCanvas(imagePainter, drawDataPacket->pen, drawDataPacket->drawMode);
 }

//https://stackoverflow.com/questions/12828825/how-to-assign-callback-when-the-user-resizes-a-qmainwindow
void Hermes::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    drawDataPacket->windowSize = this->size();
    qDebug() << "Height: " << drawDataPacket->windowSize.height() << "Width" << drawDataPacket->windowSize.width();
}

void Hermes::drawOnCanvas(QPainter& painter, QPen& pen, int drawMode) {
    switch (drawMode) {
    case 0:
        draw->drawLine(painter, pen);
        break;
    case 1:
        draw->drawPoint(painter, pen);
        break;
    case 2:
        draw->drawCircle(painter, pen);
		break;
    case 3:
		draw->drawRectangle(painter, pen);
		break;
    case 8:
        pen.setColor(Qt::white);
		draw->erasePoint(painter, pen);        
		break;
    default:        
        qDebug() << "Unexpected drawMode value:" << drawMode;
        qWarning() << "Unexpected drawMode value:" << drawMode;
        break;
    }
}

void Hermes::on_eraseButton_clicked(){
    drawDataPacket->drawMode = 8;
	qDebug() << "Erase Button Clicked";
	update();
}

void Hermes::on_drawCircle_clicked(){
    drawDataPacket->drawMode = 2;
	qDebug() << "Draw Circle Button Clicked";
	update();
}

void Hermes::on_drawRectangle_clicked(){
    drawDataPacket->drawMode = 3;
	qDebug() << "Draw Rectangle Button Clicked";
	update();
}

void Hermes::on_drawLine_clicked(){
	drawDataPacket->drawMode = 0;
	qDebug() << "Draw Line Button Clicked";
	update();
}

void Hermes::on_drawPoint_clicked(){
    drawDataPacket->drawMode = 1;
	qDebug() << "Draw Point Button Clicked";
	update();
}

void Hermes::penProperties_clicked(){
    //TODO
	//Open a new window to set pen properties
	//QPenDialog penDialog;
	//penDialog.exec();
	//pen.setColor(Qt::black);
	//pen.setWidth(20);
	//pen.setBrush(Qt::black);
	//update();
}
