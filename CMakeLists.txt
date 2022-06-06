cmake_minimum_required(VERSION 3.22)
project(tictactoepp)

set(CMAKE_CXX_STANDARD 14)

add_executable(tictactoepp src/main.cpp src/Game.cpp src/Game.h)
