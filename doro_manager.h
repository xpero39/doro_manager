#ifndef DORO_MANAGER_H
#define DORO_MANAGER_H

#include <QMainWindow>

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

private slots:                               //daclared private functions
    void showDateTime();

    void on_startButton_clicked();

    void on_closeButton_clicked();

    void on_resetButton_clicked();

    void showTime();

    void odstevanje();

    void on_infoButton_clicked();

    void on_stopButton_clicked();


    void on_pushButton_pTimer_clicked();

    void on_pushButton_Calendar_clicked();

    void on_pushButton_tList_clicked();

    void on_pushButton_dList_clicked();

    void on_aboutButton_clicked();

private:
    Ui::doro_manager *ui;

    QTimer *timer;                          //daclared pointers
    QTimer *timer1;                          //daclared pointers
    QTimer *kaz;
};

#endif // DORO_MANAGER_H
