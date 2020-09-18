/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *IpLine;
    QLineEdit *PortLine;
    QLineEdit *UserLine;
    QLineEdit *PassLine;
    QPushButton *ConnectionButton;
    QPushButton *QuitButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(180, 90, 301, 241));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        IpLine = new QLineEdit(verticalLayoutWidget);
        IpLine->setObjectName(QString::fromUtf8("IpLine"));

        verticalLayout->addWidget(IpLine);

        PortLine = new QLineEdit(verticalLayoutWidget);
        PortLine->setObjectName(QString::fromUtf8("PortLine"));

        verticalLayout->addWidget(PortLine);

        UserLine = new QLineEdit(verticalLayoutWidget);
        UserLine->setObjectName(QString::fromUtf8("UserLine"));

        verticalLayout->addWidget(UserLine);

        PassLine = new QLineEdit(verticalLayoutWidget);
        PassLine->setObjectName(QString::fromUtf8("PassLine"));
        PassLine->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(PassLine);

        ConnectionButton = new QPushButton(verticalLayoutWidget);
        ConnectionButton->setObjectName(QString::fromUtf8("ConnectionButton"));

        verticalLayout->addWidget(ConnectionButton);

        QuitButton = new QPushButton(verticalLayoutWidget);
        QuitButton->setObjectName(QString::fromUtf8("QuitButton"));

        verticalLayout->addWidget(QuitButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(QuitButton, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(accessibility)
        MainWindow->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        IpLine->setText(QString());
        IpLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        PortLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        UserLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "User", nullptr));
        PassLine->setInputMask(QString());
        PassLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        ConnectionButton->setText(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        QuitButton->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
