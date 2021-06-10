#include "types.h"

data_t init_data()
{
    data_t d;
    d.lines = nullptr;
    d.points = nullptr;
    d.status.loaded = false;
    d.status.saved = true;
    d.lines_count = 0;
    d.points_count = 0;
    d.center = point_t{0, 0, 0};
    return d;
}