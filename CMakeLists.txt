cmake_minimum_required(VERSION 3.7)

project(flatris)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(COMPILER_FLAGS
    "-g3"
    "-O0")

include_directories(${SDL2_INCLUDE_DIRS}
                ${SDL2_IMAGE_INCLUDE_DIRS}
                src)

add_executable(${CMAKE_PROJECT_NAME}
                #Entry
                src/main.cpp
                #Rest
                src/blocks/tetris_block.cpp
                src/map/tetris_map.cpp
                src/tetris_game.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}
                ${SDL2_LIBRARIES}
                ${SDL2_IMAGE_LIBRARIES})

target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC ${COMPILER_FLAGS})

set_property(TARGET ${CMAKE_PROJECT_NAME}
    PROPERTY CXX_STANDARD 17)
