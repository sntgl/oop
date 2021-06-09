#include "Controller.h"

#include <QDebug>
#include <memory>

Controller::Controller(QWidget *parent) : QWidget(parent)
{
    this->layout = std::make_unique<QVBoxLayout>();
    this->setLayout(this->layout.get());
    status = FREE;
    QObject::connect(this, SIGNAL(no_target_signal()), this, SLOT(no_target()));
    QObject::connect(this, SIGNAL(at_floor_signal(ssize_t)), this, SLOT(update_target(ssize_t)));



//    display = std::shared_ptr<Display>(new Display);
//    layout->addWidget(dynamic_cast<QLabel *>(display.get()));
//    QObject::connect(this, SIGNAL(passed_floor_signal(ssize_t, direction_t)), display.get(),
//                     SLOT(passed_floor(ssize_t, direction_t)));
//    QObject::connect(this, SIGNAL(stopped_signal(bool, ssize_t)), display.get(), SLOT(stop()));
//    QObject::connect(this, SIGNAL(free_signal()), display.get(), SLOT(on_free()));


    for (int i = 0; i < FLOORS; i++) {
        std::shared_ptr<Button> btn(new Button);
        btn->set_floor(FLOORS - i);
        btn->setText(QString::number(FLOORS - i));

        buttons.insert(buttons.begin(), btn);
        layout->addWidget(dynamic_cast<QPushButton *>(btn.get()));

        visited_floors.push_back(true);
        QObject::connect(btn.get(), SIGNAL(floor_pressed(ssize_t)), this, SLOT(new_target(ssize_t)));
    }
}

void Controller::new_target(ssize_t floor)
{
    qDebug() << "Контроллер получил новый этаж - " << floor;
    controller_status old_status = status;
    status = NEW_TARGET;
    visited_floors[floor - 1] = false;
//    target_exist(floor);
//    this->needed_floor = floor;
    if (old_status == FREE)
        emit at_floor_signal(current_floor + 1);
}

void Controller::update_target(ssize_t floor)
{
    qDebug() << "Контроллер обновляет этаж";
    controller_status old_status = status;
    status = BUSY;
    current_floor = floor;
    if (current_floor == next_target || old_status != BUSY) {
        if (current_floor == next_target) {
            emit this->buttons.at(floor - 1)->unpress_signal();
            visited_floors[floor - 1] = true;
        }
        if (direction != DOWN)
        {
            direction = STOP;
            for (next_target = current_floor; next_target <= FLOORS; ++next_target)
                if (!visited_floors[next_target - 1])
                {
                    direction = UP;
                    break;
                }
        }
        if (direction != UP)
        {
            direction = STOP;
            for (next_target = current_floor - 1; next_target > 0; --next_target)
                if (!visited_floors[next_target - 1])
                {
                    direction = DOWN;
                    break;
                }
        }
    }
    if (direction == STOP)
        emit no_target_signal();
    else
        emit target_setted(next_target);
//    else
//        emit


//    if (status == BUSY) {
//        this->current_floor = floor;
//        this->direction = direction_;
//        emit passed_floor_signal(floor, direction);
//
//        if (current_floor == needed_floor) {
//            qDebug() << "Лифт остановился на этаже: " << floor;
//
//            emit this->buttons.at(floor - 1)->unpress_signal();
//            this->visited_floors[floor - 1] = true;
//
//            if (target_exist(floor)) {
//                this->needed_floor = floor;
//                emit stopped_signal(false, floor);
//            } else {
//                this->status = FREE;
//                emit stopped_signal(true);
//            }
//        }
//    }
}


//bool Controller::target_exist(ssize_t &new_floor)
//{
//    int direction = direction != STOP ? direction : DOWN;
//
//    for (int i = current_floor - 1; i >= 0 && i < FLOORS; i += direction) {
//        if (!visited_floors[i]) {
//            new_floor = i + 1;
//            return true;
//        }
//    }
//
//    for (int i = current_floor - 1; i >= 0 && i < FLOORS; i += -direction) {
//        if (!visited_floors[i]) {
//            new_floor = i + 1;
//            return true;
//        }
//    }
//
//    return false;
//}

void Controller::no_target()
{
    status = FREE;
    qDebug() << "Контроллер бездействует";
}

//void Controller::on_free()
//{
//    status = ENDS;
//    emit free_signal();
//}
