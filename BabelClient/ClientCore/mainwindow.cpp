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

    QPushButton *button1 = new QPushButton("Contact 1", ui->ContactArea);
    QPushButton *button2 = new QPushButton("Contact 2", ui->ContactArea);
    QPushButton *button3 = new QPushButton("Contact 3", ui->ContactArea);
    QPushButton *button4 = new QPushButton("Contact 4", ui->ContactArea);
    QPushButton *button5 = new QPushButton("Contact 5", ui->ContactArea);
    QPushButton *button6 = new QPushButton("Contact 6", ui->ContactArea);
    QPushButton *button7 = new QPushButton("Contact 7", ui->ContactArea);
    QPushButton *button8 = new QPushButton("Contact 8", ui->ContactArea);
    QPushButton *button9 = new QPushButton("Contact 9", ui->ContactArea);


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
    butts = ui->ContactArea->findChildren<QPushButton *>();
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
    std::cout << "BACK BUTTON" << std::endl;
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
    std::string friendLogin = ui->SearchFriendLine->text().toLocal8Bit().constData();

    auto response = BabelNetwork::FriendResponse::DeleteFriendRequest(login, friendLogin);
    client.getTcp()->sendResponse(response);
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
    client.getTcp()->sendResponse(response);
}

void MainWindow::on_DeleteAccount_clicked()
{
    //std::string user = ui->UserRegisterLine->text().toLocal8Bit().constData();

    //auto response = BabelNetwork::UserResponse::AccountDeletionRequest(user)
    std::cout << "Delete Account clicked" << std::endl;
}

void MainWindow::on_RefuseRequestButton_clicked()
{
    if (friendRequest != nullptr) {
        auto response = BabelNetwork::FriendResponse::FriendRequestDeclined(friendRequest);
        client.getTcp()->sendResponse(response);
    }
    friendRequest = nullptr;
    ui->gridStackedWidget->setCurrentWidget(ui->CallPage);
}

void MainWindow::on_AcceptRequestButton_clicked()
{
        if (friendRequest != nullptr) {
        auto response = BabelNetwork::FriendResponse::FriendRequestAccepted(login, friendRequest->getFriendLogin());
        client.getTcp()->sendResponse(response);
    }
    friendRequest = nullptr;
    ui->gridStackedWidget->setCurrentWidget(ui->CallPage);
}

void MainWindow::on_AcceptCallButton_clicked()
{
    called = true;
    auto response = BabelNetwork::CallResponse::AcceptCall(callInfo->getReceiver, callInfo->getSender());
    client.getTcp()->sendResponse(response);
    // SE CONNECTER A LA SOCKET
}

void MainWindow::on_RefuseCallButton_clicked()
{
    called = false;
    auto response = BabelNetwork::CallResponse::RefusedCall(callInfo->getReceiver, callInfo->getSender());
    client.getTcp()->sendResponse(response);
    callInfo = nullptr;
}

void MainWindow::on_HangOutButton_clicked()
{
    called = false;
    auto response = BabelNetwork::CallResponse::LeftCall(callInfo->getReceiver, callInfo->getSender());
    client.getTcp()->sendResponse(response);
    callInfo = nullptr;
    // DECONNECTER LA SOCKET
}

void MainWindow::on_CallButton_clicked()
{
    if (called != true) {
        called = true;
        auto response = BabelNetwork::CallResponse::CallRequest(login, login /* A REMPLACER PAR LE LOGIN DU BOUTON CONTACT ENCLENCHE */)
        client.getTcp()->sendResponse(response);
    }
    //else display already in a call
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
    //DISPLAY COMPTE CREE
    std::cout << "ACCOUNT CREATE" << std::endl;
    (void) response;
}

void MainWindow::AccountDelete(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    //DISPLAY COMPTE SUPPRIME
    (void) response;
}

void MainWindow::UnknowUserError(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    //THROW ERROR
    (void) response;
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
    //DISPLAY LOGIN ALREADY TAKEN
    std::cout << "LOGIN ALREADY TAKEN" << std::endl;
    (void) response;
}

void MainWindow::AlreadyLoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    //DISPLAY ALREADY LOGGED IN
    std::cout << "ALREADY LOGGED IN" << std::endl;
    (void) response;
    //FRONT ARTHUR
}

void MainWindow::CallStarted(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    called = true;
    (void) response;
    // OUVRIR SOCKET + SE CONNECTER + CHANGER FRONT
}

void MainWindow::CallLeft(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    called = false;
    (void) response;
    // FERMER SOCKET + CHANGER FRONT
}

void MainWindow::IncomingCall(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    ui->gridStackedWidget->setCurrentWidget(ui->IncomingCall);
    (void) response;
}

void MainWindow::CallAccepted(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    called = true;
    (void) response;
    // COMMENCER TIMER QUDPSOCKET
}

void MainWindow::CallRefused(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    called = false;
    (void) response;
    //FERMER SOCKET + CHANGER FRONT
}

void MainWindow::UserDisconnected(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    (void) response;
    //FERMER SOCKET + CHANGER FRONT
}

void MainWindow::AddFriend(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    friendList.push_back(response->getFriendLogin());
    for (size_t i = 0; i < friendList.size(); i++) {
        butts[i]->setText(response->getFriendLogin());
        if (i >= butts.size())
            butts.push_back(new QPushButton(response->getFriendLogin(), ui->ContactArea);)
    }
}

void MainWindow::FriendRequest(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    ui->gridStackedWidget->setCurrentWidget(ui->FriendRequest);
    friendRequest = response;
}

void MainWindow::UnknowUser(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    //THROW ERROR
    (void) response;
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

    std::cout << "CODE" << std::endl;
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
    std::cout << response->getCode() << std::endl;
    dispatch_ptr[response->getResponseType()](this, response);
}

void MainWindow::UpdateClient()
{
    std::shared_ptr<BabelNetwork::AResponse> response = nullptr;

    while ((response = client.getTcp()->readResponse()) != nullptr)
        checkTypeResponse(response);
}