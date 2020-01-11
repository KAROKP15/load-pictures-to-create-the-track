#include "select.h"
#include "ui_select.h"

select::select(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::select)
{
    ui->setupUi(this);
    QString filepath="file:///Users/karo/tong7you/baidumap.html";
    ui->webview->page()->load(QUrl(filepath));
    ui->webview_2->page()->load(QUrl(filepath));
    connect(ui->userQBtn, &QPushButton::clicked, this, &select::userquery);
    connect(ui->timeBtn, &QPushButton::clicked, this, &select::timequery);
}

select::~select()
{
    delete ui;
}


void select::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap img(tr(":/tong7you.png"));
    img=img.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, img);
}

void select::userquery(){
    //连接数据库,查询user表中有没有该用户
    sqlconn = QSqlDatabase::addDatabase("QPSQL");
    sqlconn.setHostName("127.0.0.1");
    sqlconn.setPort(5432);
    sqlconn.setUserName("postroot");
    sqlconn.setPassword("samantha");
    sqlconn.setDatabaseName("tongyou");

    //打开连接
    if(!sqlconn.open()){
        qDebug()<<sqlconn.lastError();
        qDebug()<<"连接数据库失败";
    }
    else
        qDebug()<<"连接数据库成功";

    //执行查询
    QString str1=QString("select * from trip where userid='%0';").arg(ui->userQName->text());
    QSqlQuery sqlQuery(str1);
    int num=ui->userQNum->text().toUInt();
    while(num!=0){
        sqlQuery.next();
        num--;
    }
    int tripId=sqlQuery.value(0).toInt();

    QString str2=QString("select count(*) from picture where tripid='%0';").arg(tripId);
    QSqlQuery sqlQuery2(str2);
    sqlQuery2.next();
    int picnum=sqlQuery2.value(0).toInt();
    qDebug()<<picnum;

    QString str3=QString("select * from picture where tripid='%0';").arg(tripId);
    QSqlQuery sqlQuery3(str3);
    while(picnum!=0){
        sqlQuery3.next();
        QString cmd=QString("theLocation(%0, %1)")
            .arg(sqlQuery3.value(3).toDouble())
            .arg(sqlQuery3.value(2).toDouble());
        ui->webview->page()->runJavaScript(cmd);
        picnum--;
    }
    QString cmd=QString("drawLine()");
    ui->webview->page()->runJavaScript(cmd);
}

void select::timequery(){
    //连接数据库,查询picture表中的时间信息
    sqlconn = QSqlDatabase::addDatabase("QPSQL");
    sqlconn.setHostName("127.0.0.1");
    sqlconn.setPort(5432);
    sqlconn.setUserName("postroot");
    sqlconn.setPassword("samantha");
    sqlconn.setDatabaseName("tongyou");

    //打开连接
    if(!sqlconn.open()){
        qDebug()<<sqlconn.lastError();
        qDebug()<<"连接数据库失败";
    }
    else
        qDebug()<<"连接数据库成功";

    QString str0=QString("select count(*) from picture where shootingdate='%1';").arg(ui->timeEdit->text());
    QSqlQuery query0(str0);
    query0.next();
    int num=query0.value(0).toInt();

    QString str=QString("select * from picture where shootingdate='%1';").arg(ui->timeEdit->text());
    QSqlQuery query(str);
    while(num!=0){
        query.next();
        QString cmd=QString("theLocation(%0, %1)")
            .arg(query.value(3).toDouble())
            .arg(query.value(2).toDouble());
        ui->webview_2->page()->runJavaScript(cmd);
        num--;
    }
    QString cmd=QString("drawLine()");
    ui->webview_2->page()->runJavaScript(cmd);
}
