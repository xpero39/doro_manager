#include "doro_manager.h"
#include "ui_doro_manager.h"

doro_manager::doro_manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::doro_manager)
{
    ui->setupUi(this);

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    this->timer1 = new QTimer(this);                                         //pointer for Main Tab showing time and date
    connect(timer1 , SIGNAL(timeout()), this, SLOT(showDateTime()));         //connects pointer with a signal and assigns a function to slot
    timer1->start(1000);                                            //starts a function with a pointer and calls it every 1000 miliseconds

    this->timer = new QTimer(this);
    connect(timer , SIGNAL(timeout()), this, SLOT(showTime()));     //pointer for Timer Tab showing time
    timer->start(1000);

    this->kaz = new QTimer(this);
    connect(kaz , SIGNAL(timeout()), this, SLOT(countdown()));         //inicialization of a pointer and links it to a function to countdown

    this->sound = new QSound("C:/Faks/DIPLOMSKA/Doro_Manager/doro_manager/Sounds/sound_alert.wav");

    activeWork=true;
    activeBreak=false;

    //Added images
    QPixmap image_logo(":/Images/Images/time_sand2.png");
    image_logo = image_logo.scaledToWidth(ui->label_about->width(), Qt::SmoothTransformation);
    ui->label_about->setPixmap(image_logo);

    image_logo = image_logo.scaledToWidth(ui->label_dl_pic->width(), Qt::SmoothTransformation);
    ui->label_dl_pic->setPixmap(image_logo);

    image_logo = image_logo.scaledToWidth(ui->label_main_pic->width(), Qt::SmoothTransformation);
    ui->label_main_pic->setPixmap(image_logo);

    image_logo = image_logo.scaledToWidth(ui->label_tl_pic->width(), Qt::SmoothTransformation);
    ui->label_tl_pic->setPixmap(image_logo);

    //Database connection
    QSqlDatabase db_con = QSqlDatabase::addDatabase("QSQLITE");
    db_con.setDatabaseName("C:/Faks/DIPLOMSKA/Doro_Manager/doro_manager/Database/doro_data.db");  //path

       if (!db_con.open()){
            ui->textBrowser_Calander->setText("Error: Connection with database failed.");
       }
       else {
            ui->textBrowser_Calander->setText("Database: Connection successful.");
       }

     //Show data in Calender widget and in task list, dist. list
     QSqlQueryModel *model = new QSqlQueryModel();
     QSqlQuery query;
     query.prepare("SELECT distraction FROM dist_list");
     query.exec();
     model->setQuery(query);
     ui->listView_distraction->setModel(model);
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
        sound->play();                                       //pointer calls a function to play a alert sound
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

void doro_manager::on_addDistractButton_clicked()
{
    if(!ui->lineEdit_DistList->isModified()){
        //DOES NOTHING IF NOT MODIFIED
    }
    else{
              QSqlQueryModel *model = new QSqlQueryModel();
              QSqlQuery query;
              query.prepare("INSERT INTO dist_list(distraction) VALUES(:distraction)");
              query.bindValue(":distraction",ui->lineEdit_DistList->text());

              if(!query.exec())
              {
                  QMessageBox::critical(0,"Database error",query.lastError().text());
                  qDebug() << query.lastQuery();
              }
              else
              {
                  query.prepare("SELECT distraction FROM dist_list");
                  query.exec();
                  model->setQuery(query);
                  ui->listView_distraction->setModel(model);
              }
         }

}

void doro_manager::on_calendarWidget_selectionChanged()
{
    //WHEN DATE CHANGED SHOW TASK FOR SELECTED DATE
}

void doro_manager::on_removeDistButton_clicked()
{
    /*
     if(ui->listView_distraction->currentIndex().count() != 0)
    {
        int index[] = ui->listView_distraction->selectedIndexes();

        while (index[].next())
        {
            for(int i=0; i<=index[].length(); i++) {
                QSqlQueryModel *model = new QSqlQueryModel();
                QSqlQuery query;
                query.prepare("DELETE FROM dist_list(distraction) VALUES(:distItem)");
                query.bindValue(":distItem", i);

                if(!query.exec())
                {
                    QMessageBox::critical(0,"Database error",query.lastError().text());
                    qDebug() << query.lastQuery();
                }
                else
                {
                    query.prepare("SELECT distraction FROM dist_list");
                    query.exec();
                    model->setQuery(query);
                    ui->listView_distraction->setModel(model);
                }
            }
        }
    */
}
