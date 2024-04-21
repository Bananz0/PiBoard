#ifndef HERMES_H
#define HERMES_H

#include <QMainWindow>
#include <QMouseEvent>
#include "artemis.h"
#include "minerva.h"
#include <QImage>



namespace Ui {
class Hermes;
}

class Hermes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hermes(QWidget *parent = nullptr);
    ~Hermes();

    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;
    void drawOnCanvas(QPainter& painter, QPen& pen, int drawMode);




private:
    int drawMode = 0;
    Ui::Hermes *ui;
    QImage* image;
    Artemis* draw = new Artemis;

private slots:
    void on_clearCanvas_clicked();
};

#endif // HERMES_H
