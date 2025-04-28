#include "catch2/catch_all.hpp"
#include <catch2/catch_session.hpp>
#include "ttcan_scheduler.h"
#include "fff.h"
#include "ttcan_example_static_schedule.h"

uint8_t ttcan_tick_cnt[8];
uint8_t ttcan_sens_ctrl[2];
uint8_t ttcan_sens_data[2];

// Define FFF globals
DEFINE_FFF_GLOBALS;

TEST_CASE("Scheduler Init - Valid Context", "[init]")
{
    ttcan_scheduler_ctx_t ctx = {
        .timer          = nullptr,
        .schedule       = &ttcan_schedule,
        .master_mode_en = 1U,
        .curr_timeslot  = 5U,
        .curr_sched_idx = 2U,
    };

    auto status = ttcan_scheduler_init(&ctx);

    REQUIRE(status == TTCAN_SCHEDULER_STATUS_OK);
    REQUIRE(ctx.curr_timeslot == 0U);
    REQUIRE(ctx.curr_sched_idx == 0U);
}

TEST_CASE("Scheduler Start/Stop - Simple Calls", "[startstop]")
{
    ttcan_scheduler_ctx_t ctx = {
        .timer    = nullptr,
        .schedule = &ttcan_schedule,
    };

    REQUIRE(ttcan_scheduler_start(&ctx) == TTCAN_SCHEDULER_STATUS_OK);
    REQUIRE(ttcan_scheduler_stop(&ctx) == TTCAN_SCHEDULER_STATUS_OK);
}

TEST_CASE("Scheduler Timer Callback - Ref Slot and Data Slot Handling", "[timer_cb]")
{
    ttcan_scheduler_ctx_t ctx = {
        .timer          = nullptr,
        .schedule       = &ttcan_schedule,
        .master_mode_en = 1U,
        .curr_timeslot  = 0U,
        .curr_sched_idx = 0U,
    };

    SECTION("First Tick - Reference Slot")
    {
        auto action = ttcan_scheduler_timer_cb_get_action(&ctx);

        REQUIRE(action.message_type == TTCAN_MSG_REF_TRANSMIT);
        REQUIRE(ctx.curr_timeslot == 1U);
    }

    SECTION("Window 0 - First Message (READ control)")
    {
        ctx.curr_timeslot  = 1U;
        ctx.curr_sched_idx = 0U;

        // Now second call
        auto action = ttcan_scheduler_timer_cb_get_action(&ctx);

        REQUIRE(action.message_type == TTCAN_MSG_READ);
        REQUIRE(action.window_num == 0U);
        REQUIRE(action.data_ptr == &ttcan_sens_ctrl[0]);
        REQUIRE(ctx.curr_sched_idx == 1U);
    }

    SECTION("Window 1 - Second Message (WRITE control)")
    {
        ctx.curr_timeslot  = 1U;
        ctx.curr_sched_idx = 1U;
        ctx.curr_window    = 1U;
        auto action        = ttcan_scheduler_timer_cb_get_action(&ctx);

        REQUIRE(action.message_type == TTCAN_MSG_WRITE);
        REQUIRE(action.window_num == 1U);
        REQUIRE(action.data_ptr == &ttcan_sens_ctrl[0]);
        REQUIRE(ctx.curr_sched_idx == 2U);
    }

    SECTION("Window 2 - Third Message (WRITE data)")
    {
        ctx.curr_timeslot  = 2U;
        ctx.curr_sched_idx = 2U;
        ctx.curr_window    = 2U;

        auto action = ttcan_scheduler_timer_cb_get_action(&ctx);

        REQUIRE(action.message_type == TTCAN_MSG_WRITE);
        REQUIRE(action.window_num == 2U);
        REQUIRE(action.data_ptr == &ttcan_sens_data[0]);
        REQUIRE(ctx.curr_sched_idx == 3U);
    }
    SECTION("Window 10 - Fourth Message (WRITE data)")
    {
        ctx.curr_timeslot  = 3U;
        ctx.curr_sched_idx = 3U;
        ctx.curr_window    = 3U;
        for (uint8_t i = 3U; i < 11U; ++i)
        {
            auto action = ttcan_scheduler_timer_cb_get_action(&ctx);
            switch (i)
            {
                case 10U: {
                    REQUIRE(action.message_type == TTCAN_MSG_REF_TRANSMIT);
                    break;
                }
                case 11U: {
                    REQUIRE(action.message_type == TTCAN_MSG_WRITE);
                    break;
                }
                default: {
                    REQUIRE(action.message_type == TTCAM_MSG_WAIT);
                }
            }
        }
    }
}

TEST_CASE("Scheduler Deinit - No Error", "[deinit]")
{
    ttcan_scheduler_ctx_t ctx = {
        .timer    = nullptr,
        .schedule = &ttcan_schedule,
    };

    REQUIRE(ttcan_scheduler_deinit(&ctx) == TTCAN_SCHEDULER_STATUS_OK);
}

int
main (int argc, char *argv[])
{
    // your setup ...

    int result = Catch::Session().run(argc, argv);

    // your clean-up...

    return result;
}