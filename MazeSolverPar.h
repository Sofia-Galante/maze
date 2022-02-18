//
// Created by Sofy on 06/02/2022.
//

#include <omp.h>

#include "MazeSolver.h"

#ifndef MAZE_MAZESOLVERPAR_H
#define MAZE_MAZESOLVERPAR_H


class MazeSolverPar : public MazeSolver{
public:
    explicit MazeSolverPar(Maze m, int threads, bool lock) : MazeSolver(m), threads(threads), withLock(lock) {}
    void solve(int numberOfParticles) override;

private:
    std::vector<Coordinate> validMoves(Coordinate p) override;
    std::vector<Coordinate> validMovesLock(Coordinate p);

    int threads;
    bool withLock;
};

#endif //MAZE_MAZESOLVERPAR_H
