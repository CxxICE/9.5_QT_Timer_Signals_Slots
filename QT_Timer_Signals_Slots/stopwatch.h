#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QObject>
#include <QTimer>

class StopWatch : public QObject
{
    Q_OBJECT
public:
    explicit StopWatch(QObject *parent = nullptr);
    void start();
    void stop();
    void reset();
    char *curTime();

signals:
   void sig_time(char* sendTime);
private slots:
    void setNewTime();

private:
    static constexpr int kInterval = 100;//интервал в миллисекундах
    QTimer *timer;
    char time[12];//00:00:00:00
};

#endif // STOPWATCH_H
