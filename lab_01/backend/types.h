#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <math.h>

typedef struct
{
    float x;
    float y;
    float z;
} point_t;

typedef struct
{
    float x;
    float y;
} point2d_t;

typedef struct
{
    bool loaded;
    bool saved;
} status_t;

typedef struct
{
    int p1;
    int p2;
} line_t;

typedef struct
{
    point_t center;
    point_t *points;
    line_t *lines;
    int points_count;
    int lines_count;
    status_t status;
} data_t;

data_t init_data();

typedef struct
{
    int points_count;
    int lines_count;
    point2d_t *points;
    point2d_t center;
    line_t *lines;
    status_t status;
} draw_data_t;

typedef enum
{
    action_load,
    action_save,
    action_rotate,
    action_move,
    action_scale,
    action_exit,
    action_load_projection
} action_t;

typedef enum
{
    ok,
    error_open_file,
    error_save_file,
    error_read_file,
    error_allocate_memory,
    error_empty_edit,
    error_empty_save,
    error_print_to_file,
    error_broken_file
} result_code_t;


typedef struct
{
    char *file_name;
    action_t action;
    float scale_percent;
    point2d_t point_previous;
    point2d_t point_actual;
    bool need_to_move_center;
    float angle_x;
    float angle_y;
    float delta_x;
    float delta_y;
} editions_data_t;



