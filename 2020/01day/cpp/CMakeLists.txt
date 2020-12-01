cmake_minimum_required(VERSION 3.13)

add_executable(task1_d1.elf task1.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.in
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(task2_d1.elf task2.cpp)

