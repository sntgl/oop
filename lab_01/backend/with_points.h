#pragma once

#include "types.h"
#include "with_matrix.h"
#include "with_projection.h"

result_code_t do_move(data_t &d, bool need_to_move_center, float edition_x, float edition_y);

result_code_t do_scale(data_t &d, float scale_percent);

result_code_t do_rotate(data_t &d, float angle_x, float angle_y);

