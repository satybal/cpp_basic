cmake_minimum_required(VERSION 3.5)
project(onRadio)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
find_package(SDL2_mixer REQUIRED)

add_executable(onRadio 
    src/onRadio.cpp
)

target_link_libraries(onRadio PRIVATE SDL2::SDL2)
target_link_libraries(onRadio PRIVATE SDL2::SDL2main)
target_link_libraries(onRadio PRIVATE ${SDL2_MIXER_LIBRARIES})

include_directories(${SDL2_MIXER_INCLUDE_DIR})

target_compile_options(onRadio PRIVATE 
    -g
    -Wall
    -Wextra
    -Werror
    -Wno-unused-parameter
    -pedantic
    # -fsanitize=address
)





# cmake_minimum_required(VERSION 3.5)
# project(onRadio)
# # Create an option to switch between a system sdl library and a vendored sdl library
# option(MYGAME_VENDORED "Use vendored libraries" OFF)
# if(MYGAME_VENDORED)
#     add_subdirectory(vendored/sdl EXCLUDE_FROM_ALL)
# else()
#     # 1. Look for a SDL2 package, 2. look for the SDL2 component and 3. fail if none can be found
#     find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
#     # 1. Look for a SDL2 package, 2. Look for the SDL2maincomponent and 3. DO NOT fail when SDL2main is not available
#     find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
# endif()

# # find_package(SDL2_mixer REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
# # target_link_libraries(${PROJECT_NAME} SDL2::Mixer)

# # Create your game executable target as usual
# add_executable(onRadio 
#     src/onRadio.cpp
# )

# # SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
# if(TARGET SDL2::SDL2main)
#     # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
#     target_link_libraries(onRadio PRIVATE SDL2::SDL2main)
# endif()

# # Link to the actual SDL2 library. SDL2::SDL2 is the shared SDL library, SDL2::SDL2-static is the static SDL libarary.
# target_link_libraries(onRadio PRIVATE SDL2::SDL2)

# target_compile_options(onRadio PRIVATE 
#     -g
#     -Wall
#     -Wextra
#     -Werror
#     -Wno-unused-parameter
#     -pedantic
#     # -fsanitize=address
# )


