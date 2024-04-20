/********************************************************************************
** Form generated from reading UI file 'hephaestus.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HEPHAESTUS_H
#define UI_HEPHAESTUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Hephaestus
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Hephaestus)
    {
        if (Hephaestus->objectName().isEmpty())
            Hephaestus->setObjectName("Hephaestus");
        Hephaestus->resize(800, 600);
        centralwidget = new QWidget(Hephaestus);
        centralwidget->setObjectName("centralwidget");
        Hephaestus->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Hephaestus);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        Hephaestus->setMenuBar(menubar);
        statusbar = new QStatusBar(Hephaestus);
        statusbar->setObjectName("statusbar");
        Hephaestus->setStatusBar(statusbar);

        retranslateUi(Hephaestus);

        QMetaObject::connectSlotsByName(Hephaestus);
    } // setupUi

    void retranslateUi(QMainWindow *Hephaestus)
    {
        Hephaestus->setWindowTitle(QCoreApplication::translate("Hephaestus", "Hephaestus", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Hephaestus: public Ui_Hephaestus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HEPHAESTUS_H
