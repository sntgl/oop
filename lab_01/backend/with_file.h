#pragma once

#include "types.h"
#include "with_memory.h"
#include "with_projection.h"

result_code_t load_data_from_file(data_t &d, char *file_name);

result_code_t save_data_to_file(data_t &d, char *file_name);
