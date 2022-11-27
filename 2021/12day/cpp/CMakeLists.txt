cmake_minimum_required(VERSION 3.13)

file(GLOB INPUTS ${CMAKE_CURRENT_SOURCE_DIR}/*.in)
list(LENGTH INPUTS FILE_COUNT)
#if (NOT INPUTS)
if (FILE_COUNT)
    MESSAGE(STATUS "Copying files... ${INPUTS}")
    file(COPY ${INPUTS}
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
else()
    MESSAGE(STATUS "Inputs empty... ignoring")
endif()

add_executable(task1_d12.elf task1.cpp)
add_executable(task2_d12.elf task2.cpp)

