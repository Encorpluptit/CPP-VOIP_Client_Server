#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <string>
#include <ClientCore.hpp>
#include <QMainWindow>

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
    std::vector<std::string> getLoginInfo() const;

private slots:
    void on_ConnectionButton_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<std::string> _loginInfo;
    ClientCore *_client;
};
#endif // MAINWINDOW_H
