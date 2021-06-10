#include "Controller.h"

#include <QDebug>
#include <memory>

Controller::Controller(QWidget *parent) : QWidget(parent)
{
    current_floor = 1;
    target_floor = 0;
    status = FREE;

    this->layout = std::make_unique<QVBoxLayout>();
    this->setLayout(this->layout.get());
    QObject::connect(this, SIGNAL(no_target_signal()), this, SLOT(no_target()));
    QObject::connect(this, SIGNAL(at_floor_signal(int)), this, SLOT(update_target(int)));

    for (int i = 0; i < FLOORS; i++) {
        std::shared_ptr<Button> btn(new Button);
        btn->set_floor(FLOORS - i);
        btn->setText(QString::number(FLOORS - i));

        buttons.insert(buttons.begin(), btn);
        layout->addWidget(dynamic_cast<QPushButton *>(btn.get()));

        visited_floors.push_back(true);
        QObject::connect(btn.get(), SIGNAL(floor_pressed(int)), this, SLOT(new_target(int)));
    }
}

void Controller::new_target(int floor)
{
    controller_status old_status = status;
    status = NEW_TARGET;
    visited_floors[floor - 1] = false;
    if (old_status == FREE)
        emit at_floor_signal(current_floor);
}

void Controller::update_target(int floor)
{
    if (status != FREE) {
        current_floor = floor;
        if (current_floor == target_floor || status != BUSY) {
            if (current_floor == target_floor) {
                emit this->buttons.at(floor - 1)->unpress_signal();
                visited_floors[floor - 1] = true;
            }
            update_direction();
        }
        status = BUSY;
        if (direction == STOP)
            emit no_target_signal();
        else {
            if (target_floor == current_floor)
                direction = STOP;
            emit target_setted(target_floor, direction);
        }
    }
}

void Controller::no_target()
{
    if (status != FREE) {
        status = FREE;
        target_floor = 0;
        qDebug() << "Лифт бездействует";
    }
}

void Controller::update_direction()
{
    direction_t old_direction = direction;
    direction = STOP;
    if (old_direction != UP)
    {
        update_direction_down();
        if (direction == STOP)
            update_direction_up();
    } else {
        update_direction_up();
        if (direction == STOP)
            update_direction_down();
    }

}

void Controller::update_direction_up()
{
    for (target_floor = current_floor; target_floor <= FLOORS; ++target_floor)
        if (!visited_floors[target_floor - 1])
        {
            direction = UP;
            break;
        }
}

void Controller::update_direction_down()
{
    for (target_floor = current_floor - 1; target_floor > 0; --target_floor)
        if (!visited_floors[target_floor - 1])
        {
            direction = DOWN;
            break;
        }
}
