include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.0
)

# CMake 3.14+
FetchContent_MakeAvailable(catch2)

include(Catch)

FetchContent_Declare(
    fff
    GIT_REPOSITORY https://github.com/meekrosoft/fff.git
    GIT_TAG master
)

FetchContent_MakeAvailable(fff)

add_executable(ttcan_basic_functionality basic_functionality/test_basic_functionality.cpp)
target_link_libraries(ttcan_basic_functionality ${PROJECT_NAME} Catch2 fff)
target_compile_definitions(ttcan_basic_functionality PUBLIC "FFF_GENERATE" "LWRB_DISABLE_ATOMIC")
target_include_directories(${PROJECT_NAME} PUBLIC test_stubs/conf)
catch_discover_tests(ttcan_basic_functionality)
