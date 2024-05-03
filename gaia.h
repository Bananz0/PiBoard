#ifndef GAIA_H
#define GAIA_H

#include <QMainWindow>
#include "hermes.h"
#include "hephaestus.h"
#include <QScreen>
#include <QString>
#include "minerva.h"
#include "Epimetheus.h"
#include "Prometheus.h"

class Hermes;
class Hephaestus;

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
    void on_testDMAbutton_clicked();
    void testDMA();
    QString testPins();
    void on_pinTestButton_clicked();

private:
    Ui::Gaia *ui;
    Hermes* senderWindow;
    Hephaestus* receiverWindow;
    Minerva* minervaOut;
    Minerva* minervaIn;
    Epimetheus* epimetheus;
    Prometheus* prometheus;
    EpimetheusThread* epimetheusThread;
    PrometheusThread* prometheusThread;

};
#endif // GAIA_H
