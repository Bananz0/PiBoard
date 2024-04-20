#ifndef HEPHAESTUS_H
#define HEPHAESTUS_H

#include <QMainWindow>

namespace Ui {
class Hephaestus;
}

class Hephaestus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hephaestus(QWidget *parent = nullptr);
    ~Hephaestus();

private:
    Ui::Hephaestus *ui;
};

#endif // HEPHAESTUS_H
