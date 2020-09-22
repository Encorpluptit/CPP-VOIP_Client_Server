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
    serv = new MyTcpSocket();
    connect(serv->socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void)response;
}

void MainWindow::LoggedOut(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
}

void MainWindow::AccountCreate(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
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

void MainWindow::on_ConnectionButton_clicked()
{
    /*
    qDebug()<< ui->UserLine->text();
    qDebug()<< ui->PassLine->text();
    */
    std::string user = ui->UserLine->text().toLocal8Bit().constData();
    std::string pass = ui->PassLine->text().toLocal8Bit().constData();

    auto response = BabelNetwork::UserResponse::NewLoginRequest(user, pass);
    serv->writeData(response);
}
