#include "delegate.h"
#include <QApplication>
#include <QSqlQuery>
#include <QEvent>
#include <QPainter>
#include <QStyleOptionButton>
#include <QMouseEvent>
#include <QtDebug>

delegate::delegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

delegate::~delegate()
{
}

      //Creates the editor
QWidget *delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
        QCheckBox *chkbox =new QCheckBox(parent);
        return chkbox;
}

    //Current data that you modify
void delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QVariant data = index.model()->data(index, Qt::DisplayRole).toInt();
    if(data == 1)
    {
        static_cast<QCheckBox*>(editor)->setCheckState(Qt::Checked);
    }
    else if (data == 0)
    {
        static_cast<QCheckBox*>(editor)->setCheckState(Qt::Unchecked);
    }
    else {
    QStyledItemDelegate::setEditorData(editor, index);
    }
}
    //The data you return to the model
void delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QVariant value = static_cast<QCheckBox*>(editor)->checkState();
    model->setData(index, value, Qt::CheckStateRole);
}

    //Changes size based on your needs
void delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionButton opt;
    opt.rect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &opt, NULL );
    const int x = option.rect.center().x() - opt.rect.width() / 2;
    const int y = (option.rect.center().y() - opt.rect.height() / 2)-7; //Small adjustment to apear more centrally.(paint() checkbox interference?)
    opt.rect.moveTo( x, y );
    editor->setGeometry(option.rect);
    editor->move(x,y);
}

void delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
            // Setting parameters
           Qt::CheckState state = (Qt::CheckState)index.data( Qt::CheckStateRole ).toInt();
           QStyleOptionButton opt;

           opt.state = QStyle::State_Enabled; // Enabling checkbox
           if ( option.state & QStyle::State_MouseOver )
               opt.state |= QStyle::State_MouseOver; // Mouse oversell

           QVariant data = index.model()->data(index, Qt::DisplayRole/*CheckStateRole*/).toInt();
           if(data == 1)
           {
               opt.state |= QStyle::State_On;
           } else
           {
               opt.state |= QStyle::State_Off;
           }

          // Checkbox rect
           opt.rect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &opt, NULL );
           const int x = option.rect.center().x() - opt.rect.width() / 2;
           const int y = option.rect.center().y() - opt.rect.height() / 2;
           opt.rect.moveTo( x, y );

           // Draws hover focus
           if ( option.state & QStyle::State_MouseOver )
               painter->fillRect( option.rect, QBrush( QColor( 0xff, 0xff, 0xaa, 0x60 ) ) );

           // Drawing checkbox
           QApplication::style()->drawControl( QStyle::CE_CheckBox, &opt, painter );
}

bool delegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
       switch ( event->type() )
        {
        case QEvent::MouseButtonPress:
            m_lastClickedIndex = index;
            break;

        case QEvent::MouseButtonRelease:
            {
                if ( index != m_lastClickedIndex )
                    break;
                QMouseEvent *e = static_cast< QMouseEvent * >( event );
                if ( e->button() != Qt::LeftButton )
                    break;
                m_lastClickedIndex = QModelIndex();

                //Update database
                QVariant id = index.sibling(index.row(),0).data(Qt::DisplayRole).toInt();
                QVariant value = index.model()->data(index, Qt::DisplayRole).toInt();
               /* int xid = id.toInt();
                int xvalue = value.toInt();
                if (xvalue == 0)
                {
                    xvalue = 1;
                   // opt.state |= QStyle::State_On;
                }
                else
                {
                    xvalue = 0;
                 //   opt.state |= QStyle::State_Off;
                }
                databaseUpdate(xid,xvalue);*/

                QStyleOptionButton opt;
                opt.rect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &opt, NULL );
                const int x = option.rect.center().x() - opt.rect.width() / 2;
                const int y = option.rect.center().y() - opt.rect.height() / 2;
                opt.rect.moveTo( x, y );

                if ( opt.rect.contains( e->pos() ) )
                {
                    // Process click on checkbox logic
                    Qt::CheckState state = (Qt::CheckState)index.data( Qt::CheckStateRole ).toInt();
                   /* switch ( state )
                    {
                    case Qt::Unchecked:
                        state = Qt::PartiallyChecked;
                        break;
                    case Qt::PartiallyChecked:
                        state = Qt::Checked;
                        break;
                    case Qt::Checked:
                        state = Qt::Unchecked;
                        break;*/

                        int xid = id.toInt();
                        int xvalue = value.toInt();
                        if (xvalue == 0)
                        {
                            xvalue = 1;
                            state = Qt::Checked;
                        }
                        else
                        {
                            xvalue = 0;
                            state = Qt::Unchecked;
                        }
                        databaseUpdate(xid,xvalue);
                        emit clickSignal();
                        model->setData( index, state, Qt::CheckStateRole );
                }
                return true;
            }

        default:
            break;
        }

        return QStyledItemDelegate::editorEvent( event, model, option, index );
}

bool delegate::databaseUpdate(int task_id, int checkbox_value) const
{
    QSqlQuery query;
    query.prepare("UPDATE task_list SET finished = :finished WHERE id = :id");
    query.bindValue(":finished", checkbox_value);
    query.bindValue(":id", task_id);
    return query.exec();
    qDebug() << query.lastQuery();
}

