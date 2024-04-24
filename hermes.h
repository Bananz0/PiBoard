#ifndef HERMES_H
#define HERMES_H

#include <QMainWindow>
#include <QMouseEvent>
#include "artemis.h"
#include <QImage>
#include "minerva.h"


namespace Ui {
class Hermes;
}

class Hermes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hermes(Minerva* minerva, QWidget* parent = nullptr);
    ~Hermes();    

private:
    Ui::Hermes *ui;
    QImage* image;
    Artemis* draw = new Artemis;
    Minerva* minervaOut;

    int timerId = 0;

    void mouseReleaseEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void initializePenProperties();
    void drawOnCanvas(QPainter& painter, QPen& pen, int drawMode);
    void setPenProperties(QPen& pen);


private slots:
    void on_clearCanvas_clicked();
    void on_eraseButton_clicked();
    void on_drawCircle_clicked();
    void on_drawRectangle_clicked();
    void on_drawLine_clicked();
    void on_drawPoint_clicked();
    void penProperties_clicked();

protected: 
    void timerEvent(QTimerEvent* event) override;
};

#endif // HERMES_H
