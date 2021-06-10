#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QVBoxLayout>
#include <vector>
#include <QDebug>
#include <memory>

#include "Button.h"
#include "direction_t.h"

#define FLOORS 17
#define DOOR_SLEEP 700
#define MOVE_SLEEP 1100

class Controller : public QWidget
{
Q_OBJECT;

    enum controller_status
    {
        FREE,
        BUSY,
        NEW_TARGET
    };

public:
    explicit Controller(QWidget *parent = nullptr);

    ~Controller() = default;

public slots:
    void new_target(int floor); //NEW_TARGET
    void update_target(int floor); //BUSY
    void no_target(); //FREE

signals:
    void at_floor_signal(int);
    void no_target_signal();
    void target_setted(int, direction_t);

private:
    void update_direction();
    void update_direction_up();
    void update_direction_down();

private:
    controller_status status;
    direction_t direction;
    int current_floor;
    int target_floor;

    std::vector<std::shared_ptr<Button>> buttons;
    std::vector<bool> visited_floors;
    std::unique_ptr<QVBoxLayout> layout;
};

#endif
