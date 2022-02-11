cmake_minimum_required(VERSION 3.21)
project(state_io C)

set(CMAKE_C_STANDARD 99)

add_executable(state_io main.c Functions.h Mapfunc.h Generalfunc.h  Generals.h globals.c Functions.c Mafunc.c Generalfunc.c)
include_directories("/usr/include/SDL2")
target_link_libraries(state_io m SDL2 SDL2_gfx SDL2_ttf SDL2_mixer SDL2_image)

