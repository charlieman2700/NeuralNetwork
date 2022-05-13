cmake_minimum_required(VERSION 3.22)
project(NeuralNetwork)

set(CMAKE_CXX_STANDARD 14)

add_executable(NeuralNetwork main.cpp src/Matrix.cpp src/Matrix.hpp src/NeuralNetwork.cpp src/NeuralNetwork.hpp)
