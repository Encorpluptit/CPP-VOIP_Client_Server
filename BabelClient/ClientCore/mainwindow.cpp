#include "mainwindow.hpp"
#include "UserResponse.hpp"
#include "./ui_mainwindow.h"
#include "Debug.hpp"
#include "BabelError.hpp"

#include <QtDebug>
#include <QAbstractButton>
#include <QSignalMapper>
#include <QObject>
#include <string>
#include <iostream>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent, NetworkClientSocket &network) : QMainWindow(parent), ui(new Ui::MainWindow),
                                                                        client(network)
{
    audio = std::make_shared<PortAudio>();
    codec = std::make_shared<Opus>();
    ui->setupUi(this);

    ui->VLayout = new QVBoxLayout(ui->ContactArea);

    butts = ui->ContactArea->findChildren<QPushButton *>();

    mapper = new QSignalMapper();

    ui->WrongLoginText->hide();

    timer = new QTimer(this);
    voiceTimer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(UpdateClient()));
    connect(voiceTimer, SIGNAL(timeout()), this, SLOT(ManageVoice()));
    timer->start(100);
    logged = false;
    ui->CantFindText->hide();
    called = false;
    ui->textEdit->hide();
    ui->gridStackedWidget->setCurrentWidget(ui->LoginWidget);
}

MainWindow::~MainWindow()
{
    delete mapper;
    delete timer;
    delete voiceTimer;
    delete ui;
}


void MainWindow::coucou(const QString &name)
{
    actualFriend = name.toLocal8Bit().constData();
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
    if (called == true && callInfo != nullptr) {
        auto CallResponse = BabelNetwork::CallResponse::EndCallRequest(callInfo);
        client.getTcp()->sendResponse(CallResponse);
        UserDisconnected(callInfo);
    }
    auto response = BabelNetwork::UserResponse::LogoutRequest(login);
    ui->gridStackedWidget->setCurrentWidget(ui->LoginWidget);
    client.getTcp()->sendResponse(response);
}

void MainWindow::on_AddFriendButton_clicked()
{
    std::string friendLogin = ui->SearchFriendLine->text().toLocal8Bit().constData();

    auto response = BabelNetwork::FriendResponse::RequestFriend(login, friendLogin);
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

void MainWindow::on_DeleteAccountButton_clicked()
{
    auto response = BabelNetwork::UserResponse::AccountDeletionRequest(login);
    client.getTcp()->sendResponse(response);
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
    client.setIpPort(5000 + std::rand() % 15000);
    client.getUdp()->doConnect(client.getMyUdpIp(), client.getMyUdpPort());
    auto response = BabelNetwork::CallResponse::AcceptCall(callInfo, client.getMyUdpIp(), client.getMyUdpPort());
    client.getTcp()->sendResponse(response);
    ui->gridStackedWidget->setCurrentWidget(ui->CallPage);
}

void MainWindow::on_RefuseCallButton_clicked()
{
    called = false;
    auto response = BabelNetwork::CallResponse::RefusedCall(callInfo);
    client.getTcp()->sendResponse(response);
    callInfo = nullptr;
    ui->gridStackedWidget->setCurrentWidget(ui->CallPage);
}

void MainWindow::on_HangOutButton_clicked()
{
    called = false;
    auto response = BabelNetwork::CallResponse::EndCallRequest(callInfo);
    client.getTcp()->sendResponse(response);
    callInfo = nullptr;
    voiceTimer->stop();
    audio->stop_audio();
    client.getUdp()->disconnect();
}

void MainWindow::on_CallButton_clicked()
{
    if (called != true && actualFriend != login) {
        client.setIpPort(5000 + std::rand() % 15000);
        std::cout << "MY UDP PORT : " << client.getMyUdpPort() << std::endl;
        called = true;
        client.getUdp()->doConnect(client.getMyUdpIp(), client.getMyUdpPort());
        auto response = BabelNetwork::CallResponse::CallRequest(login, actualFriend, client.getMyUdpIp(),
            std::to_string(client.getMyUdpPort()));
        client.getTcp()->sendResponse(response);
    }
}

void MainWindow::on_sendMessage_clicked()
{
    std::string message;

    if (actualFriend != login) {
        message = ui->NewMessages->text().toLocal8Bit().constData();
        std::cout << "MESSAGE : " << message << std::endl;
        auto response = BabelNetwork::MessageResponse::RequestMessageSend(login, actualFriend, message);
        client.getTcp()->sendResponse(response);
    }
}

void MainWindow::LoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    actualFriend = login;
    ui->gridStackedWidget->setCurrentWidget(ui->CallPage);
    ui->WrongLoginText->hide();
    std::cout << "LOGGED IN" << std::endl;
    login = response->getLogin();
    logged = true;
    ui->LoginNameEdit->setText(login.c_str());
}

void MainWindow::LoggedOut(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    if (called == true) {
        voiceTimer->stop();
        audio->stop_audio();
        called = false;
        client.getUdp()->disconnect();
    }
    logged = false;
    (void) response;
    friendList.clear();
    callInfo = nullptr;
    friendRequest = nullptr;
    ui->gridStackedWidget->setCurrentWidget(ui->LoginWidget);
}

void MainWindow::AccountCreate(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    ui->textEdit->setText("Account Create");
    ui->textEdit->show();
    (void) response;
}

void MainWindow::AccountDelete(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    if (called) {
        voiceTimer->stop();
        audio->stop_audio();
        called = false;
        client.getUdp()->disconnect();
    }
    logged = false;
    (void) response;
    friendList.clear();
    callInfo = nullptr;
    friendRequest = nullptr;
    ui->gridStackedWidget->setCurrentWidget(ui->LoginWidget);
}

void MainWindow::UnknowUserError(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    throw (BabelErrors::BabelError("Response code : " + std::to_string(response->getCode())));
}

void MainWindow::WrongLogin(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    ui->WrongLoginText->setText("Wrong Login");
    ui->WrongLoginText->show();
    (void) response;
}

void MainWindow::WrongPassword(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    ui->WrongLoginText->setText("Wrong password");
    ui->WrongLoginText->show();
    (void) response;
}

void MainWindow::LoginAlreadyTaken(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    ui->textEdit->setText("Login already taken");
    ui->textEdit->show();
    (void) response;
}

void MainWindow::AlreadyLoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response)
{
    ui->WrongLoginText->setText("Already logged in");
    ui->WrongLoginText->show();
    (void) response;
}

void MainWindow::CallStarted(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    audio->init_audio();
    called = true;
    callInfo = response;
    voiceTimer->start(1);
}

void MainWindow::CallLeft(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    voiceTimer->stop();
    audio->stop_audio();
    called = false;
    (void) response;
    client.getUdp()->disconnect();
    callInfo = nullptr;
}

void MainWindow::IncomingCall(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    std::string str = "Call from ";
    std::string name = response->getSender();
    std::string result = str + name;
    ui->gridStackedWidget->setCurrentWidget(ui->IncomingCall);
    ui->NameCallText->setText(result.c_str());
    callInfo = response;
}

void MainWindow::CallRefused(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    called = false;
    (void) response;
    client.getUdp()->disconnect();
    callInfo = nullptr;
}

void MainWindow::UserDisconnected(const std::shared_ptr<BabelNetwork::CallResponse> &response)
{
    voiceTimer->stop();
    audio->stop_audio();
    called = false;
    (void) response;
    client.getUdp()->disconnect();
    callInfo = nullptr;
}

void MainWindow::AddFriend(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    QPushButton *button;

    friendList.emplace_back(response->getFriendLogin());
    for (size_t i = 0; i < friendList.size(); i++) {
        if ((int) i >= butts.size()) {
            button = new QPushButton(friendList[i].c_str(), ui->ContactArea);
            ui->VLayout->addWidget(button);
            connect(button, SIGNAL(clicked()), mapper, SLOT(map()));
            mapper->setMapping(button, button->text());
            connect(mapper, SIGNAL(mapped(const QString &)), this, SLOT(coucou(const QString &)));
            button->setText(friendList[i].c_str());
            butts.push_back(button);
        }
    }
}

void MainWindow::DeleteFriend(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    int i = 0;

    for (auto it = friendList.begin(); it != friendList.end(); it++, i++) {
        if (butts[i]->text() == response->getFriendLogin() && butts[i]->isHidden() == false) {
            butts[i]->hide();
            butts.removeAt(i);
            friendList.erase(it);
            break;
        }
    }
}

void MainWindow::FriendRequest(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    std::string str = "Friend request from ";
    std::string name = response->getFriendLogin();
    std::string result = str + name;
    ui->gridStackedWidget->setCurrentWidget(ui->FriendRequest);
    ui->RequestText->setText(result.c_str());
    friendRequest = response;
}

void MainWindow::UnknowUser(const std::shared_ptr<BabelNetwork::FriendResponse> &response)
{
    ui->CantFindText->show();
    (void) response;
}

void MainWindow::SendMessageOk(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    std::string receiver = response->getReceiver();
    std::string data = response->getMessageData();
    std::string message = "Message Send to " + receiver + " : " + data + "\n";
    ui->HistoricMessages->append(message.c_str());
}

void MainWindow::ReceiveMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    std::string sender = response->getSender();
    std::string data = response->getMessageData();
    std::string message = "Message Receive from " + sender + " : " + data + "\n";
    ui->HistoricMessages->append(message.c_str());
}

void MainWindow::UnknowUserMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response)
{
    throw (BabelErrors::BabelError("Response code : " + std::to_string(response->getCode())));
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

    std::cout << response->getDescription() << std::endl;
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
    throw (BabelErrors::BabelError("Response code : " + std::to_string(response->getCode())));
}

void MainWindow::checkTypeResponse(const std::shared_ptr<BabelNetwork::AResponse> &response)
{
    dbg("Request Received: %s", response->describe().c_str());
    dispatch_ptr[response->getResponseType()](this, response);
}

void MainWindow::UpdateClient()
{
    std::shared_ptr<BabelNetwork::AResponse> response = nullptr;

    while ((response = client.getTcp()->readResponse()) != nullptr)
        checkTypeResponse(response);
}

void MainWindow::ManageVoice()
{
    std::vector<uint16_t> send;
    std::vector<uint16_t> receive;

    /*send = audio->getVoice();
    std::cout << send.size() << std::endl;
    if (send.size() != 0)
        send = codec->encode(send);
    if (send.size() != 0)
        receive = codec->decode(send);
    audio->playVoice(receive);
    send.clear();
    receive.clear();*/

    send = audio->getVoice();
    if (!send.empty())
        send = codec->encode(send);
    client.getUdp()->sendVoice(send, callInfo->getIp(), std::stoi(callInfo->getPort()));
    send.clear();
    receive = client.getUdp()->readVoice(callInfo->getIp(), std::stoi(callInfo->getPort()));
    if (!receive.empty()) {
        receive = codec->decode(receive);
        audio->playVoice(receive);
    }
    receive.clear();

    //client.getUdp()->sendData("PTDR", callInfo->getIp(), std::stoi(callInfo->getPort()));
    //client.getUdp()->readData(callInfo->getIp(), std::stoi(callInfo->getPort()));
}