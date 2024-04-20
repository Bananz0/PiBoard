#include "gaia.h"
#include <QApplication>
#include <QTimer>
#include <QSplashScreen>

/*
I've got the worst idea to name every class
after some amazing game I played and gave a
9/10.
Why?
Great question.
Good luck future me, you'll need it.
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("PiBoard: An MS: Paint Knockoff");
    a.setApplicationVersion("0.0.1");

    QIcon icon(":/assets/icon-48.png");

    a.setWindowIcon(icon);


    QSplashScreen *splash =new QSplashScreen;
    splash->setPixmap(QPixmap(":/assets/splash.png"));
    splash->show();

    Gaia *w = new Gaia;

    QTimer::singleShot(2500,splash,SLOT(close()));
    QTimer::singleShot(2500,w,SLOT(show()));

    w->setWindowTitle("PiBoard: Raspberry Pi Whiteboard Knockoff");
    w->setWindowIcon(icon);


    return a.exec();
}
