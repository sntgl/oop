#pragma once

#include "types.h"

void update_projection_points(data_t &d, draw_data_t &draw_data, action_t action);

void update_projection_lines(data_t &d, draw_data_t &draw_data);

result_code_t create_draw_data(data_t &d, draw_data_t &draw_data);

#include "types.h"
#include "with_matrix.h"
