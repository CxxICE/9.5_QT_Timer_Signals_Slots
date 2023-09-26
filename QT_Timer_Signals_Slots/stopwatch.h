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
    void newLap(char* returnLapTime);

signals:
   void sig_time(char* sendTime, char* sendLapTime);
private slots:
    void setNewTime();

private:
    void calculateTime(char* oldTime);
    static constexpr int kInterval = 100;//интервал в миллисекундах
    QTimer *timer;
    char time[12];//00:00:00.00
    char lapTime[12];//00:00:00.00
};

#endif // STOPWATCH_H
