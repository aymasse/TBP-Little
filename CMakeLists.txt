cmake_minimum_required(VERSION 3.7)
project(TBP_Little)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Coordinates.cpp Coordinates.h LittleNode.cpp LittleNode.h Little.cpp Little.h Segment.cpp Segment.h Regret.cpp Regret.h)
add_executable(TBP_Little ${SOURCE_FILES})