cmake_minimum_required(VERSION 3.13)

project(aoc_2019)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused")
foreach(DAY_NO RANGE 1 9)
    add_subdirectory("0${DAY_NO}day")
endforeach(${DAY_NO})

foreach(DAY_NO RANGE 10 25)
    add_subdirectory("${DAY_NO}day")
endforeach(${DAY_NO})
