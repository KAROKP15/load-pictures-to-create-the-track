#ifndef SELECT_H
#define SELECT_H

#include <QWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QPainter>
#include <QWebEngineView>
#include <QWebChannel>
#include <QDir>
#include <QFileDialog>
#include "bridge.h"

namespace Ui {
class select;
}

class select : public QWidget
{
    Q_OBJECT

public:
    explicit select(QWidget *parent = nullptr);
        virtual void paintEvent(QPaintEvent *event);
    QSqlDatabase sqlconn;//数据库的连接对象
    QDialog *userDialog;//用户不存在dialog
    QDialog *queryDialog;
    ~select();

protected slots:
    void userquery();//按用户查询
    void timequery();//按时间查询
    //void noexist();//用户不存在
    //void trip();//行程
    //void queryfail();//查询失败

protected slots:
    //void finished(bool b);
    //void getInfo();

private:
    Ui::select *ui;

};

#endif // SELECT_H
