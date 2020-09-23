#ifndef CONTACTLIST_HPP
#define CONTACTLIST_HPP

#include <QPushButton>
#include <QWidget>

class ContactList : public QWidget
{
    Q_OBJECT
public:
    explicit ContactList(QWidget *parent = nullptr);
    ~ContactList();

private:
    QList<QPushButton *> butts;
    QString _buttonName;

private slots:
    ContactList::coucou();

};

#endif // CONTACTLIST_HPP
