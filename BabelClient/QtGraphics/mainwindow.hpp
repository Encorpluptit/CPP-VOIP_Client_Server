#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ClientCore.hpp"
#include "QtSocket.hpp"

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

using namespace BabelClient;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void adress(const std::string &ip, uint16_t port) const;
    ClientCore *client;
    MyTcpSocket *serv;

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


private slots:
    void on_ConnectionButton_clicked();
    void readyRead();

private:
    Ui::MainWindow *ui;
    std::vector<std::function<void(MainWindow*, std::shared_ptr<BabelNetwork::AResponse>)>> dispatch_ptr = {&MainWindow::doUnknowTypeResponse, &MainWindow::doUserResponse, &MainWindow::doCallResponse, &MainWindow::doFriendResponse, &MainWindow::doMessageResponse};
    std::vector<std::function<void(MainWindow*, std::shared_ptr<BabelNetwork::UserResponse>)>> user_ptr = {&MainWindow::LoggedIn, &MainWindow::LoggedOut, &MainWindow::AccountCreate, &MainWindow::AccountDelete, &MainWindow::WrongLogin, &MainWindow::WrongPassword, &MainWindow::LoginAlreadyTaken, &MainWindow::AlreadyLoggedIn, &MainWindow::UnknowUserError};
    std::vector<std::function<void(MainWindow*, std::shared_ptr<BabelNetwork::CallResponse>)>> call_ptr = {&MainWindow::CallStarted, &MainWindow::CallLeft, &MainWindow::IncomingCall, &MainWindow::CallAccepted, &MainWindow::CallRefused, &MainWindow::IncomingCall};
    std::vector<std::function<void(MainWindow*, std::shared_ptr<BabelNetwork::FriendResponse>)>> friend_ptr = {&MainWindow::AddFriend, &MainWindow::FriendRequest, &MainWindow::UnknowUser};
    std::vector<std::function<void(MainWindow*, std::shared_ptr<BabelNetwork::MessageResponse>)>> message_ptr = {&MainWindow::SendMessageOk, &MainWindow::ReceiveMessage, &MainWindow::UnknowUserMessage};
    std::vector<int> userCodeIdx = {100, 102, 110, 112, 171, 172, 173, 174, 170};
    std::vector<int> callCodeIdx = {200, 202, 204, 205, 270, 271};
    std::vector<int> friendCodeIdx = {301, 302, 350};
    std::vector<int> messageCodeIdx = {402, 403, 450};    
};
#endif // MAINWINDOW_H
