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
    if (status == CLOSED || status == CLOSING)
    {
        qDebug() << "\t\tДвери - начинаю открывать";

        if (this->status == CLOSED)
        {
            this->status = OPENING;
            this->opening_timer.start(DOOR_SLEEP);
        }
        else
        {
            this->status = OPENING;
            auto timer = closing_timer.remainingTime();
            closing_timer.stop();
            this->opening_timer.start(DOOR_SLEEP - timer);
        }
    }
}

void Door::opened()
{
    if (status == OPENING)
    {
        this->status = OPEN;
        qDebug() << "\t\tДвери - открыты, можно выходить";
        this->opened_timer.start(DOOR_SLEEP);
    }
}

void Door::closing()
{
    if (status == OPEN)
    {
        this->status = CLOSING;
        qDebug() << "\t\tДвери - начинаю закрывать";
        this->closing_timer.start(DOOR_SLEEP);
    }
}

void Door::closed()
{
    if (status == CLOSING)
    {
        this->status = CLOSED;
        qDebug() << "\t\tДвери - закрыты, можно ехать";
        emit closed_signal();
    }
}
