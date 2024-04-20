#ifndef HEPHAESTUS_H
#define HEPHAESTUS_H

#include <QMainWindow>
#include "artemis.h"


namespace Ui {
class Hephaestus;
}

class Hephaestus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hephaestus(QWidget *parent = nullptr);
    ~Hephaestus();
    void mouseReleaseEvent(QMouseEvent *event) override;
    Artemis *draw = new Artemis;

private:
    Ui::Hephaestus *ui;
};

#endif // HEPHAESTUS_H
