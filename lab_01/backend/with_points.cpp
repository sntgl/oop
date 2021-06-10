#include "with_points.h"

void set_edited_status(status_t &status, result_code_t rc)
{
    if (rc == ok)
        status.saved = false;
    else
        status.saved = true;
}

void apply_matrix_to_points_and_center(matrix_t &m, data_t &d, bool need_to_move_center)
{
    vector_t buffer;
    apply_matrix_to_points_add_buffer(d.points, d.points_count, buffer, m);
    apply_matrix_to_center_add_buffer(d.center, buffer, m, need_to_move_center);
}

result_code_t do_move(data_t &d, bool need_to_move_center, float edition_x, float edition_y)
{
    result_code_t rc = ok;
    if (!d.status.loaded)
        rc = error_empty_edit;
    if (rc == ok) {
        matrix_t edition_matrix = create_move_matrix(edition_x, edition_y);
        apply_matrix_to_points_and_center(edition_matrix, d, need_to_move_center);
    }
    set_edited_status(d.status, rc);
    return rc;
}

result_code_t do_scale(data_t &d, float scale_percent)
{
    result_code_t rc = ok;
    if (!d.status.loaded)
        rc = error_empty_edit;
    if (rc == ok) {
        matrix_t edition_matrix = create_scale_matrix(d.center, scale_percent);
        apply_matrix_to_points_and_center(edition_matrix, d, true);
    }
    set_edited_status(d.status, rc);
    return rc;
}

result_code_t do_rotate(data_t &d, float angle_x, float angle_y)
{
    result_code_t rc = ok;
    if (!d.status.loaded)
        rc = error_empty_edit;
    else {
        matrix_t edition_matrix = create_rotate_matrix(d.center, angle_x, angle_y);
        apply_matrix_to_points_and_center(edition_matrix, d, false);
    }
    set_edited_status(d.status, rc);
    return rc;
}
