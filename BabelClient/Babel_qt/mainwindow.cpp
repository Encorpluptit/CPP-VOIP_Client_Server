#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QtDebug>
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ConnectionButton_clicked()
{
    /*qDebug()<< ui->IpLine->text();
    qDebug()<< ui->PortLine->text();
    qDebug()<< ui->UserLine->text();
    qDebug()<< ui->PassLine->text();
    */
    std::string ip = ui->IpLine->text().toLocal8Bit().constData();
    std::string port = ui->PortLine->text().toLocal8Bit().constData();
    std::string user = ui->UserLine->text().toLocal8Bit().constData();
    std::string pass = ui->PassLine->text().toLocal8Bit().constData();

    std::cout << ip << std::endl;
    std::cout << port << std::endl;
    std::cout << user << std::endl;
    std::cout << pass << std::endl;
}
