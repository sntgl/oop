#include "Lift.h"
#include <QPalette>

Lift::Lift(QObject *parent) : QObject(parent)
{
    this->controller.setStyleSheet("background-color:gray;");

    QObject::connect(&controller, SIGNAL(target_setted(ssize_t)), &cabin, SLOT(cabin_take_target(ssize_t)));
    QObject::connect(&cabin, SIGNAL(request_target(ssize_t)), &controller, SLOT(update_target(ssize_t)));


//    QObject::connect(&cabin, SIGNAL(free_signal()), &controller, SLOT(on_free()));
//    QObject::connect(&controller, SIGNAL(new_target_signal(ssize_t)), &cabin, SLOT(cabin_take_target(ssize_t)));
//    QObject::connect(&controller, SIGNAL(stopped_signal(bool, ssize_t)), &cabin, SLOT(cabin_stopped(bool, ssize_t)));
}

QWidget *Lift::widget()
{
    return &this->controller;
}
