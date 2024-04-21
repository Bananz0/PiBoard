#ifndef GAIA_H
#define GAIA_H

#include <QMainWindow>
#include "hermes.h"
#include "hephaestus.h"
#include <QScreen>
#include <QString>
#include "artemis.h"
#include "minerva.h"


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
    void startServer(const QString& position, int localMode);
    void startClient(const QString& position, int localMode);
    void movePosition(QMainWindow* window, const QString &position);
    void selectDataPinCount(int pincount);

private slots:
    void on_senderButton_clicked();
    void on_receiverButton_clicked();
    void on_allButton_clicked();

private:
    Ui::Gaia *ui;
    Minerva* minerva = new Minerva;
};
#endif // GAIA_H
