#include "Button.h"

Button::Button(QWidget *parrent) : QPushButton(parrent)
{
    QObject::connect(this, SIGNAL(clicked()), this, SLOT(pressed()));
    QObject::connect(this, SIGNAL(unpress_signal()), this, SLOT(unpressed()));

    this->status = UNPRESSED;
    this->button_floor = 1;
}

void Button::set_floor(const int &floor)
{
    this->button_floor = floor;
}

void Button::pressed()
{
    if (status == UNPRESSED) {
        this->setStyleSheet("background-color:cyan;");
        this->update();

        this->status = PRESSED;
        this->setDisabled(true);
        emit floor_pressed(this->button_floor);
    }
}

void Button::unpressed()
{
    if (status == PRESSED) {
        this->setStyleSheet("background-color:gray;");
        this->update();
        this->status = UNPRESSED;
        this->setDisabled(false);
    }
}
