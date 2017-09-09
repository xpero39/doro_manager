#ifndef DELEGATE_H
#define DELEGATE_H

#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QCheckBox>

class delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit delegate(QObject *parent = 0);
    ~delegate();

    //Creates the editor
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //Current data that you modify
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    //The data you return to the model
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    //Changes size based on your needs
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //Paints over the model, we draw a checkbox
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //EditorEvent has logic to what should happen when a certain event i.e. Mousebutton click is triggered.
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    bool databaseUpdate(int task_id, int checkbox_value) const;
    QModelIndex m_lastClickedIndex;

signals:
    void clickSignal();

};

#endif // DELEGATE_H
