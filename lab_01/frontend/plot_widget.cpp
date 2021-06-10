#include "plot_widget.h"

#include <QMessageBox>


PlotWidget::PlotWidget(QWidget *parent)
{
    draw_data.status.loaded = false;
    draw_data.status.saved = true;
    editions_data.scale_percent = 0;
    draw_data.lines = nullptr;
    draw_data.points = nullptr;
    clean_buttons();
    PlotWidget::grabKeyboard();
}

void PlotWidget::clean_buttons()
{
    buttons_status.mouse_pressed = false;
    buttons_status.space_pressed = false;
    buttons_status.control_pressed = false;
    this->setCursor(QCursor(Qt::ArrowCursor));
}

void PlotWidget::wheelEvent(QWheelEvent *event)
{
    editions_data.scale_percent = event->angleDelta().y();
    editions_data.action = action_scale;
    toBackend();
    repaint();
}

void PlotWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (buttons_status.mouse_pressed)
    {
        QPointF point = event->position();
        editions_data.point_previous.x = editions_data.point_actual.x;
        editions_data.point_previous.y = editions_data.point_actual.y;
        editions_data.point_actual.x = point.x();
        editions_data.point_actual.y = point.y();
        if (buttons_status.space_pressed || buttons_status.control_pressed)
        {
            editions_data.action = action_move;
            editions_data.need_to_move_center = buttons_status.space_pressed;
        }
        else
            editions_data.action = action_rotate;
        toBackend();
        repaint();
    }
}

void PlotWidget::mousePressEvent(QMouseEvent *event)
{
    QPointF point = event->position();
    editions_data.point_actual.x = point.x();
    editions_data.point_actual.y = point.y();
    buttons_status.mouse_pressed = true;
    if (buttons_status.space_pressed)
        this->setCursor(QCursor(Qt::ClosedHandCursor));
    else
        this->setCursor(QCursor(Qt::SizeAllCursor));
}

void PlotWidget::mouseReleaseEvent(QMouseEvent *event)
{
    buttons_status.mouse_pressed = false;
    repaint();
    this->setCursor(QCursor(Qt::ArrowCursor));
}

void PlotWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space or event->key() == Qt::Key_Control)
    {
        if (event->key() == Qt::Key_Space)
            buttons_status.space_pressed = true;
        else
            buttons_status.control_pressed = true;
        this->setCursor(QCursor(Qt::ClosedHandCursor));
    }
}

void PlotWidget::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space or event->key() == Qt::Key_Control)
    {
        if (event->key() == Qt::Key_Space)
            buttons_status.space_pressed = false;
        else
            buttons_status.control_pressed = false;
        if (buttons_status.mouse_pressed)
            this->setCursor(QCursor(Qt::SizeAllCursor));
        else
            this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

bool PlotWidget::getSaved()
{
    return draw_data.status.saved;
}

void PlotWidget::fileEvent(file_action action, char *str)
{
    clean_buttons();
    editions_data.file_name = strdup(str);
    if (action == file_open)
        editions_data.action = action_load;
    else
        editions_data.action = action_save;
    toBackend();
    repaint();
}


void PlotWidget::fileEvent()
{
    clean_buttons();
    editions_data.action = action_save;
    toBackend();
    repaint();
}

void PlotWidget::paint_lines()
{
    for (int i = 0; i < draw_data.lines_count; ++i)
    {
        QPoint p1 = QPoint(draw_data.points[draw_data.lines[i].p1].x, draw_data.points[draw_data.lines[i].p1].y);
        QPoint p2 = QPoint(draw_data.points[draw_data.lines[i].p2].x, draw_data.points[draw_data.lines[i].p2].y);
        painter.drawLine(p1, p2);
    }
}

void PlotWidget::paint_points()
{
    for (int i = 0; i < draw_data.points_count; ++i)
    {
        QPoint p1 = QPoint(draw_data.points[i].x, draw_data.points[i].y);
        painter.drawEllipse(p1, 1, 1);
    }
}

void PlotWidget::paint_center()
{
    QPen pen(Qt::red, 4);
    painter.setPen(pen);
    QPoint p = QPoint(draw_data.center.x, draw_data.center.y);
    painter.drawEllipse(p, 1, 1);
}


void PlotWidget::paint_figure()
{
    if (!draw_data.status.loaded)
        return;
    paint_lines();
    paint_points();
    paint_center();
}

void PlotWidget::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
    painter.translate(size().width() / 2, size().height() / 2);
    paint_figure();
    painter.end();
}

void PlotWidget::toBackend()
{
    editions_data.angle_y = float (editions_data.point_actual.y - editions_data.point_previous.y) * M_PI / 180.0;
    editions_data.angle_x = - float (editions_data.point_actual.x - editions_data.point_previous.x) * M_PI / 180.0;
    editions_data.delta_x = editions_data.point_actual.x - editions_data.point_previous.x;
    editions_data.delta_y =  editions_data.point_actual.y - editions_data.point_previous.y;
    result_code_t rc = backend(draw_data, editions_data);
    handle_error(rc);
    if (rc == ok and editions_data.action == action_load) {
        editions_data.action = action_load_projection;
        toBackend();
    }
}

void PlotWidget::closeEvent(QCloseEvent *event)
{
    editions_data.action = action_exit;
    toBackend();
}
