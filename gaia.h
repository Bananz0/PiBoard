#ifndef GAIA_H
#define GAIA_H

#include <QMainWindow>
#include "hermes.h"
#include "hephaestus.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Gaia;
}
QT_END_NAMESPACE

class Gaia : public QMainWindow
{
    Q_OBJECT

public:
    Gaia(QWidget *parent = nullptr);
    ~Gaia();
    void startServer();
    void startClient();

private slots:
    void on_senderButton_clicked();
    void on_receiverButton_clicked();
    void on_allButton_clicked();


private:
    Ui::Gaia *ui;
};
#endif // GAIA_H
