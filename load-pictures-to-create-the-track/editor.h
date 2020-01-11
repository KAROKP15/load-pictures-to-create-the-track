#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QWebEngineView>
#include <QWebChannel>
#include <QDir>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include "bridge.h"
#include "exif.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    virtual void paintEvent(QPaintEvent *event);

    //功能一
    QWebEngineView *m_view;//加载HTML
    QWebChannel *channel;//实现数据交互
    QSqlDatabase sqlconn;
    int photonum=0;
    void getExifInfo();

signals:
    //void sendMsg();

protected slots:
    void btnClick();
    void finishBtnClick();
    void fpBtnClick();
    void ftmBtnClick();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
