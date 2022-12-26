cmake_minimum_required(VERSION 3.20)
project(snake)

set(CMAKE_CXX_STANDARD 23)
set(SDL2_PATH "/usr/include/SDL2")
find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

add_executable(snake main.cpp snake.cpp snake.h Game.cpp Game.h)

target_link_libraries(snake ${SDL2_LIBRARY} )

