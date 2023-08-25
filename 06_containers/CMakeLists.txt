cmake_minimum_required(VERSION 3.5)

project(06.containers)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED TRUE)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(containers
    containers.cpp

    sequenceContainer.hpp
    #sequenceContainer.cpp

    singleListContainer.hpp
    #singleListContainer.cpp

    doublyListContainer.hpp
    #doublyListContainer.cpp
)
