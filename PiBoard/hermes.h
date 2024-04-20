#ifndef HERMES_H
#define HERMES_H

#include <QMainWindow>

namespace Ui {
class Hermes;
}

class Hermes : public QMainWindow
{
    Q_OBJECT

public:
    explicit Hermes(QWidget *parent = nullptr);
    ~Hermes();

private:
    Ui::Hermes *ui;
};

#endif // HERMES_H
