/********************************************************************************
** Form generated from reading UI file 'hermes.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HERMES_H
#define UI_HERMES_H

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

    void setupUi(QMainWindow *Hermes)
    {
        if (Hermes->objectName().isEmpty())
            Hermes->setObjectName("Hermes");
        Hermes->resize(800, 600);
        centralwidget = new QWidget(Hermes);
        centralwidget->setObjectName("centralwidget");
        Hermes->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Hermes);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        Hermes->setMenuBar(menubar);
        statusbar = new QStatusBar(Hermes);
        statusbar->setObjectName("statusbar");
        Hermes->setStatusBar(statusbar);

        retranslateUi(Hermes);

        QMetaObject::connectSlotsByName(Hermes);
    } // setupUi

    void retranslateUi(QMainWindow *Hermes)
    {
        Hermes->setWindowTitle(QCoreApplication::translate("Hermes", "Hermes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Hermes: public Ui_Hermes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HERMES_H
