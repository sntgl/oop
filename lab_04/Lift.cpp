#include "Lift.h"
#include <QPalette>

Lift::Lift(QObject *parent) : QObject(parent)
{
    this->controller.setStyleSheet("background-color:gray;");

    QObject::connect(&controller, SIGNAL(target_setted(int, direction_t)), &cabin, SLOT(cabin_take_target(int, direction_t)));
    QObject::connect(&cabin, SIGNAL(request_target(int)), &controller, SLOT(update_target(int)));
}

QWidget *Lift::widget()
{
    return &this->controller;
}
