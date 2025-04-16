#include "catch2/catch_all.hpp"
#include <catch2/catch_session.hpp>
#include "ttcan_scheduler.h"
#include "fff.h"

// Define FFF globals
DEFINE_FFF_GLOBALS;
/* Create mock functions */



TEST_CASE("init_function", "![init]")
{

}

TEST_CASE("init_function", "![register_node]")
{
}

TEST_CASE("init_function", "![param_check]") {

    
}

int
main (int argc, char *argv[])
{
    // your setup ...

    int result = Catch::Session().run(argc, argv);

    // your clean-up...

    return result;
}