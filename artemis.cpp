//Drawer
#include "artemis.h"

Artemis::Artemis() {

}

void Artemis::setStartPoint(QPointF start){
    startPoint = start;
};
void Artemis::setEndPoint(QPointF end){
    endPoint = end;
};
void Artemis::setMovingPoints(QPointF move){
    movingPoints = move;
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

void Artemis::drawLine(){

}
