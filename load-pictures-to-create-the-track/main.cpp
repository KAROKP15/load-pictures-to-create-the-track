#include "editor.h"
#include <QApplication>
#include "mainpage.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainpage mainpage;
    mainpage.show();
    mainpage.setWindowTitle("Tong You");
    return a.exec();
}
