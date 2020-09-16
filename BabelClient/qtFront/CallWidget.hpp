#ifndef CALLWIDGET_HPP
#define CALLWIDGET_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CallWidget; }
QT_END_NAMESPACE

class CallWidget : public QWidget
{
    Q_OBJECT

public:
    CallWidget(QWidget *parent = nullptr);
    ~CallWidget();

private:
    Ui::CallWidget *ui;
};
#endif // CALLWIDGET_HPP
