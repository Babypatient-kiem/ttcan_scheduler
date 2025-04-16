cmake_minimum_required(VERSION 3.21)
project(ttcan_scheduler C CXX)

option(TTCAN_SCHEDULER_BUILD_TESTS "Enable building tests" YES)


add_library(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/src/ttcan_scheduler.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src/)


if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(CMAKE_C_STANDARD 11)
  set(CMAKE_C_STANDARD_REQUIRED True)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED True)
  set(MANIKIN_CAN_DRIVER_BUILD_TESTS ON)
endif()

include(FetchContent)

add_definitions("-DLWRB_DISABLE_ATOMIC")
FetchContent_Declare(
  lwrb
  GIT_REPOSITORY https://github.com/MaJerle/lwrb.git
  GIT_TAG v3.2.0
)
FetchContent_MakeAvailable(lwrb)

target_link_libraries(${PROJECT_NAME} lwrb)

if(TTCAN_SCHEDULER_DRIVER_BUILD_TESTS)
  add_subdirectory(tests)
endif()