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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void adress(char **av);
    ClientCore *client;
    QtSocket *serv;


private slots:
    void on_ConnectionButton_clicked();
    void readyRead();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
