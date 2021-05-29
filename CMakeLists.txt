cmake_minimum_required(VERSION 3.7)
project(Drone VERSION 0.0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

#add_library(WEKTOR ./inc/Wektor.hpp src/empty.cpp)
#target_include_directories(WEKTOR PUBLIC ./inc ./src ./fml)
#
#add_library(MACIERZ ./src/Macierz.cpp)
#target_link_libraries(MACIERZ WEKTOR)
#target_include_directories(MACIERZ PUBLIC ./inc ./src ./fml)

#set(LIBS WEKTOR MACIERZ)

add_executable(Drone ./src/_main.cpp)
#target_link_libraries(Drone ${LIBS})

target_compile_options(Drone PUBLIC -Wall -Wextra -pedantic -O3)