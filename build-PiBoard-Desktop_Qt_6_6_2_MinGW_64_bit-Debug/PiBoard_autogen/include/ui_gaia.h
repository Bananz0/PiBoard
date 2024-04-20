/********************************************************************************
** Form generated from reading UI file 'gaia.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAIA_H
#define UI_GAIA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Gaia
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *allButton;
    QPushButton *receiverButton;
    QSpacerItem *verticalSpacer;
    QPushButton *senderButton;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Gaia)
    {
        if (Gaia->objectName().isEmpty())
            Gaia->setObjectName("Gaia");
        Gaia->resize(800, 600);
        centralwidget = new QWidget(Gaia);
        centralwidget->setObjectName("centralwidget");
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        allButton = new QPushButton(centralwidget);
        allButton->setObjectName("allButton");

        gridLayout->addWidget(allButton, 4, 0, 1, 1);

        receiverButton = new QPushButton(centralwidget);
        receiverButton->setObjectName("receiverButton");

        gridLayout->addWidget(receiverButton, 3, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        senderButton = new QPushButton(centralwidget);
        senderButton->setObjectName("senderButton");

        gridLayout->addWidget(senderButton, 2, 0, 1, 1);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");

        gridLayout->addWidget(textBrowser, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        Gaia->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Gaia);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        Gaia->setMenuBar(menubar);
        statusbar = new QStatusBar(Gaia);
        statusbar->setObjectName("statusbar");
        Gaia->setStatusBar(statusbar);

        retranslateUi(Gaia);

        QMetaObject::connectSlotsByName(Gaia);
    } // setupUi

    void retranslateUi(QMainWindow *Gaia)
    {
        Gaia->setWindowTitle(QCoreApplication::translate("Gaia", "Gaia", nullptr));
        allButton->setText(QCoreApplication::translate("Gaia", "Local Mode", nullptr));
        receiverButton->setText(QCoreApplication::translate("Gaia", "Client Mode", nullptr));
        senderButton->setText(QCoreApplication::translate("Gaia", "Server Mode", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Gaia: public Ui_Gaia {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAIA_H
