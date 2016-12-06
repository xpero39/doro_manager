#include "delegate.h"
#include <QSqlQuery>

delegate::delegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}
      //Creates the editor
 QWidget *delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
     //qInfo("New checkbox.");
    if(index.isValid() && index.column() == 3)
    {
        QVariant data = index.model()->data(index, Qt::CheckStateRole).toInt();
        if(data == 1)
        {
            qDebug("New checkbox. XX");
            QCheckBox *editor = new QCheckBox(parent);
            editor->setChecked(true);
            return editor;
        }
        else
        {
            //Checkbox is unchecked by default
            QCheckBox *editor = new QCheckBox(parent);
            return editor;
        }

    }
    else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

    //Current data that you modify
void delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //int value = index.calmodel()->data(index, Qt::CheckStateRole).toInt();
    //QVariant value = model->data(index, role);
    //Qt::CheckState value = index.model()->data(index, Qt::CheckStateRole);
    QVariant value = index.model()->data(index, Qt::CheckStateRole).toInt();
    QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
    checkbox->checkState();

    //const QAbstractItemModel * model = index.model();
    //model->data(model->index(row, col), Qt::DisplayRole);
   // QVariant row = index.data();
    //index.row();

    //databaseUpdate(row,value);
}
    //The data you return to the model
void delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
    checkbox->checkState();
    bool value = checkbox->checkState();
    model->setData(index, value, Qt::CheckStateRole);
}
    //Changes size based on your needs
void delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    //editor->setGeometry(option.displayAlignment(Qt::AlignCenter));
    //editor->setStyleSheet("margin-left:50%; margin-right:50%;");
    //editor->setGeometry(option.rect);
}

/*void delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


}

bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{

}*/

bool delegate::databaseUpdate(int task_id, int checkbox_value) const
{
    QSqlQuery query;
    query.prepare("UPDATE task_list SET finished = :finished WHERE id = :id");
    query.bindValue(":finished", checkbox_value);
    query.bindValue(":id", task_id);
    return query.exec();
}
