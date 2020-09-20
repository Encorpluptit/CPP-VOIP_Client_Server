#include "mainwindow.hpp"
#include "UserResponse.hpp"
#include "./ui_mainwindow.h"

#include <QtDebug>
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), client(new ClientCore)
    , ui(new Ui::MainWindow)
{
    QtSocket *sock = new QtSocket();
    serv = sock;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readyRead()
{
    std::cout << "COUCOU" << std::endl;
}

void MainWindow::adress(char **av)
{
    client->initSocket(av);
    serv->Binding(8000);
    connect(serv->socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void MainWindow::on_ConnectionButton_clicked()
{
    /*
    qDebug()<< ui->UserLine->text();
    qDebug()<< ui->PassLine->text();
    */
    std::string user = ui->UserLine->text().toLocal8Bit().constData();
    std::string pass = ui->PassLine->text().toLocal8Bit().constData();

    std::cout << user << std::endl;
    std::cout << pass << std::endl;
    auto response = BabelNetwork::UserResponse::NewLoginRequest(user, pass);
    client->_socket->sendResponse(response);
}
