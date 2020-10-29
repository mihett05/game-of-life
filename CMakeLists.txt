cmake_minimum_required(VERSION 3.16)
project(life C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(
        life
        main.c
        core/app.c
        core/app.h
        core/vector/vector.c
        core/vector/vector.h
        core/field.h
        core/field.c
)
target_link_libraries(life ${SDL2_LIBRARIES})

add_custom_target(SDLCopyBin
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/bin/ ${CMAKE_CURRENT_BINARY_DIR}
)

add_dependencies(life SDLCopyBin)