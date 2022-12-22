cmake_minimum_required(VERSION 3.20)

file(GLOB INPUTS ${CMAKE_CURRENT_SOURCE_DIR}/*.in)
if (INPUTS)
    MESSAGE(STATUS "Copying files... ${INPUTS}")
    file(COPY ${INPUTS}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
    MESSAGE(STATUS "Inputs empty... ignoring")
endif()
add_executable(day21_task1 task1.cpp)
set_target_properties(day21_task1 PROPERTIES OUTPUT_NAME t1.elf)

add_executable(day21_task2 task2.cpp)
set_target_properties(day21_task2 PROPERTIES OUTPUT_NAME t2.elf)
