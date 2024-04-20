/********************************************************************************
** Form generated from reading UI file 'sendwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDWINDOW_H
#define UI_SENDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Hermes
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SendWindow)
    {
        if (SendWindow->objectName().isEmpty())
            SendWindow->setObjectName("SendWindow");
        SendWindow->resize(800, 600);
        centralwidget = new QWidget(SendWindow);
        centralwidget->setObjectName("centralwidget");
        SendWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SendWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        SendWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SendWindow);
        statusbar->setObjectName("statusbar");
        SendWindow->setStatusBar(statusbar);

        retranslateUi(SendWindow);

        QMetaObject::connectSlotsByName(SendWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SendWindow)
    {
        SendWindow->setWindowTitle(QCoreApplication::translate("SendWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
class SendWindow: public Ui_Hermes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDWINDOW_H
