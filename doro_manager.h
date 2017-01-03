#ifndef DORO_MANAGER_H
#define DORO_MANAGER_H

#include "delegate.h"
#include <QMainWindow>
#include <QTime>
#include <QDate>
#include <QString>
#include <QTimer>
#include <QApplication>
#include <QStyleFactory>
#include <QSound>
#include <QtSql>
#include <QtDebug>
#include <QMessageBox>
#include <QFile>
#include <QVariant>
#include <QModelIndex>

namespace Ui {
class doro_manager;
}

class doro_manager : public QMainWindow
{
    Q_OBJECT

    bool activeWork;
    bool activeBreak;                       //declaration of class variables
    int timeValueMin;
    int timeValueSec;
    int temporaryMin;
    int temporarySec;

public:
    explicit doro_manager(QWidget *parent = 0);
    ~doro_manager();

private slots:                               //declared private functions

    void showDateTime();

    void on_startButton_clicked();

    void on_resetButton_clicked();

    void showTime();

    void countdown();

    void on_infoButton_clicked();

    void on_stopButton_clicked();

    void on_aboutButton_clicked();

    void on_pTimerButton_clicked();

    void on_calendarButton_clicked();

    void on_taskListButton_clicked();

    void on_distractListButton_clicked();

    void on_quitButton_clicked();

    void on_breakButton_clicked();

    void on_AddTaskButton_clicked();

    void on_addDistractButton_clicked();

    //void on_dateEdit_dateChanged(const QDate &date);

    void on_calendarWidget_clicked(const QDate &date);

    void on_clearTheListButton_clicked();

    void refresh();

private:
    Ui::doro_manager *ui;

    QTimer *timer;                          //declared pointers
    QTimer *timer1;
    QTimer *kaz;
    QSound *sound;
    QSqlQueryModel *distmodel;
    QSqlQueryModel *taskmodel;
    QSqlTableModel *calmodel; //Calander tab task model
    delegate *mydelegate; //delegate pointer
};

#endif // DORO_MANAGER_H
