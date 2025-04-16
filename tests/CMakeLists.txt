include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.0
)

# CMake 3.14+
FetchContent_MakeAvailable(catch2)

FetchContent_Declare(
    fff
    GIT_REPOSITORY https://github.com/meekrosoft/fff.git
    GIT_TAG master
)

FetchContent_MakeAvailable(fff)

add_executable(scheduler_test ${CMAKE_CURRENT_LIST_DIR}/scheduler_test.cpp)
target_link_libraries(scheduler_test ${PROJECT_NAME} Catch2 fff)
target_compile_definitions(scheduler_test PUBLIC "FFF_GENERATE" "LWRB_DISABLE_ATOMIC")


add_test(
        NAME scheduler_test
        COMMAND scheduler_test
)

