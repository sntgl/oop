#include "with_memory.h"


void free_points(point_t **data)
{
    delete[] (*data);
    *data = nullptr;
}

void free_2d_points(point2d_t **data)
{
    delete[] (*data);
    *data = nullptr;
}

void free_struct_allocates(data_t &d)
{
    free_lines(&d.lines);
    free_points(&d.points);
}

void free_struct_allocates(draw_data_t &d)
{
    free_lines(&d.lines);
    free_2d_points(&d.points);
}

void free_lines(line_t **data)
{
    delete[] (*data);
    *data = nullptr;
}


void free_struct_allocates(data_t &d, draw_data_t draw_data)
{
    free_struct_allocates(draw_data);
    free_struct_allocates(d);
}

result_code_t allocate_points2d(point2d_t **points, int count)
{
    result_code_t rc = ok;
    *points = new point2d_t[count];
    if (!*points) {
        *points = nullptr;
        rc = error_allocate_memory;
    }
    return rc;
}

result_code_t allocate_points(point_t **points, int count)
{
    result_code_t rc = ok;
    *points = (point_t *) calloc(count, sizeof(point_t));
    if (!*points) {
        *points = nullptr;
        rc = error_allocate_memory;
    }
    return rc;
}

result_code_t allocate_lines(line_t **lines, int count)
{
    result_code_t rc = ok;
    *lines = new line_t[count];
    if (!*lines) {
        *lines = nullptr;
        rc = error_allocate_memory;
    }
    return rc;
}


result_code_t allocate_draw_data(draw_data_t &draw_data)
{
    result_code_t rc;
    rc = allocate_lines(&draw_data.lines, draw_data.lines_count);
    if (rc == ok) {
        rc = allocate_points2d(&draw_data.points, draw_data.points_count);
        if (rc != ok)
            free_lines(&draw_data.lines);
    }
    return rc;
}


