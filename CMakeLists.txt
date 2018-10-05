# cmake_minimum_required(VERSION <specify CMake version here>)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

add_executable(TicTacToe Board.cpp Board.h main.cpp)