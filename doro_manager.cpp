#include "doro_manager.h"
#include "ui_doro_manager.h"
#include <QTime>
#include <QDate>
#include <QString>
#include <QTimer>

#include <QtSql>
#include <QtDebug>

#include <QMessageBox>
#include <QFile>

doro_manager::doro_manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::doro_manager)
{
    ui->setupUi(this);

    this->timer1= new QTimer(this);
    connect(timer1 , SIGNAL(timeout()), this, SLOT(showDateTime()));         //connects pointer with a signal and assigns a function to slot
    timer1->start(1000);                                            //starts a function with a pointer and calls it every 1000 miliseconds

    this->timer= new QTimer(this);
    connect(timer , SIGNAL(timeout()), this, SLOT(showTime()));         //connects pointer with a signal and assigns a function to slot
    timer->start(1000);                                            //starts a function with a pointer and calls it every 1000 miliseconds

    this->kaz = new QTimer(this);
    connect(kaz , SIGNAL(timeout()), this, SLOT(odstevanje()));         //inicialization of a pointer and links it to a function

    activeWork=true;
    activeBreak=false;
}


void doro_manager::showDateTime()                   //method to show current date and time
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh : mm : ss");
    ui->label_time->setText(text);

    QDate date = QDate::currentDate();
    QString text2 = date.toString("d of MMMM yyyy");
    ui->label_date->setText(text2);
}

void doro_manager::showTime()                   //method to show current time
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh : mm : ss");
    /*if ((time.second() % 2) == 0){
            text[3] = ' ';
            text[8] = ' ';
    }*/
    ui->clockLabel->setText(text);

}

void doro_manager::odstevanje()                        //function sets countdown timer value depending on work/break interwall and subracts time
{
   if ((timeValueMin == 0) && (timeValueSec == 0))                  //loop checks if the countdown ended to switch work and break time intervals
    {
       if(activeWork==true){
       activeWork=false;
       activeBreak=true;
       timeValueMin = ui->hSliderBreak->value();
       ui->counterLabel->setNum(timeValueMin);
       timeValueSec = 0;
       ui->counterLabel2->setNum(timeValueSec);
       }
       else if(activeBreak==true){
           activeBreak=false;
           activeWork=true;
           timeValueMin = ui->hSliderTime->value();
           ui->counterLabel->setNum(timeValueMin);
           timeValueSec = 0;
           ui->counterLabel2->setNum(timeValueSec);
       }
            //player->play();                                       //pointer calls a function to play a sound
    }

    if (timeValueSec == 0)                                          //if loop checks if the value of seconds is 0 and changes it to 59 if true
    {                                                                  //it also subtracts value of minutes by one
        timeValueSec = 59;
        timeValueMin--;
    }
    else timeValueSec--;

    ui->counterLabel->setNum(timeValueMin);                         //setting the value of minutes to the label
    ui->counterLabel2->setNum(timeValueSec);                        //setting the value of seconds to the label
}

void doro_manager::on_startButton_clicked()         //function that is run when the button START is clicked
{
    kaz->stop();                                    //stops pointer, function if active

    if((temporaryMin == 0)&&(temporarySec == 0)){          //checks if temporary values are zero to set values from slider
    timeValueMin = ui->hSliderTime->value();            //sets slider values
    ui->counterLabel->setNum(timeValueMin);
    timeValueSec = 0;
    ui->counterLabel2->setNum(timeValueSec);            //label for value of seconds is set primary to zero
    }
    else{
    timeValueMin=temporaryMin;                             //if program was paused then temporary values are used and set to the timer
    timeValueSec=temporarySec;                             //...instead of slider values
    temporaryMin=0;
    temporarySec=0;
    }

    kaz->start(1000);                                       //pointer starts to call a function every 1000 miliseconds

}

void doro_manager::on_closeButton_clicked()                 //CLOSE button function activated when clicked, it closes the application
{
    close();
}


void doro_manager::on_resetButton_clicked()                 //RESET button function resets values, also checks if break or work interval is in progress
{
    if(activeWork==true){
    timeValueMin = ui->hSliderTime->value();
    ui->counterLabel->setNum(timeValueMin);
    timeValueSec=0;
    ui->counterLabel2->setNum(timeValueSec);
    }

    if(activeBreak==true){
     timeValueMin = ui->hSliderBreak->value();
     ui->counterLabel->setNum(timeValueMin);
     timeValueSec=0;
     ui->counterLabel2->setNum(timeValueSec);
    }
}

void doro_manager::on_infoButton_clicked()                  //function for INFO button provides us a information about pomodoro tehnique
{
    QMessageBox::information(this, tr("Kaj je pomodoro tehnika?"), tr("<p>The <b>Pomodoro Technique</b> is a time management method developed by Francesco Cirillo in the late 1980s.[1] The technique uses a timer to break down work into intervals, <b>traditionally 25 minutes in length</b>, separated by short breaks. These intervals are called <i>pomodoros</i>, the plural in English of the Italian word <i>pomodoro</i>, which means tomato.[2] The method is based on the idea that <b>frequent breaks can improve mental agility</b>.[3][4]</p><p>Closely related to concepts such as <b>timeboxing</b> and iterative and incremental development used in software design, the method has been adopted in pair programming contexts.[5]</p><p>Vir: https://en.wikipedia.org/wiki/Pomodoro_Technique</p>"));
}

void doro_manager::on_stopButton_clicked()                                  //STOP button function stops the countdown timer and saves the timer values
{
    temporaryMin=timeValueMin;
    temporarySec=timeValueSec;

    kaz->stop();
}



doro_manager::~doro_manager()
{
    delete ui;
}


void doro_manager::on_pushButton_pTimer_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void doro_manager::on_pushButton_Calendar_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void doro_manager::on_pushButton_tList_clicked()
{
    ui->tabWidget->setCurrentIndex(3);
}

void doro_manager::on_pushButton_dList_clicked()
{
    ui->tabWidget->setCurrentIndex(4);
}

void doro_manager::on_aboutButton_clicked()
{
    QMessageBox::information(this, tr("About Doro Manager."), tr("<p>Doro Manager is a pomodoro tehnique time managment application for more productive work or study.</p>"));
}
