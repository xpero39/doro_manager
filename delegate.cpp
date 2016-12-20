#include "delegate.h"
#include <QApplication>
#include <QSqlQuery>
#include <QEvent>

#include <QPainter>
#include <QStyleOptionButton>
#include <QMouseEvent>


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
        //qInfo("New checkbox.");
        QVariant data = index.model()->data(index, Qt::CheckStateRole).toInt();
        if(data == 1)
        {
            qDebug("New checkbox. XX");
            QCheckBox *editor = new QCheckBox(parent);
            editor->setChecked(true);
            return editor;
        } else if (data == 0)
        {
            //Checkbox is unchecked by default
            QCheckBox *editor = new QCheckBox(parent);
            return editor;
        }
        else {
        return QStyledItemDelegate::createEditor(parent, option, index);
        }
}

    //Current data that you modify
/*void delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
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
}*/
    //Changes size based on your needs
/*void delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
    //editor->setGeometry(option.displayAlignment(Qt::AlignCenter));
    //editor->setStyleSheet("margin-left:50%; margin-right:50%;");
    //editor->setGeometry(option.rect);
}*/

/*void delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
     QStyleOptionViewItem viewItemOption(option);

        if (index.column() == 3)
        {
            const int textMargin = QApplication::style()->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
            QRect newRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                                QSize(option.decorationSize.width() + 5,option.decorationSize.height()),
                                                QRect(option.rect.x() + textMargin, option.rect.y(),
                                                      option.rect.width() - (2 * textMargin), option.rect.height()));
            viewItemOption.rect = newRect;
        }
        QStyledItemDelegate::paint(painter, viewItemOption, index);
}*/

void delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // Setting parameters
           Qt::CheckState state = (Qt::CheckState)index.data( Qt::CheckStateRole ).toInt();
           QStyleOptionButton opt;

           opt.state = QStyle::State_Enabled; // CheckBox enabled
           if ( option.state & QStyle::State_MouseOver )
               opt.state |= QStyle::State_MouseOver; // Mouse over sell
           switch ( state )  // Check box state
           {
           case Qt::Unchecked:
               opt.state |= QStyle::State_Off;
               break;
           case Qt::PartiallyChecked:
               opt.state |= QStyle::State_NoChange;
               break;
           case Qt::Checked:
               opt.state |= QStyle::State_On;
               break;
           }

           /*QVariant data = index.model()->data(index, Qt::CheckStateRole).toInt();
           if(data == 1)
           {
               opt.state |= QStyle::State_On;
           } else
           {
               opt.state |= QStyle::State_Off;
           }*/


           // Check box rect
           opt.rect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &opt, NULL );
           const int x = option.rect.center().x() - opt.rect.width() / 2;
           const int y = option.rect.center().y() - opt.rect.height() / 2;
           opt.rect.moveTo( x, y );

           // Optional: draw hover focus
           if ( option.state & QStyle::State_MouseOver )
               painter->fillRect( option.rect, QBrush( QColor( 0xff, 0xff, 0xaa, 0x60 ) ) );

           // Mandatory: drawing check box
           QApplication::style()->drawControl( QStyle::CE_CheckBox, &opt, painter );
}

/*bool delegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
        Q_ASSERT(event);
        Q_ASSERT(model);

        // make sure that the item is checkable
        Qt::ItemFlags flags = model->flags(index);
        if (!(flags & Qt::ItemIsUserCheckable) || !(flags & Qt::ItemIsEnabled))
            return false;
        // make sure that we have a check state
        QVariant value = index.data(Qt::CheckStateRole);
        if (!value.isValid())
            return false;
        // make sure that we have the right event type
        if (event->type() == QEvent::MouseButtonRelease)
        {
            const int textMargin = QApplication::style()->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
            QRect checkRect = QStyle::alignedRect(option.direction, Qt::AlignCenter, option.decorationSize, QRect(option.rect.x() + (2 * textMargin), option.rect.y(), option.rect.width() - (2 * textMargin), option.rect.height()));

        } else {
            return false;
        }

        Qt::CheckState state = (static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked ? Qt::Unchecked : Qt::Checked);

                emit(clickSignal(index.row()));
                return model->setData(index, state, Qt::CheckStateRole);
}*/

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

                QStyleOptionButton opt;
                opt.rect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &opt, NULL );
                const int x = option.rect.center().x() - opt.rect.width() / 2;
                const int y = option.rect.center().y() - opt.rect.height() / 2;
                opt.rect.moveTo( x, y );

                if ( opt.rect.contains( e->pos() ) )
                {
                    // TODO: process click on checkbox logic
                    Qt::CheckState state = (Qt::CheckState)index.data( Qt::CheckStateRole ).toInt();
                    switch ( state )
                    {
                    case Qt::Unchecked:
                        state = Qt::PartiallyChecked;
                        break;
                    case Qt::PartiallyChecked:
                        state = Qt::Checked;
                        break;
                    case Qt::Checked:
                        state = Qt::Unchecked;
                        break;
                    }

                    model->setData( index, state, Qt::CheckStateRole );
                }
                return true;
            }

        default:
            break;
        }

        return QAbstractItemDelegate::editorEvent( event, model, option, index );
}

bool delegate::databaseUpdate(int task_id, int checkbox_value) const
{
    QSqlQuery query;
    query.prepare("UPDATE task_list SET finished = :finished WHERE id = :id");
    query.bindValue(":finished", checkbox_value);
    query.bindValue(":id", task_id);
    return query.exec();
}
