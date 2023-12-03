cmake_minimum_required(VERSION 3.27)

project(aoc_2023)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-g -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused")

find_package(fmt REQUIRED)
include_directories(${fmt_INCLUDE_DIRS})
link_libraries(fmt::fmt)
foreach(DAY_NO RANGE 1 9)
    add_subdirectory("0${DAY_NO}day/cpp")
endforeach(${DAY_NO})

foreach(DAY_NO RANGE 10 25)
    add_subdirectory("${DAY_NO}day/cpp")
endforeach(${DAY_NO})
