#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QAbstractButton>
#include <QSignalMapper>
#include <QtDebug>
#include <QObject>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QVBoxLayout *hlayout = new QVBoxLayout;

    //VLayout->addWidget(ui->ContactList);

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


    //setLayout(VLayout);

    //ui->CallLayout->addWidget(button1);
    //ui->ContactList->setWidget(ui->ContactArea);
    /*ui->ContactList->setWidget(button2);
    ui->ContactList->setWidget(button3);
    ui->ContactList->setWidget(button4);
    ui->ContactList->setWidget(button5);
    ui->ContactList->setWidget(button6);
    ui->ContactList->setWidget(button7);
    ui->ContactList->setWidget(button8);
    ui->ContactList->setWidget(button9);
    ui->ContactList->setWidget(button10);
    */

    //std::cout << ui->gridStackedWidgetPage1->indexOf(ui->LoginWidget) << std::endl;
    //ui->WrongLoginText->hide();
    //ui->LogedWidget->hide();
}

void MainWindow::coucou(const QString &name)
{
    ui->ContactName->setMarkdown(name);
    //std::cout << "coucou fonction" << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ConnectionButton_clicked()
{
    /*
    qDebug()<< ui->UserLine->text();
    qDebug()<< ui->PassLine->text();
    */
    std::string user = ui->UserLine->text().toLocal8Bit().constData();
    std::string pass = ui->PassLine->text().toLocal8Bit().constData();

    ui->gridStackedWidget->setCurrentWidget(ui->CallPage);
    std::cout << user << std::endl;
    std::cout << pass << std::endl;
    bool tmp = true;
    //if (tmp == true)
    //    ui->WrongLoginText->show();
    if (tmp == true) {
        //ui->LoginWidget->hide();
        //ui->LogedWidget->show();
    }
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
