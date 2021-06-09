#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QObject>

class Button : public QPushButton
{
Q_OBJECT;

    enum button_status
    {
        PRESSED,
        UNPRESSED,
    };

public:
    Button(QWidget *parent = nullptr);
    ~Button() = default;

    void set_floor(const ssize_t &floor);

public slots:

    void pressed();
    void unpressed();

signals:

    void floor_pressed(ssize_t floor);
    void unpress_signal();

private:
    button_status status;
    ssize_t button_floor;
};

#endif
