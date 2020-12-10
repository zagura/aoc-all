cmake_minimum_required(VERSION 3.13)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.in
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_executable(task1_d10.elf task1.cpp)
add_executable(task2_d10.elf task2.cpp)

