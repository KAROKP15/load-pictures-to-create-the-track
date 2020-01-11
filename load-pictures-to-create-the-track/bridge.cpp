 #include "bridge.h"


bridge::bridge(QObject *parent) : QObject(parent)
{

}


void bridge::getYourName()
{
    emit sigYourName("hello, world!");
}


void bridge::getCoordinate(QString lon, QString lat){
    //获取鼠标点击位置的地图坐标
    qDebug()<<lon<<lat;
}
