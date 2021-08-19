cmake_minimum_required(VERSION 3.7)

project(flatris)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS}
                ${SDL2_IMAGE_INCLUDE_DIRS}
                src/core)

add_executable(${CMAKE_PROJECT_NAME}
                src/core/app.cpp
                src/core/app_cleanup.cpp
                src/core/app_event.cpp
                src/core/app_init.cpp
                src/core/app_loop.cpp
                src/core/app_render.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}
                ${SDL2_LIBRARIES}
                ${SDL2_IMAGE_LIBRARIES})
