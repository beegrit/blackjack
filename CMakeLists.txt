cmake_minimum_required(VERSION 3.25)
project(blackjack)

set(CMAKE_CXX_STANDARD 23)

add_executable(blackjack main.cpp simulate.cpp simulate.h)
