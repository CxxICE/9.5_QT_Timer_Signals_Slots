#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags( windowFlags() | Qt::WindowMaximizeButtonHint );
#ifdef QT_DEBUG
    setWindowIcon(QIcon("../timer_32px.ico"));
#elif
    QString path = QDir::currentPath();
    setWindowIcon(QIcon(path + "/timer_32px.ico"));
#endif
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
    tmp += watch->curTime();
    ui->tb_laps->append(tmp);
}

void MainWindow::getTime(char *receiveTime)
{
    ui->l_time->setText(receiveTime);
}

