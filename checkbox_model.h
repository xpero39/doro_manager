#ifndef CHECKBOX_MODEL_H
#define CHECKBOX_MODEL_H

#include <QSqlQueryModel>

class checkbox_model : public QSqlQueryModel
{
    Q_OBJECT

public:
     checkbox_model(QObject *parent = 0);
     Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
     QVariant data(const QModelIndex &item, int role) const Q_DECL_OVERRIDE;
     bool setData(const QModelIndex &index, const QVariant &value, int role) Q_DECL_OVERRIDE;

     //~checkbox_model();
private:
    bool setCheckbox(int task_id, int checkbox_value);
    void refresh();
};

#endif // CHECKBOX_MODEL_H

