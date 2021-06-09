#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include <QTimer>

class Door : public QObject
{
Q_OBJECT;

private:
    enum door_status
    {
        OPEN,
        OPENING,
        CLOSING,
        CLOSED
    };

public:
    Door();
    ~Door() = default;

public slots:

    void opened();
    void closed();

private slots:
    void opening();
    void closing();

signals:
    void closed_signal();

private:
    door_status status;

    QTimer opening_timer;
    QTimer closing_timer;
    QTimer opened_timer;
};

#endif
