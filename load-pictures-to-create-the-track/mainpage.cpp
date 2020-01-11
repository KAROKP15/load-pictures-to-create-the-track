#include "mainpage.h"
#include "ui_mainpage.h"

mainpage::mainpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainpage)
{
    ui->setupUi(this);

    connect(ui->loginBtn, &QPushButton::clicked, this, &mainpage::login);
    connect(ui->newBtn, &QPushButton::clicked, this, &mainpage::newInfo);
    connect(ui->editBtn, &QPushButton::clicked, this, &mainpage::editInfo);
    connect(ui->showBtn, &QPushButton::clicked, this, &mainpage::showInfo);
}

mainpage::~mainpage()
{
    delete ui;
}

void mainpage::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap img(tr(":/tong7you.png"));
    img=img.scaled(800, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, img);
}

void mainpage::login(){
    new_login=new class login;
    new_login->show();
}

void mainpage::newInfo(){
    new_track=new newTrack;
    new_track->show();
}

void mainpage::editInfo(){
    new_editor=new Widget;
    new_editor->show();
}

void mainpage::showInfo(){
    new_select=new select;
    new_select->show();
}
