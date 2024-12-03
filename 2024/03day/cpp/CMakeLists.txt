cmake_minimum_required(VERSION 3.28)

file(GLOB INPUTS ${CMAKE_CURRENT_SOURCE_DIR}/*.in)
if (INPUTS)
    MESSAGE(STATUS "Day 03: Copying files... ${INPUTS}")
    file(COPY ${INPUTS}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
    MESSAGE(STATUS "Day 03: Inputs empty... ignoring")
endif()
add_executable(day3_task1 task1.cpp)
set_target_properties(day3_task1 PROPERTIES OUTPUT_NAME t1.elf)

add_executable(day3_task2 task2.cpp)
set_target_properties(day3_task2 PROPERTIES OUTPUT_NAME t2.elf)
