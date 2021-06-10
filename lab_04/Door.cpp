#include "Door.h"
#include "Controller.h"

Door::Door()
{
    this->status = CLOSED;

    QObject::connect(&opening_timer, SIGNAL(timeout()), this, SLOT(opened()));
    QObject::connect(&opened_timer,  SIGNAL(timeout()), this, SLOT(closing()));
    QObject::connect(&closing_timer, SIGNAL(timeout()), this, SLOT(closed()));
}

void Door::opening()
{
    if (status == CLOSED)
    {
        qDebug() << "\t\tДвери - начинаю открывать";

        if (status == CLOSED)
        {
            status = OPENING;
            opening_timer.start(DOOR_SLEEP);
        }
        else
        {
            status = OPENING;
            auto timer = closing_timer.remainingTime();
            closing_timer.stop();
            opening_timer.start(DOOR_SLEEP - timer);
        }
    }
}

void Door::opened()
{
    if (status == OPENING)
    {
        status = OPEN;
        qDebug() << "\t\tДвери - открыты, можно выходить";
        opened_timer.start(DOOR_SLEEP);
    }
}

void Door::closing()
{
    if (status == OPEN)
    {
        status = CLOSING;
        qDebug() << "\t\tДвери - начинаю закрывать";
        closing_timer.start(DOOR_SLEEP);
    }
}

void Door::closed()
{
    if (status == CLOSING)
    {
        status = CLOSED;
        qDebug() << "\t\tДвери - закрыты, можно ехать";
        emit closed_signal();
    }
}
