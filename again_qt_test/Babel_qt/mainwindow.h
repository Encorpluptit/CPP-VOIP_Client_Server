#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
