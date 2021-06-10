#pragma once

#include "types.h"

void free_struct_allocates(data_t &d, draw_data_t draw_data);

void free_struct_allocates(data_t &d);

void free_struct_allocates(draw_data_t &d);

//void free_points

result_code_t allocate_draw_data(draw_data_t &draw_data);

result_code_t allocate_points(point_t **points, int count);

result_code_t allocate_lines(line_t **lines, int count);


void free_lines(line_t **data);

void free_points(point_t **data);
