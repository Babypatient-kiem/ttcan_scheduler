#ifndef TTCAN_EXAMPLE_STATIC_SCHEDULE_H
#define TTCAN_EXAMPLE_STATIC_SCHEDULE_H
#ifdef __cplusplus
extern "C"
{
#endif
#include "private/ttcan_scheduler_types.h"

    extern uint8_t ttcan_tick_cnt[8];
    extern uint8_t ttcan_sens_ctrl[2];
    extern uint8_t ttcan_sens_data[2];

    static ttcan_data_timeslot_t ttcan_messages[] = {
        {
            .node_id      = 10,
            .window_num   = 0,
            .message_type = TTCAN_MSG_READ,
            .data_ptr     = &ttcan_sens_ctrl[0],
            .num_of_bytes = sizeof(ttcan_sens_ctrl),
        },
        {
            .node_id      = 10,
            .window_num   = 1,
            .message_type = TTCAN_MSG_WRITE,
            .data_ptr     = &ttcan_sens_ctrl[0],
            .num_of_bytes = sizeof(ttcan_sens_ctrl),
        },
        {
            .node_id      = 10,
            .window_num   = 2,
            .message_type = TTCAN_MSG_WRITE,
            .data_ptr     = &ttcan_sens_data[0],
            .num_of_bytes = sizeof(ttcan_sens_data),
        },
        {
            .node_id      = 10,
            .window_num   = 10,
            .message_type = TTCAN_MSG_WRITE,
            .data_ptr     = &ttcan_sens_data[0],
            .num_of_bytes = sizeof(ttcan_sens_data),
        },
    };

    static ttcan_schedule_t ttcan_schedule = {
        .node_id               = 0,
        .messages              = ttcan_messages,
        .num_of_messages       = std::size(ttcan_messages),
        .tick_frequency        = 1000,
        .ref_tick_frequency    = 100,
        .tick_window_size      = 1,
        .free_tick_window_size = 1,
    };
#ifdef __cplusplus
}
#endif
#endif // TTCAN_EXAMPLE_STATIC_SCHEDULE_H
