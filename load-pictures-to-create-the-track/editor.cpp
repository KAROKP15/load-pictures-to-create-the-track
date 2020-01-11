#include "editor.h"
#include "ui_editor.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //“生成轨迹”的Tab

    //导入地图API
    QString filepath="file:///Users/karo/tong7you/baidumap.html";
    ui->webview->page()->load(QUrl(filepath));

    //上传图片功能实现
    connect(ui->openBtn,&QPushButton::clicked,this,&Widget::getExifInfo);
    ui->pictureLbl->setVisible(false);
    ui->longitudeEdit->setVisible(false);
    ui->latitudeEdit->setVisible(false);

    //创建通道对象和JS交互
    channel=new QWebChannel(this);
    bridge *mybridge=new bridge();

    //注册对象，注册名与JS函数用到的一致
    channel->registerObject("bridge_name", (QObject*)mybridge);
    ui->webview->page()->setWebChannel(channel);

    //根据图片的GPS信息在地图上完成定位
    connect(ui->p2tBtn, &QPushButton::clicked, this, &Widget::btnClick);
    connect(ui->finishBtn, &QPushButton::clicked, this, &Widget::finishBtnClick);

    //“修改轨迹”
    ui->webview_2->page()->load(QUrl(filepath));

    //“修改位置”
    connect(ui->fpBtn, &QPushButton::clicked, this, &Widget::fpBtnClick);

    //“修改时间”
    connect(ui->ftmBtn, &QPushButton::clicked, this, &Widget::ftmBtnClick);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap img(tr(":/tong7you.png"));
    img=img.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, img);
    //painter.end();
}

void Widget::btnClick(){
    photonum++;
    QString cmd=QString("theLocation(%0, %1)")
            .arg(ui->longitudeEdit->text())
            .arg(ui->latitudeEdit->text());
    ui->webview->page()->runJavaScript(cmd);
}

void Widget::getExifInfo(){
    QString strFile =  QFileDialog::getOpenFileName(this); //传this，打开的是当前项目构建的目录
    QString filepath=QString(strFile.toUtf8().data());
    //qDebug()<<strFile.toUtf8().data();

    /*
    QPixmap image;
    image.load(strFile);
    ui->pictureLbl->setScaledContents(true); //true 表明填充所有的可用空间
    ui->pictureLbl->clear(); //先清空
    ui->pictureLbl->setPixmap(image); //设置图片*/

    //准备借助EXIF读取信息
    EXIFINFO exifInfo;  //结构体
    //将QString转换成const char*
    const char* picPath = strFile.toUtf8().data();
    //qDebug()<<picPath;

    FILE *fp = fopen(picPath,"rb"); //C语言读写文件，以二进制的读文件

    if(fp) //表明打开成功
    {
        Cexif ce(&exifInfo); //调用构造函数，传入结构体指针，初始化对象ce
        bool b = ce.DecodeExif(fp);  //调用解析函数，解析Exif信息
        fclose(fp);
        if(b)
        {
            //传递经纬度数据给API完成定位
            ui->latitudeEdit->setText(QString::number(exifInfo.Latitude)); //纬度
            ui->longitudeEdit->setText(QString::number(exifInfo.Longitude));//经度

            //连接数据库记录此图片信息
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

            //执行查询，获取tripID数
            QString str1=QString("select count(*) from trip;");
            QSqlQuery query1(str1);
            query1.next();
            int tripId=query1.value(0).toInt()+1;

            //获取时间信息
            QString date=QString(exifInfo.DateTime).replace(":","-").mid(0,10);

            //执行插入,userID默认为000001
            QString str=QString("insert into picture values('%1','%2','%3','%4','%5','000001');")
                    .arg(filepath).arg(date).arg(QString::number(exifInfo.Latitude)).arg(exifInfo.Longitude).arg(tripId);
            qDebug()<<str;
            QSqlQuery sqlQuery(str);


//            "光圈："<<exifInfo.ApertureFNumber;
//            "ISO感光度："<<exifInfo.ISOequivalent;
//            "曝光时间："<<exifInfo.ExposureTime;
//            "相机模型："<<exifInfo.CameraModel;
//            "纬度："<<exifInfo.Latitude;
//            "纬度参考："<<exifInfo.LatitudeRef; //例如南纬
//            "经度："<<exifInfo.Longitude;
//            "经度参考:"<<exifInfo.LongitudeRef; //例如东经
//            "时间："<<exifInfo.DateTime;

        }
        else
        {
            qDebug()<<tr("解析失败").toUtf8().data();
        }
    }
    else
    {
        qDebug()<<tr("文件打开失败！").toUtf8().data();
    }

}

void Widget::finishBtnClick(){
    QString cmd=QString("drawLine()");
    ui->webview->page()->runJavaScript(cmd);

    //连接数据库记录此轨迹信息
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

    //执行查询，获取tripID数
    QString str1=QString("select count(*) from trip;");
    QSqlQuery query1(str1);
    query1.next();
    int tripId=query1.value(0).toInt()+1;

    //执行插入,userID默认为000001
    QString str=QString("insert into trip values('%1','%2','%3','000001');")
            .arg(tripId).arg(ui->tripnameEdit->text()).arg(photonum);
    qDebug()<<str;
    QSqlQuery sqlQuery(str);
    ui->webview_2=ui->webview;
}

void Widget::fpBtnClick(){
    //连接数据库更改此图片信息
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

    //执行查询，获取tripID数
    QString str1=QString("select * from picture where userid='%1';").arg(ui->fpUser->text());
    QSqlQuery query1(str1);
    int picNum=ui->fpPicNum->text().toUInt();
    while(picNum!=0){
        query1.next();
        picNum--;
    }
    double latitude=query1.value(2).toDouble();
    double longitude=query1.value(3).toDouble();
    double newlat=ui->fpNewLat->text().toDouble();
    double newlon=ui->fpNewLon->text().toDouble();
    qDebug()<<latitude<<longitude<<newlat<<newlon;
    QString str2=QString("update picture set gpslatitude=%1,gpslongitude=%2 where userid='%3' and gpslatitude=%4 and gpslongitude=%5;")
            .arg(newlat).arg(newlon).arg(ui->fpUser->text()).arg(latitude).arg(longitude);
    QSqlQuery query2(str2);
    ui->fpTipLbl->setText("修改成功！");
}

void Widget::ftmBtnClick(){
    //连接数据库更改此图片信息
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

    //执行查询，获取tripID数
    QString str1=QString("select * from picture where userid='%1';").arg(ui->ftmUser->text());
    QSqlQuery query1(str1);
    int picNum=ui->ftmPicNum->text().toUInt();
    while(picNum!=0){
        query1.next();
        picNum--;
    }
    QString newtime=ui->ftmNewTime->text();
    double latitude=query1.value(2).toDouble();
    double longitude=query1.value(3).toDouble();
    qDebug()<<newtime;
    QString str2=QString("update picture set shootingdate='%1' where userid='%2' and gpslatitude=%3 and gpslongitude=%4;")
            .arg(newtime).arg(ui->ftmUser->text()).arg(latitude).arg(longitude);
    QSqlQuery query2(str2);
    ui->ftmTipLbl->setText("修改成功！");
}
