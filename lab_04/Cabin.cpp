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
    if (status == GET) {
        status = MOVING;
        qDebug() << "Лифт едет" << ((direction == UP) ? "наверх" : "вниз");
        move_timer.start(MOVE_SLEEP);
    }
}

void Cabin::cabin_stopped()
{
    if (status == MOVING || status == GET) {
        status = WAITING_DOORS;
        move_timer.stop();
        current_floor += direction;
        qDebug() << "Лифт на" << current_floor << "этаже";
        if (current_floor != need_floor)
            emit free_signal();
        else
            emit open_doors_signal();
    }
}

void Cabin::cabin_take_target(int floor, direction_t direction_)
{
    status = GET;
    need_floor = floor;
    direction = direction_;
    if (current_floor == need_floor)
        emit stop_cabin();
    else
        emit moving_signal();
}

void Cabin::cabin_free()
{
    if (status != FREE) {
        status = FREE;
        emit request_target(current_floor);
    }
}

