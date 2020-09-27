#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <QMainWindow>
#include "ClientCore.hpp"
#include "IGraphics.hpp"

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

using namespace BabelClient;

class MainWindow : public QMainWindow, public IGraphics
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, ISocket *core);
    ~MainWindow() override;
    int init() {
        return (0);
    }
    void showApp() {
        show();
    }

private slots:
    void on_ConnectionButton_clicked();
    void on_DisconnectButton_clicked();
    void coucou(const QString &name);
    void on_ManageFriendButton_clicked();
    void on_AddFriendButton_clicked();
    void on_DeleteFriendButton_clicked();
    void on_BackButton_clicked();
    void on_BackButtonRegister_clicked();
    void on_ToRegisterButton_clicked();
    void on_RegisterButton_clicked();

private:
    Ui::MainWindow *ui;
    ISocket *socket;
};
#endif // MAINWINDOW_H
