#include "stopwatch.h"

StopWatch::StopWatch(QObject *parent)
    : QObject{parent}
{
    strcpy(time, "00:00:00:00");
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
    strcpy(time, "00:00:00:00");
    emit sig_time(time);
}

char *StopWatch::curTime()
{
    return time;
}

void StopWatch::setNewTime()
{
    if (kInterval >= 86'400'000)
    {
        strcpy(time, "00:00:00:00");//заглушка, если случайно задана константа более суток в определении класса
    }
    else
    {
        char tmp[3] = "00";
        tmp[0] = time[0];
        tmp[1] = time[1];
        int hour = atoi(tmp);
        tmp[0] = time[3];
        tmp[1] = time[4];
        int min = atoi(tmp);
        tmp[0] = time[6];
        tmp[1] = time[7];
        int sec = atoi(tmp);
        tmp[0] = time[9];
        tmp[1] = time[10];
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

        time[0] = '0' + hour / 10;
        time[1] = '0' + hour % 10;

        time[3] = '0' + min / 10;
        time[4] = '0' + min % 10;

        time[6] = '0' + sec / 10;
        time[7] = '0' + sec % 10;

        time[9] = '0' + msec / 100;
        time[10] = '0' + (msec % 100) / 10;
    }
    emit sig_time(time);
}
