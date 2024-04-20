/********************************************************************************
** Form generated from reading UI file 'receivewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEIVEWINDOW_H
#define UI_RECEIVEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Hephaestus
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ReceiveWindow)
    {
        if (ReceiveWindow->objectName().isEmpty())
            ReceiveWindow->setObjectName("ReceiveWindow");
        ReceiveWindow->resize(800, 600);
        centralwidget = new QWidget(ReceiveWindow);
        centralwidget->setObjectName("centralwidget");
        ReceiveWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ReceiveWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        ReceiveWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ReceiveWindow);
        statusbar->setObjectName("statusbar");
        ReceiveWindow->setStatusBar(statusbar);

        retranslateUi(ReceiveWindow);

        QMetaObject::connectSlotsByName(ReceiveWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ReceiveWindow)
    {
        ReceiveWindow->setWindowTitle(QCoreApplication::translate("ReceiveWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
class Hephaestus: public Hephaestus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEIVEWINDOW_H
