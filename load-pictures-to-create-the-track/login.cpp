#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //设置密码栏输入效果
    ui->pwdEdit->setEchoMode(QLineEdit::Password);
    connect(ui->logBtn, &QPushButton::clicked, this, &login::logBtnClicked);
}

login::~login()
{
    delete ui;
}

void login::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap img(tr(":/tong7you.png"));
    img=img.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, img);
}

void login::logBtnClicked(){
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
    QString str=QString("select count(*) from tyuser where username='%1' and password='%2';").arg(ui->nameEdit->text()).arg(ui->pwdEdit->text());
    QSqlQuery sqlQuery(str);
    sqlQuery.next();
    if(sqlQuery.value(0).toInt()==0)
        ui->tipLbl->setText("用户名或密码错误！");
    else
        ui->tipLbl->setText("登录成功！");
}
