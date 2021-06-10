#ifndef CABIN_H
#define CABIN_H

#include <QObject>
#include <QDebug>
#include "Door.h"
#include "Controller.h"

class Cabin : public QObject
{
Q_OBJECT;

    enum cabin_status
    {
        GET,
        MOVING,
        WAITING_DOORS,
        FREE
    };

public:
    explicit Cabin(QObject *parent = nullptr);
    ~Cabin() = default;

public slots:

    void cabin_take_target(int floor, direction_t direction_); //GET
    void cabin_moving(); //MOVING
    void cabin_stopped(); //WAITING_DOORS
    void cabin_free(); //FREE

signals:

    void open_doors_signal();
    void request_target(int floor);
    void moving_signal();
    void stop_cabin();
    void free_signal();

private:
    int current_floor;
    int need_floor;

    direction_t direction;
    cabin_status status;

    Door door;
    QTimer move_timer;
};

#endif
