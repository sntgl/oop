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

    void set_floor(const int &floor);

public slots:
    void pressed();
    void unpressed();

signals:
    void floor_pressed(int floor);
    void unpress_signal();

private:
    button_status status;
    int button_floor;
};

#endif
