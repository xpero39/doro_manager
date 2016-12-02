#include "delegate.h"

delegate::delegate(QObject *parent) :
    QItemDelegate(parent)
{
}
    //Creates the editor
 QWidget *delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.isValid() && index.column() == 2){
      // if()
        QCheckBox *editor = new QCheckBox(parent);
        return editor;
    }
    else {
        return QItemDelegate::createEditor(parent, option, index);
    }
}
    //Current data that you modify
void delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    //int value = index.calmodel()->data(index, Qt::CheckStateRole).toInt();
   Qt::CheckState value = index.model()->data(index, Qt::CheckStateRole).t  ;
    QCheckBox *checkbox = static_cast<QCheckBox*>(editor);
    checkbox->setCheckState(value);

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
    editor->setGeometry(option.displayAlignment(Qt::AlignCenter));
}


