cmake_minimum_required(VERSION 3.13)

file(GLOB INPUTS ${CMAKE_CURRENT_SOURCE_DIR}/../*.in)
if (INPUTS)
    MESSAGE(STATUS "Copying files... ${INPUTS}")
    file(COPY ${INPUTS}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
    MESSAGE(STATUS "Inputs empty... ignoring")
endif()
add_executable(task1_d19.elf task1.cpp)
add_executable(task2_d19.elf task2.cpp)
target_compile_options(task2_d19.elf PUBLIC -Wall -Wextra -Wformat -pedantic)

