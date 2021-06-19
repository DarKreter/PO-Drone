cmake_minimum_required(VERSION 3.7)
project(Drone VERSION 0.0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_library(Gnuplot ./src/Gnuplot.cpp ./inc/Gnuplot.hpp)
target_include_directories(Gnuplot PUBLIC ./inc ./src)

add_library(Vector inc/Vector.hpp fml/Vector.tpp src/Vector.cpp)
target_include_directories(Vector PUBLIC ./inc ./src ./fml)

add_library(Matrix src/MatrixRot.cpp)
target_link_libraries(Matrix Vector)
target_include_directories(Matrix PUBLIC ./inc ./src ./fml)

add_library(Figure src/Figure.cpp inc/Figure.hpp fml/Figure.tpp)
target_link_libraries(Figure Vector Matrix)
target_include_directories(Figure PUBLIC ./inc ./src ./fml)

add_library(Prism src/Prism.cpp inc/Prism.hpp)
target_link_libraries(Prism Figure)
target_include_directories(Prism PUBLIC ./inc ./src)

add_library(Rectangle src/Rectangle.cpp inc/Rectangle.hpp)
target_link_libraries(Rectangle Vector)
target_include_directories(Rectangle PUBLIC ./inc ./src)

add_library(Cuboid src/Cuboid.cpp inc/Cuboid.hpp)
target_link_libraries(Cuboid Figure)
target_include_directories(Cuboid PUBLIC ./inc ./src)

add_library(Surface src/Surface.cpp inc/Surface.hpp)
target_link_libraries(Surface Figure)
target_include_directories(Surface PUBLIC ./inc ./src)

add_library(BrokenLine src/BrokenLine.cpp inc/BrokenLine.hpp)
target_link_libraries(BrokenLine Figure)
target_include_directories(BrokenLine PUBLIC ./inc ./src)

add_library(RidgeMountain src/RidgeMountain.cpp inc/RidgeMountain.hpp)
target_link_libraries(RidgeMountain Figure)
target_include_directories(RidgeMountain PUBLIC ./inc ./src)

add_library(Pyramid src/Pyramid.cpp inc/Pyramid.hpp)
target_link_libraries(Pyramid Figure)
target_include_directories(Pyramid PUBLIC ./inc ./src)

add_library(Plateau src/Plateau.cpp inc/Plateau.hpp)
target_link_libraries(Plateau Figure)
target_include_directories(Plateau PUBLIC ./inc ./src)

add_library(Drone src/Drone.cpp inc/Drone.hpp)
target_link_libraries(Drone Figure Cuboid Prism BrokenLine)
target_include_directories(Drone PUBLIC ./inc ./src)

add_library(Scene src/Scene.cpp inc/Scene.hpp)
target_link_libraries(Scene Cuboid Gnuplot)
target_include_directories(Scene PUBLIC ./inc ./src)

set(LIBS Gnuplot Vector Matrix Cuboid Figure Scene Prism Surface BrokenLine RidgeMountain Pyramid Plateau Drone Rectangle)
set(Compile_Flags -Wall -Wextra -pedantic -O3)

#set(CMAKE_CXX_FLAGS -pthread)

add_executable(Executable ./src/_main.cpp)
target_link_libraries(Executable ${LIBS})

target_compile_options(Executable PUBLIC ${Compile_Flags})