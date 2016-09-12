#include "doro_manager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    doro_manager w;
    w.show();

    return a.exec();
}
