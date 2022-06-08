cmake_minimum_required(VERSION 3.22)
project(microassembly C)

set(CMAKE_C_STANDARD 99)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(microassembly main.c ui.h ui.c bus.h bus.c register.h)


target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
