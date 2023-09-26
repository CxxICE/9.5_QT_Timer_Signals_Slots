#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags( windowFlags() | Qt::WindowMaximizeButtonHint );
    QPalette pal;
    pal.setColor(ui->l_lap_time->foregroundRole(), QColor(62,41,247,100));
    ui->l_lap_time->setPalette(pal);
    //ui->tb_laps->setTextColor(QColor(62,41,247,100));
    setWindowIcon(QIcon(":/window/img/timer_32px.ico"));
    watch = new StopWatch(this);
    lap = 0;
    QObject::connect(watch, &StopWatch::sig_time, this, &MainWindow::getTime, Qt::AutoConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_start_clicked()
{
    if(ui->pb_start->text() == "Старт")
    {
        watch->start();
        ui->pb_start->setText("Стоп");
        ui->pb_lap->setEnabled(true);
    }
    else
    {
        watch->stop();
        ui->pb_start->setText("Старт");
        ui->pb_lap->setEnabled(false);
    }
}


void MainWindow::on_pb_clear_clicked()
{
    ui->tb_laps->clear();
    watch->reset();
    lap = 0;
}


void MainWindow::on_pb_lap_clicked()
{
    ++lap;
    QString tmp = "Круг ";
    tmp += QString::number(lap);
    tmp += ", время: ";
    char lapTime[12] = "00:00:00.00";
    watch->newLap(lapTime);
    tmp += lapTime;
    ui->tb_laps->append(tmp);
}

void MainWindow::getTime(char *receiveTime, char *receiveLapTime)
{
    ui->l_time->setText(receiveTime);
    ui->l_lap_time->setText(receiveLapTime);
}

