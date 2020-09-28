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

MainWindow::MainWindow(QWidget *parent, NetworkClientSocket &network) : QMainWindow(parent), ui(new Ui::MainWindow), client(network)
{
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

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateClient()));
    timer->start(100);
    logged = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*          EVENT FRONT         */

void MainWindow::coucou(const QString &name)
{
    ui->ContactName->setMarkdown(name);
}

void MainWindow::on_ConnectionButton_clicked()
{
    std::string user = ui->UserLine->text().toLocal8Bit().constData();
    std::string pass = ui->PassLine->text().toLocal8Bit().constData();

    auto response = BabelNetwork::UserResponse::NewLoginRequest(user, pass);
    client.getTcp()->sendResponse(response);
}

void MainWindow::on_DisconnectButton_clicked()
{
    auto response = BabelNetwork::UserResponse::LogoutRequest(login);
    ui->gridStackedWidget->setCurrentWidget(ui->LoginWidget);
    client.getTcp()->sendResponse(response);
}

void MainWindow::on_AddFriendButton_clicked()
{
    std::string friendLogin = ui->SearchFriendLine->text().toLocal8Bit().constData();

    auto response = BabelNetwork::FriendResponse::NewFriendRequest(login, friendLogin);
    client.getTcp()->sendResponse(response);
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
    std::cout << "BACK FRIEND" << std::endl;
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
    client.getTcp()->sendResponse(response);
}






void MainWindow::LoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    ui->gridStackedWidget->setCurrentWidget(ui->CallPage);
    ui->WrongLoginText->hide();
    std::cout << "LOGGED IN" << std::endl;
    login = response->getLogin();
    logged = true;
    (void) response;
}

void MainWindow::LoggedOut(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    logged = false;
    (void) response;
    //FRONT ARTHUR;
}

void MainWindow::AccountCreate(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    std::cout << "ACCOUNT CREATE" << std::endl;
    (void) response;
}

void MainWindow::AccountDelete(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR;
}

void MainWindow::UnknowUserError(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    (void) response;
    //FRONT ARTHUR;
}

void MainWindow::WrongLogin(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    ui->WrongLoginText->show();
    std::cout << "WRONG LOGIN" << std::endl;
    (void) response;
}

void MainWindow::WrongPassword(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    ui->WrongLoginText->show(); // METTRE WRONG PASSWORD
    std::cout << "WRONG PASSWORD" << std::endl;
    (void) response;
}

void MainWindow::LoginAlreadyTaken(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    std::cout << "LOGIN ALREADY TAKEN" << std::endl;
    (void) response;
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
    std::shared_ptr<BabelNetwork::MessageResponse> ptr = std::dynamic_pointer_cast<BabelNetwork::MessageResponse>(response);
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

void MainWindow::UpdateClient()
{
    std::shared_ptr<BabelNetwork::AResponse> response = nullptr;

    while ((response = client.getTcp()->readResponse()) != nullptr)
        checkTypeResponse(response);
}