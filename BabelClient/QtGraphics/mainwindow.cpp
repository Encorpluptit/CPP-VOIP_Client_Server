#include "mainwindow.hpp"
#include "UserResponse.hpp"
#include "./ui_mainwindow.h"

#include <QtDebug>
#include <QAbstractButton>
#include <QSignalMapper>
#include <QObject>
#include <string>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), client(new ClientCore)
    , ui(new Ui::MainWindow)
{
    serv = new MyTcpSocket();
    connect(serv->socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
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

}

MainWindow::~MainWindow()
{
    delete ui;
}

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

    ui->gridStackedWidget->setCurrentWidget(ui->CallPage);
    bool tmp = true;
    //if (tmp == true)
    //    ui->WrongLoginText->show();
    if (tmp == true) {
        //ui->LoginWidget->hide();
        //ui->LogedWidget->show();
    }
    auto response = BabelNetwork::UserResponse::NewLoginRequest(user, pass);
    serv->writeData(response);
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
    std::cout << "COUCOU ENCULE PD" << std::endl;
}







void MainWindow::LoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    std::cout << "LOGGED IN" << std::endl;
    (void)response;
}

void MainWindow::LoggedOut(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
}

void MainWindow::AccountCreate(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    std::cout << "ACCOUNT CREATE" << std::endl;
    (void)response;
}

void MainWindow::AccountDelete(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void)response;
}

void MainWindow::UnknowUserError(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR;
}

void MainWindow::WrongLogin(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    std::cout << "WRONG LOGIN" << std::endl;
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::WrongPassword(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::LoginAlreadyTaken(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::AlreadyLoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::CallStarted(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::CallLeft(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::IncomingCall(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::CallAccepted(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::CallRefused(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::UserDisconnected(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::AddFriend(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::FriendRequest(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::UnknowUser(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::SendMessageOk(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::ReceiveMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::UnknowUserMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::doUserResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    std::shared_ptr<BabelNetwork::UserResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::UserResponse>(response);
    int code = response->getCode();

    for (size_t i = 0; i < userCodeIdx.size(); i++)
        if (userCodeIdx[i] == code)
            user_ptr[i](this, ptr);
}

void MainWindow::doCallResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    std::shared_ptr<BabelNetwork::CallResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::CallResponse>(response);
    int code = response->getCode();

    for (size_t i = 0; i < callCodeIdx.size(); i++)
        if (callCodeIdx[i] == code)
            call_ptr[i](this, ptr);
}

void MainWindow::doFriendResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    std::shared_ptr<BabelNetwork::FriendResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::FriendResponse>(
        response);
    int code = response->getCode();

    for (size_t i = 0; i < friendCodeIdx.size(); i++)
        if (friendCodeIdx[i] == code)
            friend_ptr[i](this, ptr);
}

void MainWindow::doMessageResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    std::shared_ptr<BabelNetwork::MessageResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(
        response);
    int code = response->getCode();

    for (size_t i = 0; i < messageCodeIdx.size(); i++)
        if (messageCodeIdx[i] == code)
            message_ptr[i](this, ptr);
}

void MainWindow::doUnknowTypeResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    printf("code : %d\n", response->getCode());
    //throw (BabelErrors::BabelError("Unknow Response Type"));
}

void MainWindow::checkTypeResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    dispatch_ptr[response->getResponseType()](this, response);
}

void MainWindow::readyRead()
{
    std::shared_ptr<BabelNetwork::AResponse> response = serv->readResponse();
    checkTypeResponse(response);
}

void MainWindow::adress(const std::string &ip, const uint16_t port) const
{
    serv->doConnect(ip, port);
}