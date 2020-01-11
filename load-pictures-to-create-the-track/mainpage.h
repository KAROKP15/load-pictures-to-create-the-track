#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QMovie>
#include "login.h"
#include "editor.h"
#include "newtrack.h"
#include "select.h"

namespace Ui {
class mainpage;
}

class mainpage : public QWidget
{
    Q_OBJECT

public:
    explicit mainpage(QWidget *parent = nullptr);
    ~mainpage();
    virtual void paintEvent(QPaintEvent *event);
    login *new_login;
    Widget *new_editor;
    newTrack *new_track;
    select *new_select;

protected slots:
    void login();
    void editInfo();
    void newInfo();
    void showInfo();

private:
    Ui::mainpage *ui;
};

#endif // MAINPAGE_H
