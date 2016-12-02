#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QCoreApplication>

static bool createConnection()
{
    QString dir_path = QCoreApplication::applicationDirPath(); //Gets directory of the executable
    QSqlDatabase db_con = QSqlDatabase::addDatabase("QSQLITE");
    db_con.setDatabaseName(dir_path +"/Database/doro_data.db");
   //db_con.setDatabaseName(":memory:");
    if (!db_con.open()) {
        QMessageBox::critical(0, qApp->tr("Can't open the database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

   return true;
}

#endif // CONNECTION_H
