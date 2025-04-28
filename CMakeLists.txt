cmake_minimum_required(VERSION 3.21)

# Detect if we are inside Zephyr
if(ZEPHYR_BASE)
  # We are building inside Zephyr as a module

  zephyr_library()

  zephyr_library_sources(
          src/ttcan_scheduler.c
          # add other .c files if needed
  )

  zephyr_include_directories(
          src/
  )

else()
  # We are building standalone (normal CMake)

  project(ttcan_scheduler C CXX)

  option(TTCAN_SCHEDULER_BUILD_TESTS "Enable building tests" OFF)

  add_library(${PROJECT_NAME}
          src/ttcan_scheduler.c
          # add other .c files if needed
  )

  target_include_directories(${PROJECT_NAME} PUBLIC src/)

  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    set(TTCAN_SCHEDULER_BUILD_TESTS ON)
  endif()


  if(TTCAN_SCHEDULER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
  endif()

endif()
