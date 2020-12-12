cmake_minimum_required(VERSION 3.13)

project(aoc_2015)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-g -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Wno-unused")
foreach(DAY 01day 02day 03day 04day 05day 06day 07day 08day 09day 10day 11day 12day 13day 14day 15day)
    add_subdirectory(${DAY})
endforeach(DAY)
