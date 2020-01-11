#ifndef BRIDGE_H
#define BRIDGE_H

#include <QObject>
#include <QDebug>

//创建对象供JS调用，JS直接调用bridge文件中的函数

class bridge : public QObject
{
    Q_OBJECT
public:
    explicit bridge(QObject *parent = nullptr);

signals:
    void sigYourName(const QString &name);
public slots:
    void getYourName();
    void getCoordinate(QString lon, QString lat);

};

#endif // BRIDGE_H
