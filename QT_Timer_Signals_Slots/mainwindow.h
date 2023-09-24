#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDir>
#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_start_clicked();
    void on_pb_clear_clicked();
    void on_pb_lap_clicked();
    void getTime(char *receiveTime);

private:
    Ui::MainWindow *ui;
    StopWatch *watch;
    int lap;
};
#endif // MAINWINDOW_H
