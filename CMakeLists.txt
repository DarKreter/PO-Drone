cmake_minimum_required(VERSION 3.7)
project(Drone VERSION 0.0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_library(Gnuplot ./src/Gnuplot.cpp ./inc/Gnuplot.hpp)
target_include_directories(Gnuplot PUBLIC ./inc ./src)

add_library(Vector inc/Vector.hpp fml/Vector.tpp src/empty.cpp)
target_include_directories(Vector PUBLIC ./inc ./src ./fml)

add_library(Matrix src/MatrixRot.cpp)
target_link_libraries(Matrix Vector)
target_include_directories(Matrix PUBLIC ./inc ./src ./fml)

add_library(MatrixRot src/MatrixRot.cpp)
target_link_libraries(MatrixRot Vector Matrix)
target_include_directories(MatrixRot PUBLIC ./inc ./src)

add_library(Figure src/Figure.cpp inc/Figure.hpp)
target_link_libraries(Figure Vector)
target_include_directories(Figure PUBLIC ./inc ./src)

add_library(Cuboid src/Cuboid.cpp inc/Cuboid.hpp)
target_link_libraries(Cuboid Figure)
target_include_directories(Cuboid PUBLIC ./inc ./src)

add_library(Scene src/Scene.cpp inc/Scene.hpp)
target_link_libraries(Scene Cuboid Gnuplot)
target_include_directories(Scene PUBLIC ./inc ./src)

set(LIBS Gnuplot Vector Matrix MatrixRot Cuboid Figure Scene)
set(GCC_Compile_Flags -lpthread -Wall -Wextra -pedantic -O3)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(Drone ./src/_main.cpp)
target_link_libraries(Drone ${LIBS})

target_compile_options(Drone PUBLIC ${GCC_Compile_Flags})