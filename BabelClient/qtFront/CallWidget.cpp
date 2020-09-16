#include "CallWidget.hpp"
#include "./ui_callwidget.h"

CallWidget::CallWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CallWidget)
{
    ui->setupUi(this);
}

CallWidget::~CallWidget()
{
    delete ui;
}

