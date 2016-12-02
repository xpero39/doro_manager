#include <QtWidgets>
#include <QSql>
#include <QSqlQuery>
#include "checkbox_model.h"

checkbox_model::checkbox_model(QObject *parent) : QSqlQueryModel(parent)
{
}

Qt::ItemFlags checkbox_model::flags(const QModelIndex &index) const
{
        Qt::ItemFlags flags = QSqlQueryModel::flags(index);
        if(index.column() == 2)
             return QSqlQueryModel::flags(index) | Qt::ItemIsUserCheckable;
        return QSqlQueryModel::flags(index);
}

QVariant checkbox_model::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    //if(index.column() == 2 && role == Qt::CheckStateRole)
    if(index.column() == 2 && role == Qt::DisplayRole)
    {
            //implement your logic to return the check state
            //....
            //if (index.column() == 2) //add a checkbox to cell(1,0)
            if(value.toInt()==1){
               return Qt::Checked;
            }
            else  if(value.toInt()==0){
               return Qt::Unchecked;
            }
    }
}

//setData() is called each time the user edits the table i.e. save data refresh view
bool checkbox_model::setData(const QModelIndex &index, const QVariant &value, int /*role*/ )
{
    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    int id = QSqlQueryModel::data(primaryKeyIndex).toInt();
   // clear();
    bool ok;
    //if(index.column() == 2 && role == Qt::CheckStateRole)
    if(index.column() == 2)
    {
            ok = setCheckbox(id, value.toInt());
    }
    /*else
    {
            return false;
            //QSqlQueryModel::setData(index, value, role);
    }*/
    //refresh();
    return ok;
}


bool checkbox_model::setCheckbox(int task_id, int checkbox_value)
{
            QSqlQuery query;
            query.prepare("UPDATE task_list SET finished = :finished WHERE id = :id");
            query.bindValue(":finished", checkbox_value);
            query.bindValue(":id", task_id);
            return query.exec();
}

/*void checkbox_model::refresh(QSqlQueryModel *model)
{
    model->setQuery("SELECT id, task, finished FROM task_list WHERE date = :date");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TASK"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("FINISHED"));

}
*/
