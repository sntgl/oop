#include "with_matrix.h"

matrix_t new_identity_matrix()
{
    return matrix_t{{
                            {1, 0, 0, 0},
                            {0, 1, 0, 0},
                            {0, 0, 1, 0},
                            {0, 0, 0, 1}}
    };
}

//запишет результат в первую матрицу
void composition(matrix_t &m1, matrix_t &m2)
{
    matrix_t temp;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            temp.data[i][j] = 0;
            for (int k = 0; k < 4; ++k)
                temp.data[i][j] += m1.data[i][k] * m2.data[k][j];
        }
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m1.data[i][j] = temp.data[i][j];
}

//запишет результат в вектор
void composition(matrix_t &m, vector_t &v)
{
    vector_t temp;
    for (int i = 0; i < 4; ++i) {
        temp.data[i] = 0;
        for (int k = 0; k < 4; ++k)
            temp.data[i] += v.data[k] * m.data[k][i];
    }
    for (int i = 0; i < 4; ++i)
        v.data[i] = temp.data[i];
}

matrix_t create_scale_matrix(float scale_percent)
{
    float scale_coeff = 1 - scale_percent / 100;
    matrix_t m = new_identity_matrix();
    for (int i = 0; i < 3; i++)
        m.data[i][i] = scale_coeff;
    return m;
}

matrix_t create_rotate_y_matrix(float angle)
{
    matrix_t m = new_identity_matrix();
    m.data[1][1] = cos(angle);
    m.data[1][2] = sin(angle);
    m.data[2][1] = -sin(angle);
    m.data[2][2] = cos(angle);
    return m;
}

matrix_t create_rotate_x_matrix(float angle)
{
    matrix_t m = new_identity_matrix();
    m.data[0][0] = cos(angle);
    m.data[0][2] = -sin(angle);
    m.data[2][0] = sin(angle);
    m.data[2][2] = cos(angle);
    return m;
}

matrix_t create_move_matrix(float edition_x, float edition_y)
{
    matrix_t edition_matrix = new_identity_matrix();
    edition_matrix.data[3][0] = edition_x;
    edition_matrix.data[3][1] = edition_y;
    return edition_matrix;
}

matrix_t create_move_matrix(float edition_x, float edition_y, float edition_z)
{
    matrix_t edition_matrix = create_move_matrix(edition_x, edition_y);
    edition_matrix.data[3][2] = edition_z;
    return edition_matrix;
}

matrix_t create_scale_matrix(point_t center, float scale_percent)
{
    matrix_t edition_matrix = new_identity_matrix();
    matrix_t matrix_to_start = create_move_matrix(-center.x, -center.y, -center.z);
    matrix_t matrix_scale = create_scale_matrix(scale_percent);
    matrix_t matrix_to_center = create_move_matrix(center.x, center.y, center.z);
    composition(edition_matrix, matrix_to_start);
    composition(edition_matrix, matrix_scale);
    composition(edition_matrix, matrix_to_center);
    return edition_matrix;
}

matrix_t create_rotate_matrix(point_t center, float angle_x, float angle_y)
{
    matrix_t edition_matrix = new_identity_matrix();
    matrix_t matrix_to_start = create_move_matrix(-center.x, -center.y, -center.z);
    matrix_t matrix_rotate_y = create_rotate_y_matrix(angle_y);
    matrix_t matrix_rotate_x = create_rotate_x_matrix(angle_x);
    matrix_t matrix_to_center = create_move_matrix(center.x, center.y, center.z);
    composition(edition_matrix, matrix_to_start);
    composition(edition_matrix, matrix_rotate_y);
    composition(edition_matrix, matrix_rotate_x);
    composition(edition_matrix, matrix_to_center);
    return edition_matrix;
}

void fill_vector_with_point(vector_t &v, point_t &p)
{
    v.data[0] = p.x;
    v.data[1] = p.y;
    v.data[2] = p.z;
    v.data[3] = 1;
}

void fill_point_with_vector(point_t &p, vector_t &v)
{
    p.x = v.data[0] / v.data[3];
    p.y = v.data[1] / v.data[3];
    p.z = v.data[2] / v.data[3];
}

void apply_matrix_to_point_add_buffer(point_t &p, vector_t &v, matrix_t &m)
{
    fill_vector_with_point(v, p);
    composition(m, v);
    fill_point_with_vector(p, v);
}

void apply_matrix_to_center_add_buffer(point_t &p, vector_t &v, matrix_t &m, int need_to_move_center)
{
    if (need_to_move_center)
        apply_matrix_to_point_add_buffer(p, v, m);
}

void apply_matrix_to_points_add_buffer(point_t *points, int points_count, vector_t &v, matrix_t &m)
{
    for (int i = 0; i < points_count; ++i)
        apply_matrix_to_point_add_buffer(points[i], v, m);
}
