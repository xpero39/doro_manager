#include "doro_manager.h"
#include "checkbox_model.h"
#include <QApplication>

/*void initializeModel(QSqlQueryModel *model)
{
    QDate date = QDate::currentDate();
    QSqlQuery query;
    query.prepare("SELECT id, task, finished FROM task_list WHERE date = :date");
    query.bindValue(":date", date);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("TASK"));
    model->setHeaderData(2, Qt::Horizontal, tr("FINISHED"));
}*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    doro_manager w;
    w.show();
  //  checkbox_model calmodel;
  //  initializeModel(calmodel);


    return a.exec();
}

