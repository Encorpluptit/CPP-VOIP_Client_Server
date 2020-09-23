#include "contactlist.hpp"
#include "./ui_mainwindow.h"

#include <QDebug>

ContactList::ContactList(QWidget *parent) : QWidget(parent)
{
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

    for (auto &button : butts) {
        _buttonName = button->text();
        connect(button, SIGNAL(clicked()), this, SLOT(coucou()));
    }
}

void ContactList::coucou()
{
    ui->ContactName->setMarkdown(_buttonName);
    std::cout << "coucou fonction" << std::endl;
}

ContactList::~ContactList() {}
