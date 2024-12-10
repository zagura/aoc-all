cmake_minimum_required(VERSION 3.28)

file(GLOB INPUTS ${CMAKE_CURRENT_SOURCE_DIR}/*.in)
if (INPUTS)
    MESSAGE(STATUS "Day 05: Copying files... ${INPUTS}")
    file(COPY ${INPUTS}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
    MESSAGE(STATUS "Day 05: Inputs empty... ignoring")
endif()
add_executable(day5_task1 task1.cpp)
set_target_properties(day5_task1 PROPERTIES OUTPUT_NAME t1.elf)

add_executable(day5_task2 task2.cpp)
set_target_properties(day5_task2 PROPERTIES OUTPUT_NAME t2.elf)
