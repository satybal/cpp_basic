cmake_minimum_required(VERSION 3.5)
project(sample)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
find_package(SDL2_mixer REQUIRED)
find_package(CURL REQUIRED)

# add_executable(music 
#     music.cpp
# )

include_directories(${SDL2_MIXER_INCLUDE_DIR})

# target_link_libraries(music PRIVATE SDL2::SDL2)
# target_link_libraries(music PRIVATE SDL2::SDL2main)
# target_link_libraries(music PRIVATE ${SDL2_MIXER_LIBRARIES})
add_executable(sample 
sample.cpp
)

# include_directories(${SDL2_MIXER_INCLUDE_DIR})

target_link_libraries(sample PRIVATE CURL::libcurl)  
target_link_libraries(sample PRIVATE SDL2::SDL2)
target_link_libraries(sample PRIVATE SDL2::SDL2main)
target_link_libraries(sample PRIVATE ${SDL2_MIXER_LIBRARIES})

# include(FetchContent)
# FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
#                          GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
# FetchContent_MakeAvailable(cpr)

# target_link_libraries(music PRIVATE cpr::cpr)
