#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ClientCore.hpp"
#include <QMainWindow>
#include "QtSocket.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
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


private slots:
    void on_ConnectionButton_clicked();
    void readyRead();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
