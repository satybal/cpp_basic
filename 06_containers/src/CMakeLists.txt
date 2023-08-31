cmake_minimum_required(VERSION 3.14)

project(06.containers)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED TRUE)

add_compile_options(-Wall -Wextra -pedantic)

#add_subdirectory(src)

add_executable(containers
    containers.cpp
    vector_container.hpp
    list_container.hpp
)
