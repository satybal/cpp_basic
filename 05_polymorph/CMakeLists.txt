cmake_minimum_required(VERSION 3.5)

project(05.homework)

add_executable(statistics 
    statistics.cpp
    istatistics.hpp
    min.cpp min.hpp 
    max.cpp max.hpp 
    mean.cpp mean.hpp 
    std.cpp std.hpp
    pct.cpp pct.hpp
)
set_target_properties(statistics PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

