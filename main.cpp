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

    //checkbox_model calanderModel;
    //initializeModel(&calanderModel);
   // createView(&calanderModel, QObject::tr("Checkbox Calander Model"));
  //  checkbox_model calmodel;
  //  initializeModel(calmodel);

    return a.exec();
}

