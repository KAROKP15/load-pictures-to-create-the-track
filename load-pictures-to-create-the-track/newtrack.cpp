#include "newtrack.h"
#include "ui_newtrack.h"

newTrack::newTrack(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newTrack)
{
    ui->setupUi(this);
    //导入地图API
    QString filepath2="file:///Users/karo/tong7you/carmap.html";
    ui->walkview->page()->load(QUrl(filepath2));
    ui->carview->page()->load(QUrl(filepath2));

    //创建通道对象和JS交互
    channel=new QWebChannel(this);
    bridge *mybridge=new bridge();

    //注册对象，注册名与JS函数用到的一致
    channel->registerObject("bridge_name", (QObject*)mybridge);
    ui->walkview->page()->setWebChannel(channel);


    //根据图片的GPS信息在地图上完成定位
    connect(ui->swBtn, &QPushButton::clicked, this, &newTrack::swBtnClick);
    connect(ui->scBtn, &QPushButton::clicked, this, &newTrack::scBtnClick);
}

newTrack::~newTrack()
{
    delete ui;
}

void newTrack::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap img(tr(":/tong7you.png"));
    img=img.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, img);
    //painter.end();
}

void newTrack::swBtnClick(){
    QString cmd=QString("walking(%0, %1, %2, %3)")
            .arg(ui->wslatEdit->text()).arg(ui->wslonEdit->text()).arg(ui->welatEdit->text()).arg(ui->welonEdit->text());
    ui->walkview->page()->runJavaScript(cmd);
}

void newTrack::scBtnClick(){
    QString cmd=QString("cardrive(%0, %1, %2, %3)")
            .arg(ui->cslatEdit->text()).arg(ui->cslonEdit->text()).arg(ui->celatEdit->text()).arg(ui->celonEdit->text());
    ui->carview->page()->runJavaScript(cmd);
}
