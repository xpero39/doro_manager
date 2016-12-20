#include <QtWidgets>
#include <QApplication>
#include "connection.h"
#include "doro_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!createConnection())
        return 1;

    doro_manager w;
    w.show();

    return a.exec();

}

