cmake_minimum_required(VERSION 3.21)
project(lockTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(lockTest main.cpp ../Maze.cpp ../Maze.h ../Coordinate.cpp ../Coordinate.h ../MazeSolverSeq.cpp ../MazeSolverSeq.h ../MazeSolverPar.cpp ../MazeSolverPar.h ../Particle.cpp ../Particle.h ../MazeSolver.cpp ../MazeSolver.h ../Map.cpp ../Map.h)

