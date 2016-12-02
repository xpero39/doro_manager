#include <QtWidgets>
#include <QApplication>
#include "connection.h"
#include "doro_manager.h"
#include "checkbox_model.h"


void initializeModel(QSqlQueryModel *model)
{
    QDate date = QDate::currentDate();
    QSqlQuery query;
    query.prepare("SELECT id, task, finished FROM task_list WHERE date = :date");
    query.bindValue(":date", date);
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TASK"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("FINISHED"));
    //doro_manager::ui->tableView_Calendar->setModel(doro_manager::calmodel);
}

QTableView* createView(QSqlQueryModel *model, const QString $title = "")
{
    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();
    return view;
}

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

