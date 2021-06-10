#pragma once

#include "types.h"

typedef struct
{
    float data[4];
} vector_t;

typedef struct
{
    float data[4][4];
} matrix_t;

void apply_matrix_to_point_add_buffer(point_t &p, vector_t &v, matrix_t &m);

void apply_matrix_to_points_add_buffer(point_t *points, int points_count, vector_t &v, matrix_t &m);

void apply_matrix_to_center_add_buffer(point_t &p, vector_t &v, matrix_t &m, int need_to_move_center);

matrix_t create_move_matrix(float edition_x, float edition_y);

matrix_t create_scale_matrix(point_t center, float scale_percent);

matrix_t create_rotate_matrix(point_t center, float angle_x, float angle_y);
