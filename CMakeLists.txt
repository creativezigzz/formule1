cmake_minimum_required(VERSION 3.16)
project(formule1 C)

set(CMAKE_C_STANDARD 99)

add_executable(formule1 src/main.c src/simulation.c inc/simulation.h src/simulation_utils.c inc/simulation_utils.h src/export_txt.c inc/export_txt.h src/car_stuff.c inc/car_stuff.h)
