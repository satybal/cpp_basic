cmake_minimum_required(VERSION 3.5)

project(06.containers)

add_executable(containers
    containers.cpp

    sequenceContainer.hpp
    #sequenceContainer.cpp

    singleListContainer.hpp
    #singleListContainer.cpp

    doublyListContainer.hpp
    #doublyListContainer.cpp
)

set_target_properties(containers PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)