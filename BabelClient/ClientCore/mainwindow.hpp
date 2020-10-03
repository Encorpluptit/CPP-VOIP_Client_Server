#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QSignalMapper>
#include "NetworkClientSocket.hpp"
#include "UserResponse.hpp"
#include "CallResponse.hpp"
#include "FriendResponse.hpp"
#include "MessageResponse.hpp"

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent, NetworkClientSocket &client);
        ~MainWindow() override;

    private slots:
    //LOGIN
        void on_ConnectionButton_clicked();
        void on_DeleteAccount_clicked();
        void on_ToRegisterButton_clicked();
    //REGISTER PAGE
        void on_RegisterButton_clicked();
        void on_BackButtonRegister_clicked();
    //CALL PAGE
        void on_CallButton_clicked();
        void on_HangOutButton_clicked();
        void on_DisconnectButton_clicked();
        void on_ManageFriendButton_clicked();
    //MANAGE FRIEND PAGE
        void on_AddFriendButton_clicked();
        void on_DeleteFriendButton_clicked();
        void on_BackButton_clicked();
    //INCOMING CALL
        void on_AcceptCallButton_clicked();
        void on_RefuseCallButton_clicked();
    //FRIEND REQUEST
        void on_AcceptRequestButton_clicked();
        void on_RefuseRequestButton_clicked();
        void UpdateClient();
        void coucou(const QString &name);

    public:
        void checkTypeResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);
        void doUserResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);
        void doCallResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);
        void doFriendResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);
        void doMessageResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);
        void doUnknowTypeResponse(const std::shared_ptr<BabelNetwork::AResponse> &response);

        void LoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response);
        void LoggedOut(const std::shared_ptr<BabelNetwork::UserResponse> &response);
        void AccountCreate(const std::shared_ptr<BabelNetwork::UserResponse> &response);
        void AccountDelete(const std::shared_ptr<BabelNetwork::UserResponse> &response);
        void UnknowUserError(const std::shared_ptr<BabelNetwork::UserResponse> &response);
        void WrongLogin(const std::shared_ptr<BabelNetwork::UserResponse> &response);
        void WrongPassword(const std::shared_ptr<BabelNetwork::UserResponse> &response);
        void LoginAlreadyTaken(const std::shared_ptr<BabelNetwork::UserResponse> &response);
        void AlreadyLoggedIn(const std::shared_ptr<BabelNetwork::UserResponse> &response);

        void CallStarted(const std::shared_ptr<BabelNetwork::CallResponse> &response);
        void CallLeft(const std::shared_ptr<BabelNetwork::CallResponse> &response);
        void IncomingCall(const std::shared_ptr<BabelNetwork::CallResponse> &response);
        void CallAccepted(const std::shared_ptr<BabelNetwork::CallResponse> &response);
        void CallRefused(const std::shared_ptr<BabelNetwork::CallResponse> &response);
        void UserDisconnected(const std::shared_ptr<BabelNetwork::CallResponse> &response);

        void AddFriend(const std::shared_ptr<BabelNetwork::FriendResponse> &response);
        void FriendRequest(const std::shared_ptr<BabelNetwork::FriendResponse> &response);
        void UnknowUser(const std::shared_ptr<BabelNetwork::FriendResponse> &response);

        void SendMessageOk(const std::shared_ptr<BabelNetwork::MessageResponse> &response);
        void ReceiveMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response);
        void UnknowUserMessage(const std::shared_ptr<BabelNetwork::MessageResponse> &response);

    private:
        Ui::MainWindow *ui;
        NetworkClientSocket &client;
        QTimer *timer;
        std::string login;
        bool logged;
        bool called;
        std::shared_ptr<BabelNetwork::FriendResponse> friendRequest;
        std::shared_ptr<BabelNetwork::CallResponse> callInfo;
        std::vector<std::string> friendList;
        QList<QPushButton *> butts;
        QSignalMapper *mapper;

    private:
        std::vector<std::function<void(MainWindow*, const std::shared_ptr<BabelNetwork::AResponse> &)>> dispatch_ptr = {&MainWindow::doUnknowTypeResponse, &MainWindow::doUserResponse, &MainWindow::doCallResponse, &MainWindow::doFriendResponse, &MainWindow::doMessageResponse};
        std::vector<std::function<void(MainWindow*, const std::shared_ptr<BabelNetwork::UserResponse> &)>> user_ptr = {&MainWindow::LoggedIn, &MainWindow::LoggedOut, &MainWindow::AccountCreate, &MainWindow::AccountDelete, &MainWindow::WrongLogin, &MainWindow::WrongPassword, &MainWindow::LoginAlreadyTaken, &MainWindow::AlreadyLoggedIn, &MainWindow::UnknowUserError};
        std::vector<std::function<void(MainWindow*, const std::shared_ptr<BabelNetwork::CallResponse> &)>> call_ptr = {&MainWindow::CallStarted, &MainWindow::CallLeft, &MainWindow::IncomingCall, &MainWindow::CallAccepted, &MainWindow::CallRefused, &MainWindow::UserDisconnected};
        std::vector<std::function<void(MainWindow*, const std::shared_ptr<BabelNetwork::FriendResponse> &)>> friend_ptr = {&MainWindow::AddFriend, &MainWindow::FriendRequest, &MainWindow::UnknowUser};
        std::vector<std::function<void(MainWindow*, const std::shared_ptr<BabelNetwork::MessageResponse> &)>> message_ptr = {&MainWindow::SendMessageOk, &MainWindow::ReceiveMessage, &MainWindow::UnknowUserMessage};
        std::vector<int> userCodeIdx = {BabelNetwork::UserResponse::LoggedIn, BabelNetwork::UserResponse::LoggedOut, BabelNetwork::UserResponse::AccountCreated, BabelNetwork::UserResponse::AccountDeleted, BabelNetwork::UserResponse::WrongLogin, BabelNetwork::UserResponse::WrongPassword, BabelNetwork::UserResponse::LoginAlreadyTaken, BabelNetwork::UserResponse::AlreadyLoggedIn, BabelNetwork::UserResponse::UnknownUserError};
        std::vector<int> callCodeIdx = {BabelNetwork::CallResponse::CallStarted, BabelNetwork::CallResponse::CallLeft,
            BabelNetwork::CallResponse::IncomingCall, BabelNetwork::CallResponse::CallAccepted,
            BabelNetwork::CallResponse::CallRefused, BabelNetwork::CallResponse::UserDisconnected};
    std::vector<int> friendCodeIdx = {BabelNetwork::FriendResponse::FriendAdded,
        BabelNetwork::FriendResponse::NewFriendshipRequested, BabelNetwork::FriendResponse::UnknownUser};
    std::vector<int> messageCodeIdx = {BabelNetwork::MessageResponse::SendMessageOk,
        BabelNetwork::MessageResponse::ReceiveMessage, BabelNetwork::MessageResponse::UnknownUser};
};
#endif // MAINWINDOW_H
