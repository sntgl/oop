#ifndef LIFT_H
#define LIFT_H

#include <QObject>

#include "Controller.h"
#include "Cabin.h"

class Lift : public QObject
{
Q_OBJECT;
public:
    explicit Lift(QObject *parent = nullptr);
    ~Lift() = default;

    QWidget *widget();

private:
    Controller controller;
    Cabin cabin;
};

#endif
