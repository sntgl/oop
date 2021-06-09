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
        FREE,
        MOVING,
        WAITING_DOORS
    };

public:
    explicit Cabin(QObject *parent = nullptr);

    ~Cabin() = default;

public slots:

    void cabin_moving(); //MOVING
    void cabin_take_target(ssize_t floor); //GET
    void cabin_stopped(); //WAITING_DOORS
    void cabin_free(); //FREE

signals:

    void open_doors_signal();
    void request_target(ssize_t floor);

signals:
    void moving_signal();
    void stop_cabin();
    void moved_signal(ssize_t floor);
    void stopped_signal(bool = true, ssize_t = 1);
    void free_signal();

private:
    Door door;
    ssize_t current_floor;
    ssize_t need_floor;

    direction_t direction;
    cabin_status status;

    QTimer move_timer;


private:
    void move_if_need();
};

#endif
