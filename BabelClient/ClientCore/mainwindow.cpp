#include "mainwindow.hpp"
#include "UserResponse.hpp"
#include "./ui_mainwindow.h"

#include <QtDebug>
#include <QAbstractButton>
#include <QSignalMapper>
#include <QObject>
#include <string>
#include <iostream>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent, ISocket *core) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    socket = core;

    ui->setupUi(this);

    ui->VLayout = new QVBoxLayout(ui->ContactArea);


    QPushButton *button1 = new QPushButton("1", ui->ContactArea);
    QPushButton *button2 = new QPushButton("2", ui->ContactArea);
    QPushButton *button3 = new QPushButton("3", ui->ContactArea);
    QPushButton *button4 = new QPushButton("4", ui->ContactArea);
    QPushButton *button5 = new QPushButton("5", ui->ContactArea);
    QPushButton *button6 = new QPushButton("6", ui->ContactArea);
    QPushButton *button7 = new QPushButton("7", ui->ContactArea);
    QPushButton *button8 = new QPushButton("8", ui->ContactArea);
    QPushButton *button9 = new QPushButton("9", ui->ContactArea);


    ui->VLayout->addWidget(button1);
    ui->VLayout->addWidget(button2);
    ui->VLayout->addWidget(button3);
    ui->VLayout->addWidget(button4);
    ui->VLayout->addWidget(button5);
    ui->VLayout->addWidget(button6);
    ui->VLayout->addWidget(button7);
    ui->VLayout->addWidget(button8);
    ui->VLayout->addWidget(button9);


    //to count all of button in contact area
    QList<QPushButton *> butts = ui->ContactArea->findChildren<QPushButton *>();
    qDebug() << butts.size();

    qDebug() << butts[0]->text();

    QSignalMapper *mapper = new QSignalMapper();
    for (auto &button : butts) {
        connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(button, button->text());
        connect(mapper, SIGNAL(mapped(const QString &)), this, SLOT(coucou(const QString &)));
    }
    ui->WrongLoginText->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*          EVENT FRONT         */

void MainWindow::coucou(const QString &name)
{
    ui->ContactName->setMarkdown(name);
    //std::cout << "coucou fonction" << std::endl;
}

void MainWindow::on_ConnectionButton_clicked()
{
    /*
    qDebug()<< ui->UserLine->text();
    qDebug()<< ui->PassLine->text();
    */
    std::string user = ui->UserLine->text().toLocal8Bit().constData();
    std::string pass = ui->PassLine->text().toLocal8Bit().constData();

    //ui->gridStackedWidget->setCurrentWidget(ui->CallPage);
    auto response = BabelNetwork::UserResponse::NewLoginRequest(user, pass);
    std::cout << response->getCode() << std::endl;
    std::cout << "PTDR" << std::endl;
    socket->writeData(response);
}

void MainWindow::on_DisconnectButton_clicked()
{
    ui->gridStackedWidget->setCurrentWidget(ui->LoginWidget);
}

void MainWindow::on_AddFriendButton_clicked()
{

}

void MainWindow::on_DeleteFriendButton_clicked()
{

}

void MainWindow::on_ManageFriendButton_clicked()
{
    ui->gridStackedWidget->setCurrentWidget(ui->ManageFriendPage);
}

void MainWindow::on_BackButton_clicked()
{
    ui->gridStackedWidget->setCurrentWidget(ui->CallPage);
}

void MainWindow::on_BackButtonRegister_clicked()
{
    ui->gridStackedWidget->setCurrentWidget(ui->LoginWidget);
}

void MainWindow::on_ToRegisterButton_clicked()
{
    ui->gridStackedWidget->setCurrentWidget(ui->RegisterPage);
}

void MainWindow::on_RegisterButton_clicked()
{
    std::string user = ui->UserRegisterLine->text().toLocal8Bit().constData();
    std::string pass = ui->PasswordRegisterLine->text().toLocal8Bit().constData();

    auto response = BabelNetwork::UserResponse::AccountCreationRequest(user, pass);
    socket->writeData(response);
}