#ifndef HEPHAESTUS_H
#define HEPHAESTUS_H

#include <QMainWindow>
#include "artemis.h"
#include "minerva.h"


namespace Ui {
class Hephaestus;
}

class Hephaestus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hephaestus(QWidget *parent = nullptr);
    ~Hephaestus();
    Artemis *draw = new Artemis;
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::Hephaestus *ui;
    QImage* image;
};

#endif // HEPHAESTUS_H
