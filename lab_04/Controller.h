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
    void new_target(ssize_t floor); //NEW_TARGET
    void update_target(ssize_t floor); //BUSY
    void no_target();
//    void on_free(); //ENDS

signals:
    void at_floor_signal(ssize_t);
    void no_target_signal();
    void target_setted(ssize_t);
//    void new_target_signal(ssize_t floor);
//    void stopped_signal(bool, ssize_t = 1);
//    void passed_floor_signal(ssize_t floor, direction_t direction_);
//    void free_signal();


private:
    controller_status status;
    direction_t direction;
    int current_floor{};
    int needed_floor{};
    int next_target;

    std::vector<std::shared_ptr<Button>> buttons;
    std::vector<bool> visited_floors;
    std::unique_ptr<QVBoxLayout> layout;
//    std::shared_ptr<Display> display;

    bool target_exist(ssize_t &new_floor);
};

#endif
