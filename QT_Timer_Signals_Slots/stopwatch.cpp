#include "stopwatch.h"

StopWatch::StopWatch(QObject *parent)
    : QObject{parent}
{
    strcpy(time, "00:00:00.00");
    strcpy(lapTime, "00:00:00.00");
    timer = new QTimer(this);
    timer->setInterval(kInterval);
    QObject::connect(timer, &QTimer::timeout, this, &StopWatch::setNewTime, Qt::AutoConnection);
}

void StopWatch::start()
{
    timer->start();
}

void StopWatch::stop()
{
    timer->stop();
}

void StopWatch::reset()
{
    strcpy(time, "00:00:00.00");
    strcpy(lapTime, "00:00:00.00");
    emit sig_time(time, lapTime);
}

void StopWatch::newLap(char* returnLapTime)
{
    strcpy(returnLapTime, lapTime);
    strcpy(lapTime, "00:00:00.00");
}

void StopWatch::setNewTime()
{
    if (kInterval >= 86'400'000)
    {
        strcpy(time, "00:00:00.00");//заглушка, если случайно задана константа более суток в определении класса
    }
    else
    {
        calculateTime(time);
        calculateTime(lapTime);
    }
    emit sig_time(time, lapTime);
}

void StopWatch::calculateTime(char* oldTime)
{
    char tmp[3] = "00";
    tmp[0] = oldTime[0];
    tmp[1] = oldTime[1];
    int hour = atoi(tmp);
    tmp[0] = oldTime[3];
    tmp[1] = oldTime[4];
    int min = atoi(tmp);
    tmp[0] = oldTime[6];
    tmp[1] = oldTime[7];
    int sec = atoi(tmp);
    tmp[0] = oldTime[9];
    tmp[1] = oldTime[10];
    int msec = atoi(tmp) * 10;

    constexpr int add_hour = kInterval/3'600'000;
    constexpr int add_min = kInterval/60'000 - add_hour * 60;
    constexpr int add_sec = kInterval/1000 - (add_hour * 3'600 + add_min * 60);
    constexpr int add_msec = kInterval - (add_hour * 3'600'000 + add_min * 60'000 + add_sec * 1'000);

    msec += add_msec;
    if (msec >= 1000)
    {
        sec += 1;
        msec %= 1000;
    }

    sec += add_sec;
    if (sec >= 60)
    {
        min += 1;
        sec %= 60;
    }

    min += add_min;
    if (min >= 60)
    {
        hour += 1;
        min %= 60;
    }

    hour += add_hour;
    if (hour >= 24)
    {
        hour = 0;
    }

    oldTime[0] = '0' + hour / 10;
    oldTime[1] = '0' + hour % 10;

    oldTime[3] = '0' + min / 10;
    oldTime[4] = '0' + min % 10;

    oldTime[6] = '0' + sec / 10;
    oldTime[7] = '0' + sec % 10;

    oldTime[9] = '0' + msec / 100;
    oldTime[10] = '0' + (msec % 100) / 10;
}
