#ifndef DELEGATE_H
#define DELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QCheckBox>

class delegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit delegate(QObject *parent = 0);

    //Creates the editor
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //Current data that you modify
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    //The data you return to the model
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    //Changes size based on your needs
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

};

#endif // DELEGATE_H
