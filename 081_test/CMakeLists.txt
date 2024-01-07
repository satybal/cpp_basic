cmake_minimum_required(VERSION 3.5)
project(music)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
find_package(SDL2_mixer REQUIRED)

add_executable(music 
    music.cpp
)

include_directories(${SDL2_MIXER_INCLUDE_DIR})

target_link_libraries(music PRIVATE SDL2::SDL2)
target_link_libraries(music PRIVATE SDL2::SDL2main)
target_link_libraries(music PRIVATE ${SDL2_MIXER_LIBRARIES})
