#ifndef TTCAN_SCHEDULER_TYPES_H
#define TTCAN_SCHEDULER_TYPES_H

#include <stdint.h>

typedef enum
{
    TTCAN_SCHEDULER_STATUS_OK,
    TTCAN_SCHEDULER_STATUS_ERR_NULL_PARAM,
} ttcan_scheduler_status_t;

typedef enum
{
    TTCAN_MSG_READ,
    TTCAN_MSG_WRITE
} ttcan_message_type_t;

typedef struct
{
    uint8_t              node_id;
    uint16_t             window_num;
    ttcan_message_type_t message_type;
    uint8_t             *data_ptr;
    uint8_t              num_of_bytes;
} ttcan_data_timeslot_t;

typedef struct
{
    uint8_t                node_id;
    ttcan_data_timeslot_t *messages;
    uint16_t               num_of_messages;
    uint16_t               tick_frequency;
    uint16_t               ref_tick_frequency;
    uint16_t               tick_window_size;
    uint8_t                free_tick_window_size;
} ttcan_schedule_t;

#endif /* TTCAN_SCHEDULER_TYPES_H */