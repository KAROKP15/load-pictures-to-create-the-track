#ifndef NEWTRACK_H
#define NEWTRACK_H

#include <QWidget>
#include <QWebEngineView>
#include <QWebChannel>
#include <QDir>
#include "bridge.h"

namespace Ui {
class newTrack;
}

class newTrack : public QWidget
{
    Q_OBJECT

public:
    explicit newTrack(QWidget *parent = nullptr);
    ~newTrack();
    virtual void paintEvent(QPaintEvent *event);
    QWebEngineView *m_view;//加载HTML
    QWebChannel *channel;//实现数据交互

protected slots:
    void swBtnClick();
    void scBtnClick();

private:
    Ui::newTrack *ui;
};

#endif // NEWTRACK_H
