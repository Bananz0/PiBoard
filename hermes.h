#ifndef HERMES_H
#define HERMES_H

#include <QMainWindow>
#include <QMouseEvent>
#include "artemis.h"
#include "minerva.h"



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

    Artemis *draw = new Artemis;

private:
    Ui::Hermes *ui;
};

#endif // HERMES_H
