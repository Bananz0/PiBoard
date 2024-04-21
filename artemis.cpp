//Drawer
#include "artemis.h"

Artemis::Artemis() {

}

void Artemis::setStartPoint(QPointF start){
    startPoint = onlyOnCanvas(start);
};
void Artemis::setEndPoint(QPointF end){
    endPoint = onlyOnCanvas(end);
};
void Artemis::setMovingPoints(QPointF move){
    movingPoints = onlyOnCanvas(move);
};

QPointF Artemis::getStartPoint(){
    return startPoint;
};
QPointF Artemis::getEndPoint(){
    return endPoint;
};
QPointF Artemis::getMovingPoints(){
    return movingPoints;
};

void Artemis::drawPoint(QPainter& painter, QPen& pen){
    painter.setPen(pen);
    painter.drawPoint(movingPoints);
}

void Artemis::drawLine(QPainter& painter,QPen& pen) {
    painter.setPen(pen);
    painter.drawLine(startPoint, endPoint);
}

void Artemis::drawCircle(QPainter& painter, QPen& pen){
    int radius = (endPoint.x() - startPoint.x())/2;
    painter.setPen(pen);
	painter.drawEllipse(startPoint.x(), startPoint.y(), radius, radius);
}

void Artemis::drawRectangle(QPainter& painter, QPen& pen){
    int rectWidth = endPoint.x() - startPoint.x();
    int rectHeight = endPoint.y() - startPoint.y();
    painter.setPen(pen);
	painter.drawRect(startPoint.x(), startPoint.y(), rectWidth, rectHeight);
}

void Artemis::erasePoint(QPainter& painter, QPen& pen) {
	painter.setPen(pen);
	painter.drawPoint(movingPoints);
}

void Artemis::clearCanvas(QImage* image) {
	image->fill(Qt::white);
}

QPointF Artemis::onlyOnCanvas(QPointF canvasPoint) {
    if (canvasPoint.x() > 800 ) {
		canvasPoint.setX(0);
	}
    if (canvasPoint.y() > 600) {
		canvasPoint.setY(0);
	}
	return canvasPoint;
}