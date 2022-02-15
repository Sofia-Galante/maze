//
// Created by Sofy on 06/02/2022.
//

#include <omp.h>

#include "MazeSolver.h"

#ifndef MAZE_MAZESOLVERPAR_H
#define MAZE_MAZESOLVERPAR_H


class MazeSolverPar : public MazeSolver{
public:
    explicit MazeSolverPar(Maze m) : MazeSolver(m) {}
    void solve(int numberOfParticles) override;

private:
    std::vector<Coordinate> validMoves(Coordinate p) override;
};

#endif //MAZE_MAZESOLVERPAR_H
