#include "backend.h"
#include "with_projection.h"

result_code_t backend(draw_data_t &draw_data, editions_data_t &ed)
{
    static data_t d = init_data();
    result_code_t rc = ok;
    switch (ed.action) {
        case action_save:
            rc = save_data_to_file(d, ed.file_name);
            break;
        case action_load:
            rc = load_data_from_file(d, ed.file_name);
            break;
        case action_scale:
            rc = do_scale(d, ed.scale_percent);
            break;
        case action_rotate:
            rc = do_rotate(d, ed.angle_x, ed.angle_y);
            break;
        case action_move:
            rc = do_move(d, ed.need_to_move_center, ed.delta_x, ed.delta_y);
            break;
        case action_exit:
            free_struct_allocates(d, draw_data_t());
            break;
        case action_load_projection:
            rc = create_draw_data(d, draw_data);
            break;
    }
    update_projection_points(d, draw_data, ed.action);
    return rc;
}
