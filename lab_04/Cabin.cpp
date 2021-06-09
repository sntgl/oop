#include "Cabin.h"

Cabin::Cabin(QObject *parent)
{
    this->status = FREE;
    this->current_floor = 1;
    this->need_floor = 1;
    this->direction = STOP;


    QObject::connect(&move_timer, SIGNAL(timeout()), this, SLOT(cabin_stopped()));
    QObject::connect(&door, SIGNAL(closed_signal()), this, SLOT(cabin_free()));
    QObject::connect(this, SIGNAL(stop_cabin()), this, SLOT(cabin_stopped()));
    QObject::connect(this, SIGNAL(moving_signal()), this, SLOT(cabin_moving()));
    QObject::connect(this, SIGNAL(free_signal()), this, SLOT(cabin_free()));
    QObject::connect(this, SIGNAL(open_doors_signal()), &door, SLOT(opening()));

}

void Cabin::cabin_moving()
{
    status = MOVING;
    qDebug() << "\tКабина направляется на " << need_floor << " этаж";
    move_timer.start(MOVE_SLEEP);
}

void Cabin::cabin_stopped()
{
    qDebug() << "\tКабина ждет двери";
    status = WAITING_DOORS;
    move_timer.stop();
    current_floor += direction;
    if (current_floor != need_floor) {
        emit free_signal();
    } else {
        emit open_doors_signal();
    }
}

void Cabin::cabin_take_target(ssize_t floor)
{
    status = GET;
    need_floor = floor;
    direction = STOP;
    qDebug() << "\tКабина получила таргет этаж - " << floor;
    if (current_floor == need_floor) {
        emit stop_cabin();
    } else {
        direction = need_floor > current_floor ? UP : DOWN;
        emit moving_signal();
    }
}

void Cabin::cabin_free()
{
    qDebug() << "\tКабина завершила цикл - этаж " << current_floor;
    status = FREE;
    emit request_target(current_floor);
}

