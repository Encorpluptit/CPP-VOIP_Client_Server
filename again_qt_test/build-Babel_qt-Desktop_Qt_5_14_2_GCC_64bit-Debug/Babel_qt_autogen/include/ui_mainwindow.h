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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *gridStackedWidget;
    QWidget *LoginWidget;
    QGridLayout *gridLayout;
    QLineEdit *UserLine;
    QPushButton *QuitButton;
    QLineEdit *PassLine;
    QTextEdit *WrongLoginText;
    QPushButton *ConnectionButton;
    QPushButton *ToRegisterButton;
    QWidget *RegisterPage;
    QWidget *formLayoutWidget_3;
    QFormLayout *formLayout_2;
    QLineEdit *UserRegisterLine;
    QLineEdit *PasswordRegisterLine;
    QPushButton *RegisterButton;
    QPushButton *BackButtonRegister;
    QWidget *CallPage;
    QWidget *formLayoutWidget;
    QFormLayout *CallLayout;
    QTextEdit *ContactName;
    QVBoxLayout *VLayout;
    QScrollArea *ContactList;
    QWidget *ContactArea;
    QTextEdit *HistoricMessages;
    QTextEdit *NewMessages;
    QPushButton *CallButton;
    QPushButton *HangOutButton;
    QPushButton *DisconnectButton;
    QPushButton *ManageFriendButton;
    QWidget *ManageFriendPage;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout;
    QLineEdit *SearchFriendLine;
    QPushButton *AddFriendButton;
    QPushButton *DeleteFriendButton;
    QTextEdit *textEdit;
    QPushButton *BackButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(683, 629);
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridStackedWidget = new QStackedWidget(centralwidget);
        gridStackedWidget->setObjectName(QString::fromUtf8("gridStackedWidget"));
        gridStackedWidget->setGeometry(QRect(120, 80, 391, 351));
        gridStackedWidget->setMaximumSize(QSize(5000, 5000));
        gridStackedWidget->setContextMenuPolicy(Qt::NoContextMenu);
        LoginWidget = new QWidget();
        LoginWidget->setObjectName(QString::fromUtf8("LoginWidget"));
        LoginWidget->setMaximumSize(QSize(5000, 5000));
        gridLayout = new QGridLayout(LoginWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        UserLine = new QLineEdit(LoginWidget);
        UserLine->setObjectName(QString::fromUtf8("UserLine"));

        gridLayout->addWidget(UserLine, 3, 0, 1, 1);

        QuitButton = new QPushButton(LoginWidget);
        QuitButton->setObjectName(QString::fromUtf8("QuitButton"));

        gridLayout->addWidget(QuitButton, 8, 0, 1, 1);

        PassLine = new QLineEdit(LoginWidget);
        PassLine->setObjectName(QString::fromUtf8("PassLine"));
        PassLine->setEchoMode(QLineEdit::Password);
        PassLine->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(PassLine, 4, 0, 1, 1);

        WrongLoginText = new QTextEdit(LoginWidget);
        WrongLoginText->setObjectName(QString::fromUtf8("WrongLoginText"));
        WrongLoginText->setMaximumSize(QSize(100, 30));
        WrongLoginText->setContextMenuPolicy(Qt::DefaultContextMenu);
        WrongLoginText->setReadOnly(true);

        gridLayout->addWidget(WrongLoginText, 5, 0, 1, 1);

        ConnectionButton = new QPushButton(LoginWidget);
        ConnectionButton->setObjectName(QString::fromUtf8("ConnectionButton"));

        gridLayout->addWidget(ConnectionButton, 6, 0, 1, 1);

        ToRegisterButton = new QPushButton(LoginWidget);
        ToRegisterButton->setObjectName(QString::fromUtf8("ToRegisterButton"));

        gridLayout->addWidget(ToRegisterButton, 7, 0, 1, 1);

        gridStackedWidget->addWidget(LoginWidget);
        RegisterPage = new QWidget();
        RegisterPage->setObjectName(QString::fromUtf8("RegisterPage"));
        formLayoutWidget_3 = new QWidget(RegisterPage);
        formLayoutWidget_3->setObjectName(QString::fromUtf8("formLayoutWidget_3"));
        formLayoutWidget_3->setGeometry(QRect(20, 10, 271, 281));
        formLayout_2 = new QFormLayout(formLayoutWidget_3);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        UserRegisterLine = new QLineEdit(formLayoutWidget_3);
        UserRegisterLine->setObjectName(QString::fromUtf8("UserRegisterLine"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, UserRegisterLine);

        PasswordRegisterLine = new QLineEdit(formLayoutWidget_3);
        PasswordRegisterLine->setObjectName(QString::fromUtf8("PasswordRegisterLine"));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, PasswordRegisterLine);

        RegisterButton = new QPushButton(formLayoutWidget_3);
        RegisterButton->setObjectName(QString::fromUtf8("RegisterButton"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, RegisterButton);

        BackButtonRegister = new QPushButton(formLayoutWidget_3);
        BackButtonRegister->setObjectName(QString::fromUtf8("BackButtonRegister"));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, BackButtonRegister);

        gridStackedWidget->addWidget(RegisterPage);
        CallPage = new QWidget();
        CallPage->setObjectName(QString::fromUtf8("CallPage"));
        formLayoutWidget = new QWidget(CallPage);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(60, 10, 411, 531));
        CallLayout = new QFormLayout(formLayoutWidget);
        CallLayout->setObjectName(QString::fromUtf8("CallLayout"));
        CallLayout->setContentsMargins(0, 0, 0, 0);
        ContactName = new QTextEdit(formLayoutWidget);
        ContactName->setObjectName(QString::fromUtf8("ContactName"));
        ContactName->setMaximumSize(QSize(120, 40));
        ContactName->setContextMenuPolicy(Qt::DefaultContextMenu);
        ContactName->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ContactName->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ContactName->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        ContactName->setReadOnly(true);
        ContactName->setMarkdown(QString::fromUtf8("Ugo\n"
"\n"
""));

        CallLayout->setWidget(0, QFormLayout::FieldRole, ContactName);

        VLayout = new QVBoxLayout();
        VLayout->setObjectName(QString::fromUtf8("VLayout"));
        ContactList = new QScrollArea(formLayoutWidget);
        ContactList->setObjectName(QString::fromUtf8("ContactList"));
        ContactList->setMinimumSize(QSize(100, 100));
        ContactList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        ContactList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ContactList->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        ContactList->setWidgetResizable(true);
        ContactList->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        ContactArea = new QWidget();
        ContactArea->setObjectName(QString::fromUtf8("ContactArea"));
        ContactArea->setGeometry(QRect(0, 0, 84, 185));
        ContactList->setWidget(ContactArea);

        VLayout->addWidget(ContactList);


        CallLayout->setLayout(2, QFormLayout::LabelRole, VLayout);

        HistoricMessages = new QTextEdit(formLayoutWidget);
        HistoricMessages->setObjectName(QString::fromUtf8("HistoricMessages"));

        CallLayout->setWidget(2, QFormLayout::FieldRole, HistoricMessages);

        NewMessages = new QTextEdit(formLayoutWidget);
        NewMessages->setObjectName(QString::fromUtf8("NewMessages"));

        CallLayout->setWidget(3, QFormLayout::FieldRole, NewMessages);

        CallButton = new QPushButton(formLayoutWidget);
        CallButton->setObjectName(QString::fromUtf8("CallButton"));

        CallLayout->setWidget(4, QFormLayout::FieldRole, CallButton);

        HangOutButton = new QPushButton(formLayoutWidget);
        HangOutButton->setObjectName(QString::fromUtf8("HangOutButton"));

        CallLayout->setWidget(5, QFormLayout::FieldRole, HangOutButton);

        DisconnectButton = new QPushButton(formLayoutWidget);
        DisconnectButton->setObjectName(QString::fromUtf8("DisconnectButton"));

        CallLayout->setWidget(6, QFormLayout::FieldRole, DisconnectButton);

        ManageFriendButton = new QPushButton(formLayoutWidget);
        ManageFriendButton->setObjectName(QString::fromUtf8("ManageFriendButton"));

        CallLayout->setWidget(5, QFormLayout::LabelRole, ManageFriendButton);

        gridStackedWidget->addWidget(CallPage);
        ManageFriendPage = new QWidget();
        ManageFriendPage->setObjectName(QString::fromUtf8("ManageFriendPage"));
        formLayoutWidget_2 = new QWidget(ManageFriendPage);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(130, 40, 271, 401));
        formLayout = new QFormLayout(formLayoutWidget_2);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        SearchFriendLine = new QLineEdit(formLayoutWidget_2);
        SearchFriendLine->setObjectName(QString::fromUtf8("SearchFriendLine"));

        formLayout->setWidget(0, QFormLayout::FieldRole, SearchFriendLine);

        AddFriendButton = new QPushButton(formLayoutWidget_2);
        AddFriendButton->setObjectName(QString::fromUtf8("AddFriendButton"));

        formLayout->setWidget(3, QFormLayout::FieldRole, AddFriendButton);

        DeleteFriendButton = new QPushButton(formLayoutWidget_2);
        DeleteFriendButton->setObjectName(QString::fromUtf8("DeleteFriendButton"));

        formLayout->setWidget(4, QFormLayout::FieldRole, DeleteFriendButton);

        textEdit = new QTextEdit(formLayoutWidget_2);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMaximumSize(QSize(120, 30));
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        formLayout->setWidget(1, QFormLayout::FieldRole, textEdit);

        BackButton = new QPushButton(formLayoutWidget_2);
        BackButton->setObjectName(QString::fromUtf8("BackButton"));

        formLayout->setWidget(5, QFormLayout::FieldRole, BackButton);

        gridStackedWidget->addWidget(ManageFriendPage);
        MainWindow->setCentralWidget(centralwidget);

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
        UserLine->setInputMask(QString());
        UserLine->setText(QString());
        UserLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "User", nullptr));
        QuitButton->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
        PassLine->setInputMask(QString());
        PassLine->setText(QString());
        PassLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        WrongLoginText->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ef2929;\">Wrong Login</span></p></body></html>", nullptr));
        ConnectionButton->setText(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        ToRegisterButton->setText(QCoreApplication::translate("MainWindow", "Register", nullptr));
        UserRegisterLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "New User", nullptr));
        PasswordRegisterLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "New Password", nullptr));
        RegisterButton->setText(QCoreApplication::translate("MainWindow", "Register", nullptr));
        BackButtonRegister->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        ContactName->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:6px; margin-bottom:6px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Ugo</p></body></html>", nullptr));
        CallButton->setText(QCoreApplication::translate("MainWindow", "Call", nullptr));
        HangOutButton->setText(QCoreApplication::translate("MainWindow", "HangOut", nullptr));
        DisconnectButton->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        ManageFriendButton->setText(QCoreApplication::translate("MainWindow", "Manage Friend", nullptr));
        SearchFriendLine->setInputMask(QString());
        SearchFriendLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search Friend", nullptr));
        AddFriendButton->setText(QCoreApplication::translate("MainWindow", "Add Friend", nullptr));
        DeleteFriendButton->setText(QCoreApplication::translate("MainWindow", "Delete Friend", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ef2929;\">Can't find friend</span></p></body></html>", nullptr));
        BackButton->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
