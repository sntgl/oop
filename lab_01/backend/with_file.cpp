#include "with_file.h"


bool is_loaded(status_t &status)
{
    return status.loaded;
}

void set_saved_status(status_t &status, result_code_t rc)
{
    if (rc == ok)
        status.saved = true;
    else
        status.saved = false;
}

result_code_t read_point_from_stream(point_t &p, FILE *f)
{
    if (fscanf(f, "%f%f%f", &p.x, &p.y, &p.z) != 3)
        return error_read_file;
    else
        return ok;
}

result_code_t read_line_from_stream(line_t &l, FILE *f)
{
    if (fscanf(f, "%d%d", &l.p1, &l.p2) != 2)
        return error_read_file;
    else {
        l.p1--;
        l.p2--;
        return ok;
    }
}

result_code_t read_pos_int_from_stream(int &d, FILE *f)
{
    if (fscanf(f, "%d", &d) == 1 and d > 0)
        return ok;
    else
        return error_read_file;
}

result_code_t print_point_to_stream(point_t &point, FILE *f)
{
    if (fprintf(f, "%f %f %f\n", point.x, point.y, point.z) > 0)
        return ok;
    else
        return error_print_to_file;
}

result_code_t print_line_to_stream(line_t &line, FILE *f)
{
    if (fprintf(f, "%d %d\n", line.p1 + 1, line.p2 + 1) > 0)
        return ok;
    else
        return error_print_to_file;
}

result_code_t print_int_to_stream(int d, FILE *f)
{
    if (fprintf(f, "%d\n", d) > 0)
        return ok;
    else
        return error_print_to_file;
}

result_code_t load_center(point_t &center, FILE *f)
{
    return read_point_from_stream(center, f);
}

result_code_t load_points(point_t **points, int points_count, FILE *f)
{
    result_code_t rc = allocate_points(points, points_count);
    for (int i = 0; rc == ok and i < points_count; i++)
        rc = read_point_from_stream((*points)[i], f);
    if (rc != ok)
        free_points(points);
    return rc;
}

result_code_t load_lines(line_t **lines, int lines_count, FILE *f)
{
    result_code_t rc = allocate_lines(lines, lines_count);
    for (int i = 0; rc == ok and i < lines_count; i++)
        rc = read_line_from_stream((*lines)[i], f);
    if (rc != ok)
        free_lines(lines);
    return rc;
}


result_code_t load_lines_and_count(line_t **lines, int &lines_count, FILE *f)
{
    result_code_t rc = read_pos_int_from_stream(lines_count, f);
    if (rc == ok)
        rc = load_lines(lines, lines_count, f);
    return rc;
}


result_code_t load_points_and_count(point_t **points, int &points_count, FILE *f)
{
    result_code_t rc = read_pos_int_from_stream(points_count, f);
    if (rc == ok)
        rc = load_points(points, points_count, f);
    return rc;
}

result_code_t load_model_from_file(data_t &temp_d, FILE *f)
{
    result_code_t rc = load_center(temp_d.center, f);
    if (rc == ok)
        rc = load_points_and_count(&temp_d.points, temp_d.points_count, f);
    if (rc == ok) {
        rc = load_lines_and_count(&temp_d.lines, temp_d.lines_count, f);
        if (rc != ok)
            free_points(&temp_d.points);
    }
    return rc;
}


result_code_t print_lines_to_stream(line_t *lines, int lines_count, FILE *f)
{
    result_code_t rc = ok;
    for (int i = 0; rc == ok and i < lines_count; i++)
        rc = print_line_to_stream(lines[i], f);
    return rc;
}

result_code_t print_points_to_stream(point_t *points, int points_count, FILE *f)
{
    result_code_t rc = ok;
    for (int i = 0; rc == ok and i < points_count; i++)
        rc = print_point_to_stream(points[i], f);
    return rc;
}

result_code_t save_center(point_t &point, FILE *f)
{
    return print_point_to_stream(point, f);
}

result_code_t save_lines_and_count(line_t *lines, int lines_count, FILE *f)
{
    result_code_t rc = print_int_to_stream(lines_count, f);
    if (rc == ok)
        rc = print_lines_to_stream(lines, lines_count, f);
    return rc;
}


result_code_t save_points_and_count(point_t *points, int points_count, FILE *f)
{
    result_code_t rc;
    rc = print_int_to_stream(points_count, f);
    if (rc == ok)
        rc = print_points_to_stream(points, points_count, f);
    return rc;
}

result_code_t save_model_to_stream(data_t &d, FILE *f)
{
    result_code_t rc = save_center(d.center, f);
    if (rc == ok) {
        rc = save_points_and_count(d.points, d.points_count, f);
        if (rc == ok)
            rc = save_lines_and_count(d.lines, d.lines_count, f);
    }
    return rc;
}


void move_data(data_t &new_data, data_t &old_data)
{
    if (is_loaded(new_data.status))
        free_struct_allocates(new_data);
    new_data.status = old_data.status;
    new_data.lines_count = old_data.lines_count;
    new_data.points_count = old_data.points_count;
    new_data.center = old_data.center;
    new_data.lines = old_data.lines;
    new_data.points = old_data.points;
}


result_code_t validate_line(line_t &l, int points_count)
{
    result_code_t rc = ok;
    if (l.p1 >= points_count || l.p2 >= points_count)
        rc = error_broken_file;
    return rc;
}

result_code_t validate_lines(const data_t &d)
{
    result_code_t rc = ok;
    for (int i = 0; rc == ok and i < d.lines_count; ++i)
        rc = validate_line(d.lines[i], d.points_count);
    return rc;
}

result_code_t validate_load(data_t &d, result_code_t rc)
{
    rc = validate_lines(d);
    if (rc == ok) {
        d.status.loaded = true;
        d.status.saved = true;
    }
    return rc;
}



result_code_t load_data_from_file(data_t &d, char *file_name)
{
    result_code_t rc;
    FILE *f = fopen(file_name, "r");
    data_t temp_d = init_data();
    if (!f)
        rc = error_open_file;
    else {
        rc = load_model_from_file(temp_d, f);
        fclose(f);
    }
    if (rc == ok) {
        rc = validate_load(temp_d, rc);
        if (rc == ok)
            move_data(d, temp_d);
        else
            free_struct_allocates(temp_d);
    }
    return rc;
}

result_code_t save_data_to_file(data_t &d, char *file_name)
{
    if (!is_loaded(d.status))
        return error_empty_save;
    result_code_t rc;
    FILE *f = fopen(file_name, "w");
    if (!f)
        rc = error_save_file;
    else {
        rc = save_model_to_stream(d, f);
        fclose(f);
    }
    set_saved_status(d.status, rc);
    return rc;
}

