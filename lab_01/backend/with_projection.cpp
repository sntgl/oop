#include "with_points.h"
#include "with_file.h"
#include "with_projection.h"

void update_line(line_t &l1, line_t &l2) {
    l1.p1 = l2.p1;
    l1.p2 = l2.p2;
}

void update_point(point_t &p, point2d_t &p2d) {
    p2d.x = p.x;
    p2d.y = p.y;
}

void update_projection_lines(data_t &d, draw_data_t &draw_data) {
    for (int i = 0; i < draw_data.lines_count; ++i)
        update_line(draw_data.lines[i], d.lines[i]);
}


void update_projection_points(data_t &d, draw_data_t &draw_data, action_t action) {
    draw_data.status = d.status;
    if (action != action_save and action != action_exit and d.status.loaded) {
        update_point(d.center, draw_data.center);
        for (int i = 0; i < d.points_count; ++i)
            update_point(d.points[i], draw_data.points[i]);
    }
}

void move_draw_data(draw_data_t &old_data, draw_data_t &new_data) {
    new_data.status = old_data.status;
    new_data.lines_count = old_data.lines_count;
    new_data.points_count = old_data.points_count;
    new_data.center = old_data.center;
    if (new_data.status.loaded)
        free_struct_allocates(new_data);
    new_data.lines = old_data.lines;
    new_data.points = old_data.points;
}

draw_data_t init_draw_data(data_t &d) {
    draw_data_t draw_data;
    draw_data.status = d.status;
    draw_data.lines_count = d.lines_count;
    draw_data.points_count = d.points_count;
    return draw_data;
}

result_code_t create_draw_data(data_t &d, draw_data_t &draw_data) {
    result_code_t rc;
    draw_data_t temp_draw_data = init_draw_data(d);
    update_point(d.center, temp_draw_data.center);
    rc = allocate_draw_data(temp_draw_data);
    if (rc == ok) {
        update_projection_lines(d, temp_draw_data);
        move_draw_data(temp_draw_data, draw_data);
    }
    return rc;
}
