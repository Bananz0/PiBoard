//Sender
//https://doc.qt.io/qt-6/qimage.html
//https://doc.qt.io/qt-6/qpainter.html

#include "hermes.h"
#include "ui_hermes.h"
#include <QPainter>

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


void Hermes::on_clearCanvas_clicked()
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
   // painter.setRenderHint(QPainter::Antialiasing);

    QPainter imagePainter(image);
    //imagePainter.setRenderHint(QPainter::Antialiasing);
    drawOnCanvas(imagePainter, pen, drawMode);    
 }

//https://stackoverflow.com/questions/12828825/how-to-assign-callback-when-the-user-resizes-a-qmainwindow
void Hermes::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    QSize size = this->size();
    qDebug() << "Height: " <<size.height() << "Width" << size.width();
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
    drawMode = 8;
	qDebug() << "Erase Button Clicked";
	update();
}

void Hermes::on_drawCircle_clicked(){
    drawMode = 2;
	qDebug() << "Draw Circle Button Clicked";
	update();
}

void Hermes::on_drawRectangle_clicked(){
    drawMode = 3;
	qDebug() << "Draw Rectangle Button Clicked";
	update();
}

void Hermes::on_drawLine_clicked(){
	drawMode = 0;
	qDebug() << "Draw Line Button Clicked";
	update();
}

void Hermes::on_drawPoint_clicked(){
    drawMode = 1;
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
