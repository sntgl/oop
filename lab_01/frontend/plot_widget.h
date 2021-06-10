#pragma once

#include <QWidget>
#include <QPainter>
#include <QPen>

#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QFileDialog>
#include <stdio.h>

#include "../backend/types.h"
#include "../backend/backend.h"
#include "error_handler.h"

typedef enum
{
    file_open,
    file_save,
    file_save_as
} file_action;

typedef struct
{
    bool mouse_pressed;
    bool space_pressed;
    bool control_pressed;
} buttons_status_t;

class PlotWidget : public QWidget
{
Q_OBJECT

public:
    PlotWidget(QWidget *parent);

    void fileEvent(file_action action, char *str);

    void fileEvent();

    bool getSaved();

private:
    QPainter painter;
//    data_t data;
    editions_data_t editions_data;
    buttons_status_t buttons_status;
    draw_data_t draw_data;

    void paint_lines();

    void paint_points();

    void paint_center();

    void paintEvent(QPaintEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

    void paint_figure();

    void clean_buttons();

    void toBackend();
};
