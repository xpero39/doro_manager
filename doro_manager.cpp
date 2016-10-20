#include "doro_manager.h"
#include "ui_doro_manager.h"
#include <QTime>
#include <QDate>
#include <QString>
#include <QTimer>
#include <QApplication>
#include <QStyleFactory>

#include <QtSql>
#include <QtDebug>

#include <QMessageBox>
#include <QFile>

doro_manager::doro_manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::doro_manager)
{
    ui->setupUi(this);

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    this->timer1= new QTimer(this);                                         //pointer for Main Tab showing time and date
    connect(timer1 , SIGNAL(timeout()), this, SLOT(showDateTime()));         //connects pointer with a signal and assigns a function to slot
    timer1->start(1000);                                            //starts a function with a pointer and calls it every 1000 miliseconds

    this->timer= new QTimer(this);
    connect(timer , SIGNAL(timeout()), this, SLOT(showTime()));     //pointer for Timer Tab showing time
    timer->start(1000);

    this->kaz = new QTimer(this);
    connect(kaz , SIGNAL(timeout()), this, SLOT(countdown()));         //inicialization of a pointer and links it to a function to countdown

    activeWork=true;
    activeBreak=false;

    //Added images
    QPixmap image_logo(":/Images/Images/time_sand2.png");
    image_logo = image_logo.scaledToWidth(ui->label_about->width(), Qt::SmoothTransformation);
    ui->label_about->setPixmap(image_logo);

    //Database connection
    QSqlDatabase db_con = QSqlDatabase::addDatabase("QSQLITE");
    db_con.setDatabaseName("C:/Faks/DIPLOMSKA/Doro_Manager/doro_manager/Database/doro_data.db");  //path

       if (!db_con.open())
       {
            ui->label_tl_pic->setText("Error: Connection with database failed.");
       }
       else
       {
            ui->label_tl_pic->setText("Database: Connection successful.");
       }

     //Show data in Calander widget and in task list, dist. list



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

    ui->clockLabel->setText(text);

}

void doro_manager::countdown()                        //function sets countdown timer value depending on work/break interwall and subtracts time
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
        //check if Work mode is active or Break mode
        if(activeWork==true){
                timeValueMin = ui->hSliderTime->value();            //sets slider values
                ui->counterLabel->setNum(timeValueMin);
                timeValueSec = 0;
                ui->counterLabel2->setNum(timeValueSec);            //label for value of seconds is set primary to zero
        }
        else if(activeBreak==true){
            timeValueMin = ui->hSliderBreak->value();            //sets slider values
            ui->counterLabel->setNum(timeValueMin);
            timeValueSec = 0;
            ui->counterLabel2->setNum(timeValueSec);
        }
    }
    else{
    timeValueMin=temporaryMin;                             //if program was paused then temporary values are used and set to the timer
    timeValueSec=temporarySec;                             //...instead of slider values
    temporaryMin=0;
    temporarySec=0;
    }

    kaz->start(1000);                                    //pointer starts to call a function every 1000 miliseconds
}

void doro_manager::on_resetButton_clicked()             //RESET button function resets values, also checks if break or work interval is in progress
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

void doro_manager::on_infoButton_clicked()          //function for INFO button provides us a information about pomodoro tehnique
{
    //QMessageBox::information(this, tr("Kaj je pomodoro tehnika?"), tr("<p>The <b>Pomodoro Technique</b> is a time management method developed by Francesco Cirillo in the late 1980s.[1] The technique uses a timer to break down work into intervals, <b>traditionally 25 minutes in length</b>, separated by short breaks. These intervals are called <i>pomodoros</i>, the plural in English of the Italian word <i>pomodoro</i>, which means tomato.[2] The method is based on the idea that <b>frequent breaks can improve mental agility</b>.[3][4]</p><p>Closely related to concepts such as <b>timeboxing</b> and iterative and incremental development used in software design, the method has been adopted in pair programming contexts.[5]</p><p>Vir: https://en.wikipedia.org/wiki/Pomodoro_Technique</p>"));
    ui->tabWidget->setCurrentIndex(5);
}

void doro_manager::on_stopButton_clicked()          //STOP button function stops the countdown timer and saves the timer values
{
    temporaryMin=timeValueMin;
    temporarySec=timeValueSec;

    kaz->stop();
}

doro_manager::~doro_manager()
{
    delete ui;
}

void doro_manager::on_pTimerButton_clicked()        //Main tab button which shows Pomodoro timer tab
{
    ui->tabWidget->setCurrentIndex(1);
}

void doro_manager::on_calendarButton_clicked()      //Main tab button which shows Calander tab
{
    ui->tabWidget->setCurrentIndex(2);
}

void doro_manager::on_taskListButton_clicked()      //Main tab button which shows Task list tab
{
    ui->tabWidget->setCurrentIndex(3);
}

void doro_manager::on_distractListButton_clicked()      //Main tab button which shows Distractions list tab
{
     ui->tabWidget->setCurrentIndex(4);
}

void doro_manager::on_aboutButton_clicked()         //Main tab button which shows About tab
{
    ui->tabWidget->setCurrentIndex(5);
}

void doro_manager::on_quitButton_clicked()          // Main Tab button that closes the program
{
    close();
}

void doro_manager::on_breakButton_clicked()     // Pomdoro timer tab button which sets pomodoro timer to break mode
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
        timeValueMin = ui->hSliderBreak->value();
        ui->counterLabel->setNum(timeValueMin);
        timeValueSec = 0;
        ui->counterLabel2->setNum(timeValueSec);
    }

    temporaryMin = 0;
    temporarySec = 0;
}

void doro_manager::on_AddTaskButton_clicked()
{
    //On button clicked date and task should be added to the list.
    //Refresh and show updated list based on current date
}
