#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPainter>
#include <QApplication>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    virtual void paintEvent(QPaintEvent *event);
    QSqlDatabase sqlconn;

protected slots:
    void logBtnClicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
