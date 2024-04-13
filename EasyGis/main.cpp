#include <QApplication>
#include <QDesktopWidget>

#include "MainWindow/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    float w_factor = 800.0 / 1920.0;
    float h_factor = 600.0 / 1080.0;

    MainWindow w;
    w.resize(QApplication::desktop()->width() * w_factor, QApplication::desktop()->height() * h_factor);
    w.show();
    return a.exec();
}
